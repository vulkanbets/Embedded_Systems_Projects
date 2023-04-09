#include <Arduino.h>

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize Serial communication at 9600 BAUD
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(500); // wait for a half-second

  // Send UART message
  Serial.print("UART Message Sent!\n");

  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(500); // wait for a half-second
}
