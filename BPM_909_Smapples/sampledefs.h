// sample structure built by wav2header based on wav2sketch by Paul Stoffregen

struct sample_t {
  const int16_t * samplearray; // pointer to sample array
  uint32_t samplesize; // size of the sample array
  uint32_t sampleindex; // current sample array index when playing. index at last sample= not playing
  uint8_t MIDINOTE;  // MIDI note on that plays this sample
  uint8_t play_volume; // play volume 0-127
  char sname[20];        // sample name
} sample[] = {

	Ch1,	// pointer to sample array
	Ch1_SIZE,	// size of the sample array
	Ch1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	35,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Ch1",	// sample name

	Ch2,	// pointer to sample array
	Ch2_SIZE,	// size of the sample array
	Ch2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	36,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Ch2",	// sample name

	Ch3,	// pointer to sample array
	Ch3_SIZE,	// size of the sample array
	Ch3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	37,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Ch3",	// sample name

	Cp1,	// pointer to sample array
	Cp1_SIZE,	// size of the sample array
	Cp1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	38,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cp1",	// sample name

	Cp2,	// pointer to sample array
	Cp2_SIZE,	// size of the sample array
	Cp2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	39,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cp2",	// sample name

	Cp3,	// pointer to sample array
	Cp3_SIZE,	// size of the sample array
	Cp3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	40,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cp3",	// sample name

	Cr1,	// pointer to sample array
	Cr1_SIZE,	// size of the sample array
	Cr1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	41,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cr1",	// sample name

	Cr2,	// pointer to sample array
	Cr2_SIZE,	// size of the sample array
	Cr2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	42,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cr2",	// sample name

	Cr3,	// pointer to sample array
	Cr3_SIZE,	// size of the sample array
	Cr3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	43,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cr3",	// sample name

	Cy1,	// pointer to sample array
	Cy1_SIZE,	// size of the sample array
	Cy1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	44,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cy1",	// sample name

	Cy2,	// pointer to sample array
	Cy2_SIZE,	// size of the sample array
	Cy2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	45,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Cy2",	// sample name

	Ht1,	// pointer to sample array
	Ht1_SIZE,	// size of the sample array
	Ht1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	46,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Ht1",	// sample name

	Ht2,	// pointer to sample array
	Ht2_SIZE,	// size of the sample array
	Ht2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	47,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Ht2",	// sample name

	Ht3,	// pointer to sample array
	Ht3_SIZE,	// size of the sample array
	Ht3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	48,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Ht3",	// sample name

	Kd1,	// pointer to sample array
	Kd1_SIZE,	// size of the sample array
	Kd1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	49,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd1",	// sample name

	Kd10,	// pointer to sample array
	Kd10_SIZE,	// size of the sample array
	Kd10_SIZE,	//sampleindex. if at end of sample array sound is not playing
	50,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd10",	// sample name

	Kd11,	// pointer to sample array
	Kd11_SIZE,	// size of the sample array
	Kd11_SIZE,	//sampleindex. if at end of sample array sound is not playing
	51,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd11",	// sample name

	Kd12,	// pointer to sample array
	Kd12_SIZE,	// size of the sample array
	Kd12_SIZE,	//sampleindex. if at end of sample array sound is not playing
	52,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd12",	// sample name

	Kd13,	// pointer to sample array
	Kd13_SIZE,	// size of the sample array
	Kd13_SIZE,	//sampleindex. if at end of sample array sound is not playing
	53,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd13",	// sample name

	Kd14,	// pointer to sample array
	Kd14_SIZE,	// size of the sample array
	Kd14_SIZE,	//sampleindex. if at end of sample array sound is not playing
	54,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd14",	// sample name

	Kd15,	// pointer to sample array
	Kd15_SIZE,	// size of the sample array
	Kd15_SIZE,	//sampleindex. if at end of sample array sound is not playing
	55,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd15",	// sample name

	Kd16,	// pointer to sample array
	Kd16_SIZE,	// size of the sample array
	Kd16_SIZE,	//sampleindex. if at end of sample array sound is not playing
	56,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd16",	// sample name

	Kd17,	// pointer to sample array
	Kd17_SIZE,	// size of the sample array
	Kd17_SIZE,	//sampleindex. if at end of sample array sound is not playing
	57,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd17",	// sample name

	Kd18,	// pointer to sample array
	Kd18_SIZE,	// size of the sample array
	Kd18_SIZE,	//sampleindex. if at end of sample array sound is not playing
	58,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd18",	// sample name

	Kd2,	// pointer to sample array
	Kd2_SIZE,	// size of the sample array
	Kd2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	59,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd2",	// sample name

	Kd3,	// pointer to sample array
	Kd3_SIZE,	// size of the sample array
	Kd3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	60,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd3",	// sample name

	Kd4,	// pointer to sample array
	Kd4_SIZE,	// size of the sample array
	Kd4_SIZE,	//sampleindex. if at end of sample array sound is not playing
	61,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd4",	// sample name

	Kd5,	// pointer to sample array
	Kd5_SIZE,	// size of the sample array
	Kd5_SIZE,	//sampleindex. if at end of sample array sound is not playing
	62,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd5",	// sample name

	Kd6,	// pointer to sample array
	Kd6_SIZE,	// size of the sample array
	Kd6_SIZE,	//sampleindex. if at end of sample array sound is not playing
	63,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd6",	// sample name

	Kd7,	// pointer to sample array
	Kd7_SIZE,	// size of the sample array
	Kd7_SIZE,	//sampleindex. if at end of sample array sound is not playing
	64,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd7",	// sample name

	Kd9,	// pointer to sample array
	Kd9_SIZE,	// size of the sample array
	Kd9_SIZE,	//sampleindex. if at end of sample array sound is not playing
	65,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Kd9",	// sample name

	Lt1,	// pointer to sample array
	Lt1_SIZE,	// size of the sample array
	Lt1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	66,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Lt1",	// sample name

	Lt2,	// pointer to sample array
	Lt2_SIZE,	// size of the sample array
	Lt2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	67,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Lt2",	// sample name

	Lt3,	// pointer to sample array
	Lt3_SIZE,	// size of the sample array
	Lt3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	68,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Lt3",	// sample name

	Mt1,	// pointer to sample array
	Mt1_SIZE,	// size of the sample array
	Mt1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	69,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Mt1",	// sample name

	Mt2,	// pointer to sample array
	Mt2_SIZE,	// size of the sample array
	Mt2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	70,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Mt2",	// sample name

	Mt3,	// pointer to sample array
	Mt3_SIZE,	// size of the sample array
	Mt3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	71,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Mt3",	// sample name

	Oh1,	// pointer to sample array
	Oh1_SIZE,	// size of the sample array
	Oh1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	72,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Oh1",	// sample name

	Oh2,	// pointer to sample array
	Oh2_SIZE,	// size of the sample array
	Oh2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	73,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Oh2",	// sample name

	Oh3,	// pointer to sample array
	Oh3_SIZE,	// size of the sample array
	Oh3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	74,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Oh3",	// sample name

	Rs1,	// pointer to sample array
	Rs1_SIZE,	// size of the sample array
	Rs1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	75,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Rs1",	// sample name

	Rs2,	// pointer to sample array
	Rs2_SIZE,	// size of the sample array
	Rs2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	76,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Rs2",	// sample name

	Rs3,	// pointer to sample array
	Rs3_SIZE,	// size of the sample array
	Rs3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	77,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Rs3",	// sample name

	Sn1,	// pointer to sample array
	Sn1_SIZE,	// size of the sample array
	Sn1_SIZE,	//sampleindex. if at end of sample array sound is not playing
	78,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Sn1",	// sample name

	Sn2,	// pointer to sample array
	Sn2_SIZE,	// size of the sample array
	Sn2_SIZE,	//sampleindex. if at end of sample array sound is not playing
	79,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Sn2",	// sample name

	Sn3,	// pointer to sample array
	Sn3_SIZE,	// size of the sample array
	Sn3_SIZE,	//sampleindex. if at end of sample array sound is not playing
	80,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Sn3",	// sample name

	Sn4,	// pointer to sample array
	Sn4_SIZE,	// size of the sample array
	Sn4_SIZE,	//sampleindex. if at end of sample array sound is not playing
	81,	// MIDI note on that plays this sample
	127,	// play volume 0-127
	"Sn4",	// sample name

};
