#include <Arduino.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// My own personal Includes
#include "myPwm.hpp"

// Define the GPIO pin number for the Chip Select signal
const uint chp_select_pin = 15;

// Define the GPIO pin number for the Data signal
const uint data_pin = 16;

void setup()
{
  // Set chp_select_pin & data_pin pins as an outputs.
  pinMode(chp_select_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  // Set the chp_select_pin & data_pin to HIGH.
  // Active Low chip select pin.  Data pin idles on HIGH
  digitalWrite(chp_select_pin, HIGH);
  digitalWrite(data_pin, HIGH);

  SetUpPinPwm();    // Set up all initial register values that the SCK PWM uses
  ResetPwmSckClock();  // Set SCK PWM Pin to Default (HIGH)
}

void loop()
{
  delay(1); // <-- This delay IS needed

  // Set the chp_select_pin to LOW. BEGIN sending serial data
  digitalWrite(chp_select_pin, LOW);

  // Start SCK Clock ticks on the pwm line (Pin 14)
  StartPwmSckClock();

  // This delay is not needed and will be replaced & determined by
  delay(1); // <-- the amount of time needed to send the data through the wire

  ResetPwmSckClock(); // <-- Reset PWM pin to HIGH, Default is HIGH

  // Set the chp_select_pin to HIGH. STOP sending serial data
  digitalWrite(chp_select_pin, HIGH);
}
