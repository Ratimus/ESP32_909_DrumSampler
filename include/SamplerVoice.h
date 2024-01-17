
// Copyright 2023 Ryan Richardson
//
// Author: Ratimus
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
#pragma once

#include <Arduino.h>
#include "Latchable.h"

// #include <sampledefs_909.h>     // 909
// #include <sampledefs_808.h>  // 808
// #include <sampledefs_wsa.h>  // WSA1 soundfont set
// #include <sampledefs_AJS.h>  // Jungle soundfont set
#include <sampledefs_ATS.h>  // Techno

enum CV_MODE
{
  NONE,
  VOLUME,
  SAMPLE,
  DECAY,
  PITCH
};


const uint8_t NUM_VOICES(4);
class Voice
{
public:
  Voice():
    mix(0),
    choke(0),
    decay(0),
    level(0),
    pitch(0),
    sample(0),
    cv_mode(0),
    envShape(0),
    envDecay(0),
    pitchScalar(0),
    sampleindex(-1),
    sampleOffset(0),
    pSample(nullptr),
    oneOverSampleRate(1.0f / 22000.0f)
  {
    pSample = &SAMPLE_BANK[sample.Q];
  }

  float getSample()
  {
    // Interpolate between the current sample and the next one as a function of hypothetical
    // sample rate necessary to play at a given pitch versus the current sample rate (yeah,
    // I get that makes no sense; just read the code)
    uint32_t sampleindex_int = static_cast<int32_t>(sampleindex);
    float   sampleindex_frac = sampleindex - sampleindex_int;

    int16_t sampleA(pSample->samplearray[sampleindex_int]);
    int16_t sampleB(pSample->samplearray[sampleindex_int  + 1]);

    sampleindex += sampleindexFactor;

    // Get the sample val, and the interpolation
    return float((float)sampleA + (float)(sampleB - sampleA) * sampleindex_frac);
  }


  void overdriveProcess(float *bvf)
  {
    // Overdrive algorithm:
    // y = x(1 - e^-|x|) / |x|
    float fac(32768.0);
    *bvf /= fac;
    if (bvf > 0)
    {
      *bvf = 1 - exp(-*bvf);
    }
    else
    {
     *bvf = -1 + exp(*bvf);
    }

    *bvf *= fac;
  }

  uint16_t scaleOutput(float * bvf)
  {
    // Apply foldback distortion instead of clipping
    int32_t buffVal(*bvf);
    if (buffVal < -32768)
    {
      buffVal = -32768 + (buffVal + 32768);
    }
    else if (buffVal > 32767)
    {
      buffVal = 32767 - (buffVal - 32767);
    }
    buffVal += 32768;

    return uint16_t(buffVal >> 4);
  }

  void tick(uint16_t * pVal)
  {
    // If we've played the whole sample, reset it and bail.
    if (sampleindex >= pSample->samplesize || sampleindex < 0.0f)
    {
      *pVal = 2048;
      return;
    }

    // Get the sample val, add the interpolation
    float bvf(getSample());

    // Apply linear envelope if applicable
    if (shape < 5)
    {
      nextEnvFactor = (1.0f - (sampleindex * envelopeScaler));
    }

    if (nextEnvFactor < 0.00001f)
    {
      sampleindex = -1.0f;
      *pVal = 2048;
      return;
    }

    // Scale sample value by the mix level and apply decay envelope
    bvf *= level;
    bvf *= nextEnvFactor;

    // Get next exponential value if applicable
    if (shape >= 5)
    {
      nextEnvFactor *= envelopeScaler;
    }

    // Apply soft clipping
    overdriveProcess(&bvf);

    // Convert our value from 16 bits signed to 12 bits unsigned
    *pVal = scaleOutput(&bvf);
  }

  // Starts playing a sample
  bool start(uint16_t CV_in)
  {
    level         = (float)mix.clock();
    shape         = envShape.clock();
    envDecay      = (float)decay.clock();
    pitchScalar   = (float)pitch.clock();
    sampleOffset  = sample.clock();

    int32_t cvSquared;
    int32_t cv32;

    float   cvFloat(CV_in);
    float   cvScalar;

    // Do some modulation stuff
    switch (cv_mode.clock())
    {
      case VOLUME:
        cv32      = (int32_t)CV_in - 2048;
        cvSquared = cv32 * cv32;
        if (cv32 < 0)
        {
          cvSquared *= -1;
        }

        cvScalar = ((float)cvSquared / (float)0x3FF001);  // 0x3FF001 == 2047 * 2047
        level   += 100.0f * cvScalar;
        if (level < 0.0)
        {
          level = 0.0;
        }
        break;

      case SAMPLE:
        sampleOffset += CV_in * NUM_SAMPLES / 4095;
        if (sampleOffset >= NUM_SAMPLES)
        {
          sampleOffset -= NUM_SAMPLES;
        }
        break;

      case DECAY:
        envDecay += 100 * (cvFloat - 2048.0f) / 2047.0f;
        break;

      case PITCH:
        cv32  = (int32_t)CV_in - 2048;
        cv32 *= 96;
        pitchScalar += (float)cv32 / 4095.0f;
        break;

      case NONE:
        break;

      default:
        cv_mode.clockIn(NONE);  // if its messed up fix it
        break;
    }

    pSample           = &SAMPLE_BANK[sampleOffset];
    pitchScalar       = pow(2.0f, pitchScalar / 96.0f);
    sampleindex       = 0.0f;
    nextEnvFactor     = 1.0f;
    sampleindexFactor = pitchScalar;

    // Shape 0: no envelope
    // Shape 1: linear envelope, 25%
    // Shape 2: linear envelope, 50%
    // Shape 3: linear envelope, 75%
    // Shape 4: linear envelope, 100%
    // Shape 5: exponential envelope
    // Shape 6: snappier exponential envelope
    level /= 100.0f;

    if (envDecay > 100.0f)
    {
      envDecay = 100.0f;
    }
    envDecay /= 100.0f;
    envDecay *= pSample->samplesize;
    envDecay *= oneOverSampleRate;
    envDecay /= sampleindexFactor;

    if (shape >= 5)
    {
      float oneOverA(exp(-1.0f / envDecay));
      envelopeScaler = pow(oneOverA, oneOverSampleRate);
      if (shape == 6)
      {
        envelopeScaler *= envelopeScaler;
      }
    }
    else
    {
      envelopeScaler = shape / (4.0f * envDecay * 22000.0f);
    }

    return choke.clock();
  }

  void stop()
  {
    sampleindex = -1;
  }

  void setDefaults(
    uint8_t sp,
    uint8_t mx,
    uint8_t dc,
    int8_t  pt,
    uint8_t cv,
    uint8_t shape,
    bool ch)
  {
    sample.preEnable(sp);
    mix.preEnable(mx);
    decay.preEnable(dc);
    pitch.preEnable(pt);
    cv_mode.preEnable(cv);
    envShape.preEnable(shape);
    choke.preEnable(ch);
    resetToDefaults();
  }

  void resetToDefaults()
  {
    sample.reset();
    mix.reset();
    decay.reset();
    pitch.reset();
    cv_mode.reset();
    envShape.reset();
    choke.reset();
    pSample = &SAMPLE_BANK[sample.Q];
  }

  latchable<bool>     choke;
  latchable<uint8_t>  mix;
  latchable<int8_t>   pitch;
  latchable<uint8_t>  decay;
  latchable<uint8_t>  sample;
  latchable<uint8_t>  cv_mode;
  latchable<uint8_t>  envShape;
  float               level;
  float               shape;
  float               envDecay;
  int32_t             buffVal;
  float               pitchScalar;
  float               sampleindex;
  sample_t           *pSample;
  uint8_t             sampleOffset;
  float               sampleindexFactor;
  float               nextEnvFactor;
  float               envelopeScaler;
  const float         oneOverSampleRate;
} voice[NUM_VOICES];
