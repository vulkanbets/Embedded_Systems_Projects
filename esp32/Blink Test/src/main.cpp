#include <Arduino.h>

char spiMessageSent[8192];  // Global Char buffer for storing received SPI messages

void setup()
{
  // Initialize Serial communication at 9600 BAUD
  Serial.begin(9600);
}

void loop()
{
  // Write string message to char buffer and add "NULL" byte terminator
  strncpy( spiMessageSent, "ESP32 Serial Monitor Message Sent Successfully!\n\0\0", sizeof(spiMessageSent) );

  // If anything has been written to the buffer; Send Serial Monitor message
  if( spiMessageSent[0] != '\0' && spiMessageSent[1] != '\0' )
  {
    Serial.print(spiMessageSent);
  }

  // My way of Resetting the buffer to null (efficiently) without using memset, which
  // might be computationally expensive on the 32-bit RISC based Xtensa LX7 ESP32 CPU
  spiMessageSent[0] = '\0';
  spiMessageSent[1] = '\0';
  spiMessageSent[2] = '\0';

  delay(1000); // wait for a Second
}
