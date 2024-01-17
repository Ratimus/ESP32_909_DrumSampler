#pragma once
// sample structure built by wav2header based on wav2sketch by Paul Stoffregen
#include <Arduino.h>
#include "samples_AJS.h"

struct sample_t {
  const int16_t * samplearray; // pointer to sample array
  uint32_t samplesize; // size of the sample array
  char sname[20];        // sample name
} SAMPLE_BANK[] = {
	Ws02,	// pointer to sample array
	Ws02_SIZE,	// size of the sample array
	"Ws02",	// sample name

	Ws03,	// pointer to sample array
	Ws03_SIZE,	// size of the sample array
	"Ws03",	// sample name

	Ws04,	// pointer to sample array
	Ws04_SIZE,	// size of the sample array
	"Ws04",	// sample name

	Ws05,	// pointer to sample array
	Ws05_SIZE,	// size of the sample array
	"Ws05",	// sample name

	Ws06,	// pointer to sample array
	Ws06_SIZE,	// size of the sample array
	"Ws06",	// sample name

	Ws08,	// pointer to sample array
	Ws08_SIZE,	// size of the sample array
	"Ws08",	// sample name

	Ws09,	// pointer to sample array
	Ws09_SIZE,	// size of the sample array
	"Ws09",	// sample name

	Ws10,	// pointer to sample array
	Ws10_SIZE,	// size of the sample array
	"Ws10",	// sample name

	Ws11,	// pointer to sample array
	Ws11_SIZE,	// size of the sample array
	"Ws11",	// sample name

	Ws12,	// pointer to sample array
	Ws12_SIZE,	// size of the sample array
	"Ws12",	// sample name

	Ws13,	// pointer to sample array
	Ws13_SIZE,	// size of the sample array
	"Ws13",	// sample name

	Ws14,	// pointer to sample array
	Ws14_SIZE,	// size of the sample array
	"Ws14",	// sample name

	Ws15,	// pointer to sample array
	Ws15_SIZE,	// size of the sample array
	"Ws15",	// sample name

	Ws16,	// pointer to sample array
	Ws16_SIZE,	// size of the sample array
	"Ws16",	// sample name

	Ws18,	// pointer to sample array
	Ws18_SIZE,	// size of the sample array
	"Ws18",	// sample name

	Ws21,	// pointer to sample array
	Ws21_SIZE,	// size of the sample array
	"Ws21",	// sample name

	Ws22,	// pointer to sample array
	Ws22_SIZE,	// size of the sample array
	"Ws22",	// sample name

	Ws23,	// pointer to sample array
	Ws23_SIZE,	// size of the sample array
	"Ws23",	// sample name

	Ws28,	// pointer to sample array
	Ws28_SIZE,	// size of the sample array
	"Ws28",	// sample name

	Ws30,	// pointer to sample array
	Ws30_SIZE,	// size of the sample array
	"Ws30",	// sample name

	Ws31,	// pointer to sample array
	Ws31_SIZE,	// size of the sample array
	"Ws31",	// sample name

	Ws32,	// pointer to sample array
	Ws32_SIZE,	// size of the sample array
	"Ws32",	// sample name

	Ws33,	// pointer to sample array
	Ws33_SIZE,	// size of the sample array
	"Ws33",	// sample name

	Ws35,	// pointer to sample array
	Ws35_SIZE,	// size of the sample array
	"Ws35",	// sample name

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

	Ws40,	// pointer to sample array
	Ws40_SIZE,	// size of the sample array
	"Ws40",	// sample name

	Ws41,	// pointer to sample array
	Ws41_SIZE,	// size of the sample array
	"Ws41",	// sample name

	Ws42,	// pointer to sample array
	Ws42_SIZE,	// size of the sample array
	"Ws42",	// sample name

	Ws43,	// pointer to sample array
	Ws43_SIZE,	// size of the sample array
	"Ws43",	// sample name

	Ws47,	// pointer to sample array
	Ws47_SIZE,	// size of the sample array
	"Ws47",	// sample name

	Ws49,	// pointer to sample array
	Ws49_SIZE,	// size of the sample array
	"Ws49",	// sample name

	Ws51,	// pointer to sample array
	Ws51_SIZE,	// size of the sample array
	"Ws51",	// sample name

	Ws53,	// pointer to sample array
	Ws53_SIZE,	// size of the sample array
	"Ws53",	// sample name

	Ws55,	// pointer to sample array
	Ws55_SIZE,	// size of the sample array
	"Ws55",	// sample name

	Ws58,	// pointer to sample array
	Ws58_SIZE,	// size of the sample array
	"Ws58",	// sample name
};

const uint16_t NUM_SAMPLES (sizeof(SAMPLE_BANK)/sizeof(sample_t));
