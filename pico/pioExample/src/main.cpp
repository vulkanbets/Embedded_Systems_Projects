#include <Arduino.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// My own personal Includes
#include "myPwm.hpp"

void setup()
{
  SetUpPinPwm();    // Set up all initial register values that the PWM uses
  SetPwmPinHigh();  // Set PWM Pin to Default (HIGH)
}

void loop()
{
  RunPinPwm();
  delay(500);
  SetPwmPinHigh();
  delay(500);
}
