#include <Arduino.h>

// Set LED_BUILTIN if undefined or not pin 13
#define LED_BUILTIN 2

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(500); // wait for a half-second

  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(500); // wait for a half-second
}
