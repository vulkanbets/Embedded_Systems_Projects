#include <Arduino.h>

// Configuration parameters
const int ledcChannel = 0; // LEDC channel to use
const int gpioPin = 23;    // GPIO pin to output the 200kHz signal
const int freq = 200000;   // Desired frequency (200kHz)
const int resolution = 8;  // Resolution of the duty cycle (8 bits)

void setup()
{
  // Set up the LEDC peripheral
  ledcSetup(ledcChannel, freq, resolution);

  // Attach the LEDC channel to the GPIO pin
  ledcAttachPin(gpioPin, ledcChannel);

  // Set the duty cycle (0 to 255 for 8-bit resolution)
  // 128 is 50% duty cycle, adjust as needed
  ledcWrite(ledcChannel, 128);
}

void loop()
{
  // The clock signal will run continuously without any code in the loop
}
