#include <Arduino.h>

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(250); // wait

  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(250); // wait
}
