#ifndef DIRECT_IO_AITCH
#define DIRECT_IO_AITCH

#include "Arduino.h"

static inline __attribute__((always_inline))
void directWriteLow(uint32_t pin)
{
  if ( pin < 32 )
      GPIO.out_w1tc = ((uint32_t)1 << pin);
  else if ( pin < 34 )
    GPIO.out1_w1tc.val = ((uint32_t)1 << (pin - 32));
}

static inline __attribute__((always_inline))
void directWriteHigh(uint32_t pin)
{
  if ( pin < 32 )
    GPIO.out_w1ts = ((uint32_t)1 << pin);
  else if ( pin < 34 )
    GPIO.out1_w1ts.val = ((uint32_t)1 << (pin - 32));
}


static inline __attribute__((always_inline))
uint32_t directRead(uint32_t pin)
{
    if ( pin < 32 )
        return (GPIO.in >> pin) & 0x1;
    else if ( pin < 40 )
        return (GPIO.in1.val >> (pin - 32)) & 0x1;

    return 0;
}


#endif
