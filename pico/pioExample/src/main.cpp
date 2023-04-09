#include <Arduino.h>
#include "pico/time.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

volatile unsigned long nopVar = 0;

// My Macros
#define One_Hz 20833332   // Rough approximation => (125 MHz / 6 instrcutions) = 20833332 = 1Hz (cycles/second)
#define One_KHz 10417     // <-- This number was found empirically through testing with oscilloscope
#define Ten_KHz 425       // <-- This number was found empirically through testing with oscilloscope

// Define Pins
#define PIN_GP17 (17u)

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PIN_GP17, OUTPUT);
}

void loop()
{
  digitalWrite(PIN_GP17, HIGH); // turn the PIN on (HIGH is the voltage level)

  // There is some overhead associated with this manual wait. After
  // some testing I have come to the conclusion that there are
  // approxiomately 6 instructions that each loop iteration executes
  for (unsigned long i = 0; i < Ten_KHz; i++)
  {
    nopVar << 0;
  }

  digitalWrite(PIN_GP17, LOW); // turn the PIN off by making the voltage LOW

  // There is some overhead associated with this manual wait. After
  // some testing I have come to the conclusion that there are
  // approxiomately 6 instructions that each loop iteration executes
  for (unsigned long i = 0; i < Ten_KHz; i++)
  {
    nopVar << 0;
  }
}
