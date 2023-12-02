
#include <Arduino.h>
#include <Preferences.h>
Preferences prefs;

#include <WiFi.h>
#include <pgmspace.h>
#include <menu.h>
#include <menuIO/clickEncoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialOut.h>
#include <menuIO/adafruitGfxOut.h>
#include <menuIO/serialIn.h>
#include "MORAD_IO.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/spi_master.h"
#include "driver/spi_common.h"
#include "SamplerVoice.h"
#include "direct_IO.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/timers.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

const uint8_t SCREEN_WIDTH(128); // OLED display width, in pixels
const uint8_t SCREEN_HEIGHT(32); // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
const uint8_t OLED_RESET     (4); // Reset pin # (or -1 if sharing Arduino reset pin)
const uint8_t SCREEN_ADDRESS (0x3C); ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET);


// encoder
ClickEncoder clickEncoder(ENC_A, ENC_B, ENC_SW, 4); // divide by 4 works best with my encoder
ClickEncoderStream encStream(clickEncoder,1);

// sample interrupt timer defs
const uint16_t DAC_TIMER_MICROS(45);  // 22khz interrupt rate for DAC
const uint16_t ENC_TIMER_MICROS(250); // 4khz for encoder

hw_timer_t * sampleClock = NULL;
hw_timer_t * timer1 = NULL;

//#include "GMsamples/samples.h"            // general MIDI set - do not run wav2header on these or it will mess up the midi mapping
//#include "808samples/samples.h"           // 808 sounds
//#include "PNSsamples/samples.h"           // PNS soundfont set
//#include "Angular_Jungle_Set/samples.h"   // Jungle soundfont set - great!
//#include "WSA1_DRUMKIT/samples.h"         // WSA1 soundfont set
//#include "Angular_Techno_Set/samples.h"   // Techno

#include <sampledefs.h>

uint8_t gateInPins[] {GATEin_0,  GATEin_1,  GATEin_2,  GATEin_3};
uint8_t gateOutPins[]{GATEout_0, GATEout_1, GATEout_2, GATEout_3};

volatile bool gates[]    {0, 0, 0, 0};
volatile long timeOn[]   {0, 0, 0, 0};
volatile bool gateFlags[]{0, 0, 0, 0};

// ADC readings
const uint16_t ADC_RANGE(4095);  // 12 bit ADC
uint16_t CV_in[4];

uint16_t voiceOutputBuffer[4];
long updateTime(0);
#define MISO 12
#define MOSI 13
#define SCLK 14

SPIClass mySpy(HSPI);
SPISettings DAC_spi_settings(   80 * 1000 * 1000, MSBFIRST, SPI_MODE0);
SPISettings MCP3204_spi_settings(2 * 1000 * 1000, MSBFIRST, SPI_MODE0);

SemaphoreHandle_t cvAdc_sem;
SemaphoreHandle_t dacTimer_sem;
SemaphoreHandle_t voiceBufferAccess_sem;

TaskHandle_t dacTaskHandle(NULL);
TaskHandle_t adcTaskHandle(NULL);
TaskHandle_t voiceTaskHandle(NULL);

void IRAM_ATTR voiceTask(void *param)
{
  voiceBufferAccess_sem = xSemaphoreCreateBinary();

  while (1)
  {
    xSemaphoreTake(voiceBufferAccess_sem, portMAX_DELAY);
    for (uint8_t v = 0; v < 4; ++v)
    {
      voice[v].tick(&voiceOutputBuffer[v]);
    }
  }
}


void IRAM_ATTR adcTask(void *param)
{
  uint8_t allTheData[4][3]{{0x06, 0, 0}, {0x06, 0x40, 0}, {0x06, 0x80, 0}, {0x06, 0xC0, 0}};
  uint8_t allTheOuts[4][3]{{0,    0, 0}, {0,    0,    0}, {0,    0,    0}, {0,    0,    0}};
  pinMode(ADC_CS, OUTPUT);
  digitalWrite(ADC_CS, HIGH);
  digitalWrite(ADC_CS, LOW);    //  force communication (See datasheet)
  digitalWrite(ADC_CS, HIGH);
  cvAdc_sem = xSemaphoreCreateBinary();
  while (1)
  {
    xSemaphoreTake(cvAdc_sem, portMAX_DELAY);
    mySpy.beginTransaction(MCP3204_spi_settings);
    for (uint8_t ch(0); ch < 4; ++ch)
    {
      directWriteLow(ADC_CS);
      mySpy.transferBytes(allTheData[ch], allTheOuts[ch], 3);
      directWriteHigh(ADC_CS);
      CV_in[ch] = (uint16_t)(256 * allTheOuts[ch][1] + allTheOuts[ch][2]) & 4095;
    }
    mySpy.endTransaction();
  }
}


void ICACHE_RAM_ATTR sampleClockTick()
{
  static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR(dacTimer_sem, &xHigherPriorityTaskWoken);
  if (xHigherPriorityTaskWoken)
  {
    portYIELD_FROM_ISR(); // this wakes up dacTask immediately
  }
}


// Updates DAC outputs to create audio
void IRAM_ATTR dacTask(void *param)
{
  pinMode(DAC0_CS, OUTPUT);
  pinMode(DAC1_CS, OUTPUT);

  digitalWrite(DAC0_CS, HIGH);
  digitalWrite(DAC1_CS, HIGH);

  // Timer will run at sample rate and will semgive when it's time
  // to update the outputs
  dacTimer_sem = xSemaphoreCreateBinary();
  sampleClock = timerBegin(0, 80, true);
  timerAttachInterrupt(sampleClock, &sampleClockTick, true);
  timerAlarmWrite(sampleClock, DAC_TIMER_MICROS, true);
  timerAlarmEnable(sampleClock);

  // Fire up the HSPI
  mySpy.begin(SCLK, MISO, MOSI, DAC0_CS);
  mySpy.setFrequency(80 * 1000 * 1000);
  mySpy.setDataMode(SPI_MODE0);
  mySpy.setBitOrder(MSBFIRST);
  uint16_t dacData[4];
  while (1)
  {
    // Prevent the Arduino watchdog from thinking it's being ignored
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;

    // Grab the output values for all four channels
    for (uint8_t ch(0); ch < 4; ++ch)
    {
      dacData[ch] = voiceOutputBuffer[ch];
    }

    // Give the voice tick algo running on Core 1 access to the output
    // buffers now that we've safely copied their values
    xSemaphoreGive(voiceBufferAccess_sem);

    // Wait for the sample clock and then acquire the SPI bus
    xSemaphoreTake(dacTimer_sem, portMAX_DELAY);
    mySpy.beginTransaction(DAC_spi_settings);

    // Update the outputs
    directWriteLow(DAC0_CS);
    mySpy.write16(0x3000 | dacData[0]);
    directWriteHigh(DAC0_CS);

    directWriteLow(DAC0_CS);
    mySpy.write16(0xB000 | dacData[1]);
    directWriteHigh(DAC0_CS);

    directWriteLow(DAC1_CS);
    mySpy.write16(0x3000 | dacData[2]);
    directWriteHigh(DAC1_CS);

    directWriteLow(DAC1_CS);
    mySpy.write16(0xB000 | dacData[3]);
    directWriteHigh(DAC1_CS);

    // Free the SPI bus
    mySpy.endTransaction();
  }
}


// Reads Trigger inputs and Nav Encoder
void ICACHE_RAM_ATTR onTimer1()
{
  for (uint8_t g = 0; g < NUM_VOICES; ++g)
  {
    bool tmp = !directRead(gateInPins[g]);
    if (tmp)
    {
      if (!gates[g])
      {
        gateFlags[g] = 1;
      }
    }
    gates[g] = tmp;
  }
  clickEncoder.service();
}

#include "menusystem.h"  // has to follow encoder instance and sampledefs.h

void maindisplay(void)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.println("~~(__C* >");
  display.println();
  display.println("      RAT DRUMS");
  display.println("            < *D__)~~");
  display.println();
  display.display();
}

// When menu is suspended
result idle(menuOut& o,idleEvent e)
{
  maindisplay();
  return proceed;
}

void setup()
{
  delay(500);
  Serial.begin(115200);
  Serial.printf("ESP.getFreeHeap() %d\n", ESP.getFreeHeap());
  Serial.printf("ESP.getMinFreeHeap() %d\n", ESP.getMinFreeHeap());
  Serial.printf("ESP.getHeapSize() %d\n", ESP.getHeapSize());
  Serial.printf("ESP.getMaxAllocHeap() %d\n", ESP.getMaxAllocHeap());
  Serial.printf("Total heap: %d\n", ESP.getHeapSize());
  Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("  LET'S BRONZE UP!!!");
  display.display();
  delay(500);

  pinMode(GATEout_0, OUTPUT);
  pinMode(GATEout_1, OUTPUT);
  pinMode(GATEout_2, OUTPUT);
  pinMode(GATEout_3, OUTPUT);

  directWriteLow(GATEout_0);
  directWriteLow(GATEout_1);
  directWriteLow(GATEout_2);
  directWriteLow(GATEout_3);

  pinMode(GATEin_0, INPUT);
  pinMode(GATEin_1, INPUT);
  pinMode(GATEin_2, INPUT);
  pinMode(GATEin_3, INPUT);

  timer1 = timerBegin(1, 80, true);
  timerAttachInterrupt(timer1, &onTimer1, true);
  timerAlarmWrite(timer1, ENC_TIMER_MICROS, true);
  timerAlarmEnable(timer1);

  nav.idleTask = idle;        //point a function to be used when menu is suspended
  nav.idleOn();               // start up in idle state
  nav.navRoot::timeOut = 30;  // inactivity timeout

  maindisplay();

  // https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
  for (uint8_t vidx(0); vidx < 4; ++vidx)
  {
    loadPrefs(vidx);
  }

  xTaskCreatePinnedToCore
  (
    dacTask,
    "DAC Task",
    4096,
    NULL,
    10,
    &dacTaskHandle,
    0
  );

  xTaskCreatePinnedToCore
  (
    adcTask,
    "ADC Task",
    4096,
    NULL,
    10,
    &adcTaskHandle,
    0
  );

  xTaskCreatePinnedToCore
  (
    voiceTask,
    "voice Task",
    4096,
    NULL,
    10,
    &voiceTaskHandle,
    1
  );
}


void loop()
{
  // Check for incoming triggers
  bool gateCopy[]{0, 0, 0, 0};
  bool trig(0);
  cli();
  for (uint8_t g(0); g < 4; ++g)
  {
    gateCopy[g] = gateFlags[g];
    trig |= gateCopy[g];
    gateFlags[g] = 0;
  }
  sei();

  // Read ADC
  if (trig)
  {
    xSemaphoreTake(dacTimer_sem, portMAX_DELAY);
    timerAlarmDisable(sampleClock);
    xSemaphoreGiveFromISR(cvAdc_sem, NULL);
    vTaskDelay(1);
    timerAlarmEnable(sampleClock);
  }

  for (uint8_t g(0); g < 4; ++g)
  {
    if (!gateCopy[g])
    {
      continue;
    }

    // Start the sample a-playin'
    voice[g].sampleindex = -1.0;
    voice[g].start(CV_in[g]);

    // Stop its neighbor if you're into that kinda thing
    if (voice[g].choke.Q) voice[g + 1].sampleindex = -1.0;
  }

  // DEBUG: blink LEDs on trigger in
  for (uint8_t g(0); g < 4; ++g)
  {
    if (gateCopy[g])
    {
      directWriteHigh(gateOutPins[g]);
      timeOn[g] = micros();
      continue;
    }

    if (!timeOn[g])
    {
      continue;
    }

    if (micros() - timeOn[g] > 50000)
    {
      directWriteLow(gateOutPins[g]);
      timeOn[g] = 0;
    }
  }

  // Menu stuff
  nav.doInput();
  if (nav.changed(0))
  {
    nav.doOutput();
    display.display();
  }
}
