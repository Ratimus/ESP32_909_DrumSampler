#ifndef SAMPLEDEFS_909_H
#define SAMPLEDEFS_909_H

// sample structure built by wav2header based on wav2sketch by Paul Stoffregen
#include <Arduino.h>
#include "samples_909.h"

struct sample_t {
  const int16_t * samplearray; // pointer to sample array
  uint32_t samplesize; // size of the sample array
  char sname[20];        // sample name
} SAMPLE_BANK[] = {

	Ch1,	// pointer to sample array
	Ch1_SIZE,	// size of the sample array
	"Ch1",	// sample name

	Ch2,	// pointer to sample array
	Ch2_SIZE,	// size of the sample array
	"Ch2",	// sample name

	Ch3,	// pointer to sample array
	Ch3_SIZE,	// size of the sample array
	"Ch3",	// sample name

	Cp1,	// pointer to sample array
	Cp1_SIZE,	// size of the sample array
	"Cp1",	// sample name

	Cp2,	// pointer to sample array
	Cp2_SIZE,	// size of the sample array
	"Cp2",	// sample name

	Cp3,	// pointer to sample array
	Cp3_SIZE,	// size of the sample array
	"Cp3",	// sample name

	Cr1,	// pointer to sample array
	Cr1_SIZE,	// size of the sample array
	"Cr1",	// sample name

	Cr2,	// pointer to sample array
	Cr2_SIZE,	// size of the sample array
	"Cr2",	// sample name

	Cr3,	// pointer to sample array
	Cr3_SIZE,	// size of the sample array
	"Cr3",	// sample name

	Cy1,	// pointer to sample array
	Cy1_SIZE,	// size of the sample array
	"Cy1",	// sample name

	Cy2,	// pointer to sample array
	Cy2_SIZE,	// size of the sample array
	"Cy2",	// sample name

	Ht1,	// pointer to sample array
	Ht1_SIZE,	// size of the sample array
	"Ht1",	// sample name

	Ht2,	// pointer to sample array
	Ht2_SIZE,	// size of the sample array
	"Ht2",	// sample name

	Ht3,	// pointer to sample array
	Ht3_SIZE,	// size of the sample array
	"Ht3",	// sample name

	Kd1,	// pointer to sample array
	Kd1_SIZE,	// size of the sample array
	"Kd1",	// sample name

	Kd10,	// pointer to sample array
	Kd10_SIZE,	// size of the sample array
	"Kd10",	// sample name

	Kd11,	// pointer to sample array
	Kd11_SIZE,	// size of the sample array
	"Kd11",	// sample name

	Kd12,	// pointer to sample array
	Kd12_SIZE,	// size of the sample array
	"Kd12",	// sample name

	Kd13,	// pointer to sample array
	Kd13_SIZE,	// size of the sample array
	"Kd13",	// sample name

	Kd14,	// pointer to sample array
	Kd14_SIZE,	// size of the sample array
	"Kd14",	// sample name

	Kd15,	// pointer to sample array
	Kd15_SIZE,	// size of the sample array
	"Kd15",	// sample name

	Kd16,	// pointer to sample array
	Kd16_SIZE,	// size of the sample array
	"Kd16",	// sample name

	Kd17,	// pointer to sample array
	Kd17_SIZE,	// size of the sample array
	"Kd17",	// sample name

	Kd18,	// pointer to sample array
	Kd18_SIZE,	// size of the sample array
	"Kd18",	// sample name

	Kd2,	// pointer to sample array
	Kd2_SIZE,	// size of the sample array
	"Kd2",	// sample name

	Kd3,	// pointer to sample array
	Kd3_SIZE,	// size of the sample array
	"Kd3",	// sample name

	Kd4,	// pointer to sample array
	Kd4_SIZE,	// size of the sample array
	"Kd4",	// sample name

	Kd5,	// pointer to sample array
	Kd5_SIZE,	// size of the sample array
	"Kd5",	// sample name

	Kd6,	// pointer to sample array
	Kd6_SIZE,	// size of the sample array
	"Kd6",	// sample name

	Kd7,	// pointer to sample array
	Kd7_SIZE,	// size of the sample array
	"Kd7",	// sample name

	Kd9,	// pointer to sample array
	Kd9_SIZE,	// size of the sample array
	"Kd9",	// sample name

	Lt1,	// pointer to sample array
	Lt1_SIZE,	// size of the sample array
	"Lt1",	// sample name

	Lt2,	// pointer to sample array
	Lt2_SIZE,	// size of the sample array
	"Lt2",	// sample name

	Lt3,	// pointer to sample array
	Lt3_SIZE,	// size of the sample array
	"Lt3",	// sample name

	Mt1,	// pointer to sample array
	Mt1_SIZE,	// size of the sample array
	"Mt1",	// sample name

	Mt2,	// pointer to sample array
	Mt2_SIZE,	// size of the sample array
	"Mt2",	// sample name

	Mt3,	// pointer to sample array
	Mt3_SIZE,	// size of the sample array
	"Mt3",	// sample name

	Oh1,	// pointer to sample array
	Oh1_SIZE,	// size of the sample array
	"Oh1",	// sample name

	Oh2,	// pointer to sample array
	Oh2_SIZE,	// size of the sample array
	"Oh2",	// sample name

	Oh3,	// pointer to sample array
	Oh3_SIZE,	// size of the sample array
	"Oh3",	// sample name

	Rs1,	// pointer to sample array
	Rs1_SIZE,	// size of the sample array
	"Rs1",	// sample name

	Rs2,	// pointer to sample array
	Rs2_SIZE,	// size of the sample array
	"Rs2",	// sample name

	Rs3,	// pointer to sample array
	Rs3_SIZE,	// size of the sample array
	"Rs3",	// sample name

	Sn1,	// pointer to sample array
	Sn1_SIZE,	// size of the sample array
	"Sn1",	// sample name

	Sn2,	// pointer to sample array
	Sn2_SIZE,	// size of the sample array
	"Sn2",	// sample name

	Sn3,	// pointer to sample array
	Sn3_SIZE,	// size of the sample array
	"Sn3",	// sample name

	Sn4,	// pointer to sample array
	Sn4_SIZE,	// size of the sample array
	"Sn4",	// sample name
};


const uint16_t NUM_SAMPLES (sizeof(SAMPLE_BANK)/sizeof(sample_t));

#endif
