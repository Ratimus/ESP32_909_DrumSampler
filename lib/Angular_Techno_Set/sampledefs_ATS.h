// sample structure built by wav2header based on wav2sketch by Paul Stoffregen
#pragma once
#include <Arduino.h>
#include "samples_ATS.h"

struct sample_t {
  const int16_t * samplearray; // pointer to sample array
  uint32_t samplesize; // size of the sample array
  char sname[20];        // sample name
} SAMPLE_BANK[] = {

	Ws05,	// pointer to sample array
	Ws05_SIZE,	// size of the sample array
	"Ws05",	// sample name

	Ws06,	// pointer to sample array
	Ws06_SIZE,	// size of the sample array
	"Ws06",	// sample name

	Ws09,	// pointer to sample array
	Ws09_SIZE,	// size of the sample array
	"Ws09",	// sample name

	Ws10,	// pointer to sample array
	Ws10_SIZE,	// size of the sample array
	"Ws10",	// sample name

	Ws13,	// pointer to sample array
	Ws13_SIZE,	// size of the sample array
	"Ws13",	// sample name

	Ws14,	// pointer to sample array
	Ws14_SIZE,	// size of the sample array
	"Ws14",	// sample name

	Ws16,	// pointer to sample array
	Ws16_SIZE,	// size of the sample array
	"Ws16",	// sample name

	Ws17,	// pointer to sample array
	Ws17_SIZE,	// size of the sample array
	"Ws17",	// sample name

	Ws18,	// pointer to sample array
	Ws18_SIZE,	// size of the sample array
	"Ws18",	// sample name

	Ws19,	// pointer to sample array
	Ws19_SIZE,	// size of the sample array
	"Ws19",	// sample name

	Ws20,	// pointer to sample array
	Ws20_SIZE,	// size of the sample array
	"Ws20",	// sample name

	Ws21,	// pointer to sample array
	Ws21_SIZE,	// size of the sample array
	"Ws21",	// sample name

	Ws22,	// pointer to sample array
	Ws22_SIZE,	// size of the sample array
	"Ws22",	// sample name

	Ws23,	// pointer to sample array
	Ws23_SIZE,	// size of the sample array
	"Ws23",	// sample name

	Ws24,	// pointer to sample array
	Ws24_SIZE,	// size of the sample array
	"Ws24",	// sample name

	Ws25,	// pointer to sample array
	Ws25_SIZE,	// size of the sample array
	"Ws25",	// sample name

	Ws30,	// pointer to sample array
	Ws30_SIZE,	// size of the sample array
	"Ws30",	// sample name

	Ws31,	// pointer to sample array
	Ws31_SIZE,	// size of the sample array
	"Ws31",	// sample name

	Ws32,	// pointer to sample array
	Ws32_SIZE,	// size of the sample array
	"Ws32",	// sample name

	Ws34,	// pointer to sample array
	Ws34_SIZE,	// size of the sample array
	"Ws34",	// sample name

	Ws36,	// pointer to sample array
	Ws36_SIZE,	// size of the sample array
	"Ws36",	// sample name

	Ws37,	// pointer to sample array
	Ws37_SIZE,	// size of the sample array
	"Ws37",	// sample name

	Ws38,	// pointer to sample array
	Ws38_SIZE,	// size of the sample array
	"Ws38",	// sample name

	Ws39,	// pointer to sample array
	Ws39_SIZE,	// size of the sample array
	"Ws39",	// sample name

	Ws42,	// pointer to sample array
	Ws42_SIZE,	// size of the sample array
	"Ws42",	// sample name

	Ws44,	// pointer to sample array
	Ws44_SIZE,	// size of the sample array
	"Ws44",	// sample name

	Ws45,	// pointer to sample array
	Ws45_SIZE,	// size of the sample array
	"Ws45",	// sample name

	Ws51,	// pointer to sample array
	Ws51_SIZE,	// size of the sample array
	"Ws51",	// sample name

	Ws56,	// pointer to sample array
	Ws56_SIZE,	// size of the sample array
	"Ws56",	// sample name

	Ws57,	// pointer to sample array
	Ws57_SIZE,	// size of the sample array
	"Ws57",	// sample name

	Ws59,	// pointer to sample array
	Ws59_SIZE,	// size of the sample array
	"Ws59",	// sample name

	Ws60,	// pointer to sample array
	Ws60_SIZE,	// size of the sample array
	"Ws60",	// sample name
};

const uint16_t NUM_SAMPLES (sizeof(SAMPLE_BANK)/sizeof(sample_t));
