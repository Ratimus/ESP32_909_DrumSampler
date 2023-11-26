//using namespace Menu;

#define gfxWidth 128
#define gfxHeight 32
#define fontX 6    // font width in pixels
#define fontY 10  // vertical text spacing
#define MAX_DEPTH 3 // max menu depth?
#define textScale 1

/*
MENU OPTIONS:
 Global:
  choke
 Per Channel:
  sample
  level
  attack
  decay
  pitch

  CV_A assign (default is pitch)
  CV_B assign (default is decay)
  Mod Gate assign (default is accent)

 One Voice mode:
  only one channel; may have secondary sample
  all CV and Gates route to one channel
  Meta Mode: CV selects sample
   - can limit selectable samples to subset of those loaded
*/

// save settings to eeprom
result savesetup(void)
{
    // https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
  prefs.begin("setup", false);  // Read-only = false
  for (uint8_t vidx(0); vidx < 4; ++vidx)
  {
    Voice *pVoice = &voice[vidx];
    switch(vidx)
    {
      case 0:
        prefs.putUChar("cv_mode0", pVoice->cv_mode.D);
        prefs.putUChar("sample0", pVoice->sample.D);
        prefs.putUChar("mix0", pVoice->mix.D);
        prefs.putChar("pitch0", pVoice->pitch.D);
        prefs.putUChar("decay0", pVoice->decay.D);
        prefs.putUChar("envShape0", pVoice->envShape.D);
        break;
      case 1:
        prefs.putUChar("cv_mode1", pVoice->cv_mode.D);
        prefs.putUChar("sample1", pVoice->sample.D);
        prefs.putUChar("mix1", pVoice->mix.D);
        prefs.putChar("pitch1", pVoice->pitch.D);
        prefs.putUChar("decay1", pVoice->decay.D);
        prefs.putUChar("envShape1", pVoice->envShape.D);
        break;
      case 2:
        prefs.putUChar("cv_mode2", pVoice->cv_mode.D);
        prefs.putUChar("sample2", pVoice->sample.D);
        prefs.putUChar("mix2", pVoice->mix.D);
        prefs.putChar("pitch2", pVoice->pitch.D);
        prefs.putUChar("decay2", pVoice->decay.D);
        prefs.putUChar("envShape2", pVoice->envShape.D);
        break;
      case 3:
        prefs.putUChar("cv_mode3", pVoice->cv_mode.D);
        prefs.putUChar("sample3", pVoice->sample.D);
        prefs.putUChar("mix3", pVoice->mix.D);
        prefs.putChar("pitch3", pVoice->pitch.D);
        prefs.putUChar("decay3", pVoice->decay.D);
        prefs.putUChar("envShape3", pVoice->envShape.D);
        break;
      default:
        break;
    }
  }
  prefs.end();
  return proceed;
}


result resetVoice1()
{
  voice[0].resetToDefaults();
  return proceed;
}
result resetVoice2()
{
  voice[1].resetToDefaults();
  return proceed;
}
result resetVoice3()
{
  voice[2].resetToDefaults();
  return proceed;
}
result resetVoice4()
{
  voice[3].resetToDefaults();
  return proceed;
}



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
        prefs.getUChar("cv_mode0", NONE),
        prefs.getUChar("envShape0", 16));
      break;
    case 1:
      pVoice->setDefaults(
        prefs.getUChar("sample1", 3),
        prefs.getUChar("mix1", 127),
        prefs.getUChar("decay1", 127),
        prefs.getChar("pitch1", 0),
        prefs.getUChar("cv_mode1", NONE),
        prefs.getUChar("envShape1", 16));
      break;
    case 2:
      pVoice->setDefaults(
        prefs.getUChar("sample2", 7),
        prefs.getUChar("mix2", 127),
        prefs.getUChar("decay2", 127),
        prefs.getChar("pitch2", 0),
        prefs.getUChar("cv_mode2", NONE),
        prefs.getUChar("envShape2", 16));
      break;
    case 3:
      pVoice->setDefaults(
        prefs.getUChar("sample3", 17),
        prefs.getUChar("mix3", 127),
        prefs.getUChar("decay3", 127),
        prefs.getChar("pitch3", 0),
        prefs.getUChar("cv_mode3", NONE),
        prefs.getUChar("envShape3", 16));
      break;
    default:
      break;
  }
  prefs.end();
  Serial.printf("Loaded Channel %d with sample %d (%s)\n", vidx, pVoice->sample.Q, pVoice->pSample->sname);
}


SELECT(voice[0].cv_mode.D,subMenu_CV_A_MODE," CV    ",doNothing,noEvent,wrapStyle,
  VALUE("Not Assigned",NONE,doNothing,noEvent),
  VALUE("Sample",SAMPLE,doNothing,noEvent),
  VALUE("Pitch",PITCH,doNothing,noEvent),
  VALUE("Decay",DECAY,doNothing,noEvent),
  VALUE("Volume",VOLUME,doNothing,noEvent)
);

SELECT(voice[1].cv_mode.D,subMenu_CV_B_MODE," CV    ",doNothing,noEvent,wrapStyle,
  VALUE("Not Assigned",NONE,doNothing,noEvent),
  VALUE("Sample",SAMPLE,doNothing,noEvent),
  VALUE("Pitch",PITCH,doNothing,noEvent),
  VALUE("Decay",DECAY,doNothing,noEvent),
  VALUE("Volume",VOLUME,doNothing,noEvent)
);

SELECT(voice[2].cv_mode.D,subMenu_CV_C_MODE," CV    ",doNothing,noEvent,wrapStyle,
  VALUE("Not Assigned",NONE,doNothing,noEvent),
  VALUE("Sample",SAMPLE,doNothing,noEvent),
  VALUE("Pitch",PITCH,doNothing,noEvent),
  VALUE("Decay",DECAY,doNothing,noEvent),
  VALUE("Volume",VOLUME,doNothing,noEvent)
);

SELECT(voice[3].cv_mode.D,subMenu_CV_D_MODE," CV    ",doNothing,noEvent,wrapStyle,
  VALUE("Not Assigned",NONE,doNothing,noEvent),
  VALUE("Sample",SAMPLE,doNothing,noEvent),
  VALUE("Pitch",PITCH,doNothing,noEvent),
  VALUE("Decay",DECAY,doNothing,noEvent),
  VALUE("Volume",VOLUME,doNothing,noEvent)
);

MENU(voice_A,"Voice 1",doNothing,noEvent,wrapStyle,
  FIELD(voice[0].sample.D," Sample","",0,(NUM_SAMPLES-1),1,0,doNothing,noEvent,wrapStyle),
  FIELD(voice[0].pitch.D," Pitch ","",-100,100,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[0].decay.D," Decay ","",0,127,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[0].mix.D," Level ","",0,255,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[0].envShape.D," Contour ","",1,25,1,0,doNothing,noEvent,noStyle),
  SUBMENU(subMenu_CV_A_MODE),
  OP("Reset to Defaults",resetVoice1,enterEvent),
  EXIT("<Back"));

MENU(voice_B,"Voice 2",doNothing,noEvent,wrapStyle,
  FIELD(voice[1].sample.D," Sample","",0,(NUM_SAMPLES-1),1,0,doNothing,noEvent,wrapStyle),
  FIELD(voice[1].pitch.D," Pitch ","",-100,100,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[1].decay.D," Decay ","",0,127,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[1].mix.D," Level ","",0,255,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[1].envShape.D," Contour ","",1,25,1,0,doNothing,noEvent,noStyle),
  SUBMENU(subMenu_CV_B_MODE),
  OP("Reset to Defaults",resetVoice2,enterEvent),
  EXIT("<Back"));

MENU(voice_C,"Voice 3",doNothing,noEvent,wrapStyle,
  FIELD(voice[2].sample.D," Sample","",0,(NUM_SAMPLES-1),1,0,doNothing,noEvent,wrapStyle),
  FIELD(voice[2].pitch.D," Pitch ","",-100,100,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[2].decay.D," Decay ","",0,127,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[2].mix.D," Level ","",0,255,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[2].envShape.D," Contour ","",1,25,1,0,doNothing,noEvent,noStyle),
  SUBMENU(subMenu_CV_C_MODE),
  OP("Reset to Defaults",resetVoice3,enterEvent),
  EXIT("<Back"));

MENU(voice_D,"Voice 4",doNothing,noEvent,wrapStyle,
  FIELD(voice[3].sample.D," Sample","",0,(NUM_SAMPLES-1),1,0,doNothing,noEvent,wrapStyle),
  FIELD(voice[3].pitch.D," Pitch ","",-100,100,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[3].decay.D," Decay ","",0,127,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[3].mix.D," Level ","",0,255,1,0,doNothing,noEvent,noStyle),
  FIELD(voice[3].envShape.D," Contour ","",1,25,1,0,doNothing,noEvent,noStyle),
  SUBMENU(subMenu_CV_D_MODE),
  OP("Reset to Defaults",resetVoice4,enterEvent),
  EXIT("<Back"));

MENU(mainMenu,"        SETUP",doNothing,noEvent,noStyle,
  SUBMENU(voice_A),
  SUBMENU(voice_B),
  SUBMENU(voice_C),
  SUBMENU(voice_D),
  OP("Update Defaults W/Changes",savesetup,enterEvent),
  EXIT("<Exit Setup Menu")
 );


 //  FIELD(MIDI_Channel,"MIDI Channel","",1,16,1,0,doNothing,noEvent,wrapStyle),
  // define menu colors --------------------------------------------------------
//  {{disabled normal,disabled selected},{enabled normal,enabled selected, enabled editing}}
//monochromatic color table
const colorDef<uint16_t> colors[] MEMMODE={
  {{WHITE,BLACK},{WHITE,BLACK,BLACK}},//bgColor
  {{BLACK,WHITE},{BLACK,WHITE,WHITE}},//fgColor
  {{BLACK,WHITE},{BLACK,WHITE,WHITE}},//valColor
  {{BLACK,WHITE},{BLACK,WHITE,WHITE}},//unitColor
  {{BLACK,WHITE},{WHITE,WHITE,WHITE}},//cursorColor
  {{BLACK,WHITE},{WHITE,BLACK,BLACK}},//titleColor
};

//the encoder button is a keyboard with only one key
keyMap encBtn_map[]={{-ENC_SW,defaultNavCodes[enterCmd].ch}};  //negative pin numbers use internal pull-up, switch is on when low
keyIn<1> encButton(encBtn_map);   //1 is the number of keys

// menu system is driven by the encoder stream
MENU_INPUTS(in,&encStream);

MENU_OUTPUTS(out,MAX_DEPTH
  ,ADAGFX_OUT(display,colors,fontX,fontY,{0,0,gfxWidth/fontX,gfxHeight/fontY})
  ,NONE //must have 2 items at least if using this macro
);

NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);
