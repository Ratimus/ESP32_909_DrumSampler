#ifndef SAMPLES_808_H
#define SAMPLES_808_H

// sample structure built by wav2header based on wav2sketch by Paul Stoffregen
#include <Arduino.h>
#include "samples_808.h"

struct sample_t {
  const int16_t * samplearray; // pointer to sample array
  uint32_t samplesize; // size of the sample array
  char sname[20];        // sample name
} SAMPLE_BANK[] = {

	Bd0000,	// pointer to sample array
	Bd0000_SIZE,	// size of the sample array
	"Bd0000",	// sample name

	Bd1000,	// pointer to sample array
	Bd1000_SIZE,	// size of the sample array
	"Bd1000",	// sample name

	Bd2550,	// pointer to sample array
	Bd2550_SIZE,	// size of the sample array
	"Bd2550",	// sample name

	Cb,	// pointer to sample array
	Cb_SIZE,	// size of the sample array
	"Cb",	// sample name

	Ch,	// pointer to sample array
	Ch_SIZE,	// size of the sample array
	"Ch",	// sample name

	Cl,	// pointer to sample array
	Cl_SIZE,	// size of the sample array
	"Cl",	// sample name

	Cp,	// pointer to sample array
	Cp_SIZE,	// size of the sample array
	"Cp",	// sample name

	Cy0000,	// pointer to sample array
	Cy0000_SIZE,	// size of the sample array
	"Cy0000",	// sample name

	Cy0025,	// pointer to sample array
	Cy0025_SIZE,	// size of the sample array
	"Cy0025",	// sample name

	Cy1000,	// pointer to sample array
	Cy1000_SIZE,	// size of the sample array
	"Cy1000",	// sample name

	Cy1025,	// pointer to sample array
	Cy1025_SIZE,	// size of the sample array
	"Cy1025",	// sample name

	Cy7525,	// pointer to sample array
	Cy7525_SIZE,	// size of the sample array
	"Cy7525",	// sample name

	Hc00,	// pointer to sample array
	Hc00_SIZE,	// size of the sample array
	"Hc00",	// sample name

	Hc10,	// pointer to sample array
	Hc10_SIZE,	// size of the sample array
	"Hc10",	// sample name

	Hc25,	// pointer to sample array
	Hc25_SIZE,	// size of the sample array
	"Hc25",	// sample name

	Hc50,	// pointer to sample array
	Hc50_SIZE,	// size of the sample array
	"Hc50",	// sample name

	Hc75,	// pointer to sample array
	Hc75_SIZE,	// size of the sample array
	"Hc75",	// sample name

	Ht00,	// pointer to sample array
	Ht00_SIZE,	// size of the sample array
	"Ht00",	// sample name

	Ht10,	// pointer to sample array
	Ht10_SIZE,	// size of the sample array
	"Ht10",	// sample name

	Ht25,	// pointer to sample array
	Ht25_SIZE,	// size of the sample array
	"Ht25",	// sample name

	Ht50,	// pointer to sample array
	Ht50_SIZE,	// size of the sample array
	"Ht50",	// sample name

	Ht75,	// pointer to sample array
	Ht75_SIZE,	// size of the sample array
	"Ht75",	// sample name

	Lc00,	// pointer to sample array
	Lc00_SIZE,	// size of the sample array
	"Lc00",	// sample name

	Lc10,	// pointer to sample array
	Lc10_SIZE,	// size of the sample array
	"Lc10",	// sample name

	Lc25,	// pointer to sample array
	Lc25_SIZE,	// size of the sample array
	"Lc25",	// sample name

	Lc50,	// pointer to sample array
	Lc50_SIZE,	// size of the sample array
	"Lc50",	// sample name

	Lc75,	// pointer to sample array
	Lc75_SIZE,	// size of the sample array
	"Lc75",	// sample name

	Lt00,	// pointer to sample array
	Lt00_SIZE,	// size of the sample array
	"Lt00",	// sample name

	Lt10,	// pointer to sample array
	Lt10_SIZE,	// size of the sample array
	"Lt10",	// sample name

	Lt25,	// pointer to sample array
	Lt25_SIZE,	// size of the sample array
	"Lt25",	// sample name

	Lt50,	// pointer to sample array
	Lt50_SIZE,	// size of the sample array
	"Lt50",	// sample name

	Lt75,	// pointer to sample array
	Lt75_SIZE,	// size of the sample array
	"Lt75",	// sample name

	Ma,	// pointer to sample array
	Ma_SIZE,	// size of the sample array
	"Ma",	// sample name

	Mt00,	// pointer to sample array
	Mt00_SIZE,	// size of the sample array
	"Mt00",	// sample name

	Mt10,	// pointer to sample array
	Mt10_SIZE,	// size of the sample array
	"Mt10",	// sample name

	Mt25,	// pointer to sample array
	Mt25_SIZE,	// size of the sample array
	"Mt25",	// sample name

	Mt50,	// pointer to sample array
	Mt50_SIZE,	// size of the sample array
	"Mt50",	// sample name

	Mt75,	// pointer to sample array
	Mt75_SIZE,	// size of the sample array
	"Mt75",	// sample name

	Oh00,	// pointer to sample array
	Oh00_SIZE,	// size of the sample array
	"Oh00",	// sample name

	Oh10,	// pointer to sample array
	Oh10_SIZE,	// size of the sample array
	"Oh10",	// sample name

	Oh25,	// pointer to sample array
	Oh25_SIZE,	// size of the sample array
	"Oh25",	// sample name

	Oh50,	// pointer to sample array
	Oh50_SIZE,	// size of the sample array
	"Oh50",	// sample name

	Oh75,	// pointer to sample array
	Oh75_SIZE,	// size of the sample array
	"Oh75",	// sample name

	Rs,	// pointer to sample array
	Rs_SIZE,	// size of the sample array
	"Rs",	// sample name

	Sd0000,	// pointer to sample array
	Sd0000_SIZE,	// size of the sample array
	"Sd0000",	// sample name

	Sd0010,	// pointer to sample array
	Sd0010_SIZE,	// size of the sample array
	"Sd0010",	// sample name

	Sd0025,	// pointer to sample array
	Sd0025_SIZE,	// size of the sample array
	"Sd0025",	// sample name

	Sd0050,	// pointer to sample array
	Sd0050_SIZE,	// size of the sample array
	"Sd0050",	// sample name

	Sd7525,	// pointer to sample array
	Sd7525_SIZE,	// size of the sample array
	"Sd7525",	// sample name

	Sd7550,	// pointer to sample array
	Sd7550_SIZE,	// size of the sample array
	"Sd7550",	// sample name

	Sd7575,	// pointer to sample array
	Sd7575_SIZE,	// size of the sample array
	"Sd7575",	// sample name
};

const uint16_t NUM_SAMPLES (sizeof(SAMPLE_BANK)/sizeof(sample_t));

#endif