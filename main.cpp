
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
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RAT_DAC.h"
#include "driver/spi_master.h"
#include <Latchable.h>
#include "SamplerVoice.h"
#include "direct_IO.h"
#include "MCP_ADC.h"

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
hw_timer_t * timer0 = NULL;
hw_timer_t * timer1 = NULL;


// // inline
// void Core0TaskSetup()
// {

//   Serial.printf("Core %d getting ready to shit.\n", xPortGetCoreID());
//   delay(1000);
//   Serial.println("let's bronze up!!!");
//   delay(500);

//   // init your stuff for core0 here
// }

// void Core0TaskLoop()
// {
//   // put your loop body for core0 here
//   Serial.print("shit. ");
//   delay(100);
// }

// void Core0Task(void *parameter)
// {
//   Core0TaskSetup();
//   while (true)
//   {
//     Core0TaskLoop();

//     // this seems necessary to trigger the watchdog
//     // delay(1);
//     yield();
//   }
// }

// TaskHandle_t Core0TaskHnd;

// inline
// void Core0TaskInit()
// {
//   xTaskCreatePinnedToCore(Core0Task, "CoreTask0", 8000, NULL, 20, &Core0TaskHnd, 0);
// }


void loadPrefs(uint8_t vidx)
{
  prefs.begin("setup", true);  // Read-only = true
  Voice *pVoice = &voice[vidx];
  uint8_t cv_mode, mix, pitch, decay;
  switch(vidx)
  {
    case 0:
      pVoice->setDefaults(
        prefs.getUChar("sample0", 0),
        prefs.getUChar("mix0", 127),
        prefs.getUChar("decay0", 127),
        prefs.getChar("pitch0", 0),
        prefs.getUChar("cv_mode0", NONE));
      break;
    case 1:
      pVoice->setDefaults(
        prefs.getUChar("sample1", 3),
        prefs.getUChar("mix1", 127),
        prefs.getUChar("decay1", 127),
        prefs.getChar("pitch1", 0),
        prefs.getUChar("cv_mode1", NONE));
      break;
    case 2:
      pVoice->setDefaults(
        prefs.getUChar("sample2", 7),
        prefs.getUChar("mix2", 127),
        prefs.getUChar("decay2", 127),
        prefs.getChar("pitch2", 0),
        prefs.getUChar("cv_mode2", NONE));
      break;
    case 3:
      pVoice->setDefaults(
        prefs.getUChar("sample3", 17),
        prefs.getUChar("mix3", 127),
        prefs.getUChar("decay3", 127),
        prefs.getChar("pitch3", 0),
        prefs.getUChar("cv_mode3", NONE));
      break;
    default:
      break;
  }
  prefs.end();
  Serial.printf("Loaded Channel %d with sample %d (%s)\n", vidx, pVoice->sample.Q, pVoice->pSample->sname);
}

//#include "GMsamples/samples.h"            // general MIDI set - do not run wav2header on these or it will mess up the midi mapping
//#include "808samples/samples.h"           // 808 sounds
//#include "PNSsamples/samples.h"           // PNS soundfont set
//#include "Angular_Jungle_Set/samples.h"   // Jungle soundfont set - great!
//#include "WSA1_DRUMKIT/samples.h"         // WSA1 soundfont set
//#include "Angular_Techno_Set/samples.h"   // Techno

#include <sampledefs.h>

uint8_t gateInPins[]{GATEin_0, GATEin_1, GATEin_2, GATEin_3};
uint8_t gateOutPins[]{GATEout_0, GATEout_1, GATEout_2, GATEout_3};
volatile bool gates[]{0, 0, 0, 0};
volatile bool gateFlags[]{0, 0, 0, 0};
volatile long timeOn[]{0, 0, 0, 0};
volatile bool DAC_CLOCK(0);

void ICACHE_RAM_ATTR onTimer0()
{
  DAC_CLOCK = 1;
}


void ICACHE_RAM_ATTR onTimer1()
{
  clickEncoder.service();

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
}

#include "menusystem.h"  // has to follow encoder instance and sampledefs.h

void maindisplay(void)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.println();
  display.println("             DRUMBS");
  display.println();
  display.display();
}

//when menu is suspended
result idle(menuOut& o,idleEvent e)
{
  maindisplay();
  return proceed;
}

#define MISO 12
#define MOSI 13
#define SCLK 14

SPIClass mySpy(HSPI);
MCP3204 CV_ADC(MISO, MOSI, SCLK);
MCP4822 LEFT_DAC(255, SCLK, &mySpy);
MCP4822 RIGHT_DAC(255, SCLK, &mySpy);

/*
create HW SPI bus on HSPI
speed = 80 MHz
for DAC:
  write CS low
  write 16 bits @ 80 MHz
  write CS high

for ADC:
  write CS low
  transfer 16 bits @ 4 MHz
  write CS high

that's it. that's all I want to do.
*/
// ADC readings
const uint16_t ADC_RANGE(4095);  // 12 bit ADC
uint16_t CV_in[4];


void setup()
{
  Serial.begin(115200);
  Serial.printf("ESP.getFreeHeap() %d\n", ESP.getFreeHeap());
  Serial.printf("ESP.getMinFreeHeap() %d\n", ESP.getMinFreeHeap());
  Serial.printf("ESP.getHeapSize() %d\n", ESP.getHeapSize());
  Serial.printf("ESP.getMaxAllocHeap() %d\n", ESP.getMaxAllocHeap());
  Serial.printf("Total heap: %d\n", ESP.getHeapSize());
  Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());
  // Serial.printf("Core %d getting ready to shit.\n", xPortGetCoreID());

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("MORAD DRUMS Feb 3/19");
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

  pinMode(DAC0_CS, OUTPUT);
  pinMode(DAC1_CS, OUTPUT);

  digitalWrite(DAC0_CS, HIGH);
  digitalWrite(DAC1_CS, HIGH);

  CV_ADC.setSPI(&mySpy);

  uint32_t spiFreq(80 * 1000 * 1000);
  mySpy.setFrequency(spiFreq);
  SPI.setBitOrder(MSBFIRST);
  mySpy.begin(SCLK, MISO, MOSI, DAC0_CS);
  LEFT_DAC.setCS(DAC0_CS);
  RIGHT_DAC.setCS(DAC1_CS);
  LEFT_DAC.setSPIspeed(spiFreq);
  RIGHT_DAC.setSPIspeed(spiFreq);
  CV_ADC.softBegin(ADC_CS);

  CV_ADC.setSPIspeed(2 * 1000 * 1000);
  Serial.printf("SPI speed L: %d\n", LEFT_DAC.getSPIspeed());
  Serial.printf("SPI speed R: %d\n", RIGHT_DAC.getSPIspeed());
  Serial.printf("Uses HW SPI = %s\n", LEFT_DAC.usesHWSPI() ? "TRUE" : "FALSE");

  timer1 = timerBegin(1, 80, true);
  timerAttachInterrupt(timer1, &onTimer1, true);
  timerAlarmWrite(timer1, ENC_TIMER_MICROS, true);
  timerAlarmEnable(timer1);

  // Read and load setup data
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more info).
  timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, &onTimer0, true);
  timerAlarmWrite(timer0, DAC_TIMER_MICROS, true);

  nav.idleTask=idle;//point a function to be used when menu is suspended
  nav.idleOn(); // start up in idle state
  nav.navRoot::timeOut=30; // inactivity timeout

  maindisplay();
  // https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/

  for (uint8_t vidx(0); vidx < 4; ++vidx)
  {
    loadPrefs(vidx);
  }
  timerAlarmEnable(timer0);
}

uint16_t writeVal[4];
long updateTime(0);

void doShit()
{
  updateTime = micros();
  for (uint8_t v = 0; v < 4; ++v)
  {
    voice[v].tick(&writeVal[v]);
  }

  LEFT_DAC.transferAB(writeVal[0], writeVal[1]);
  RIGHT_DAC.transferAB(writeVal[2], writeVal[3]);
}


void loop()
{
  bool shit(0);
  cli();
  if (DAC_CLOCK)
  {
    DAC_CLOCK = 0;
    shit = 1;
  }
  sei();
  if (shit)
  {
    doShit();
  }

  bool gateCopy[]{0, 0, 0, 0};
  cli();
  for (uint8_t g(0); g < 4; ++g)
  {
    gateCopy[g] = gateFlags[g];
    gateFlags[g] = 0;
  }
  sei();

  for (uint8_t g(0); g < 4; ++g)
  {
    if (!gateCopy[g])
    {
      continue;
    }
    CV_in[g] = (uint16_t)CV_ADC.analogRead(g);
    voice[g].start(CV_in[g]);
  }

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

    if (micros() - timeOn[g] > 100000)
    {
      directWriteLow(gateOutPins[g]);
      timeOn[g] = 0;
    }
  }

  if (micros() - updateTime > (DAC_TIMER_MICROS / 2))
  {
    nav.doInput();
    if (nav.changed(0))
    {
      nav.doOutput();
      display.display();
    }
  }
}
