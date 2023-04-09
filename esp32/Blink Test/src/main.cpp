#include <Arduino.h>

void setup()
{
  // initialize digital pin GPIO2 as an output.
  pinMode(GPIO_NUM_2, OUTPUT);
  
  // Initialize Serial communication at 9600 BAUD
  Serial.begin(9600);
}

// Char buffer for sending messages
char spiMessageSent[4096];

void loop()
{
  digitalWrite(GPIO_NUM_2, HIGH); // turn the LED on (HIGH is the voltage level)

  // Write string message to char buffer and add "NULL" byte terminator
  strncpy( spiMessageSent, "ESP32 Serial Monitor Message Sent Successfully!\n\0", sizeof(spiMessageSent) );

  // Send Serial Monitor message
  Serial.print(spiMessageSent);
  
  delay(1000); // wait for a half-second

  digitalWrite(GPIO_NUM_2, LOW); // turn the LED off by making the voltage LOW
  delay(1000); // wait for a half-second
}
