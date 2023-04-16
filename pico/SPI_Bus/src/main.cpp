#include <Arduino.h>
#include <string.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// My own personal Includes
#include "myPwm.hpp"
#include "spiShifter.hpp"

// My Macros
#define SPI_FRAME_LENGTH 1024U

// Define the GPIO pin number for the Chip Select signal
const uint chp_select_pin = 15;

// Define the GPIO pin number for the Data signal
const uint data_pin = 16;

// Final 4 bytes are padded with special chars to indicate end of transmission
// '(End Of Text)'-'(End Of Transmission)'-'(Acknowledge)'-'NULL'
const char *spi_Message = "Hello, World!!!\x03\x04\x06\x00";

// Buffer holds ASCII text message sent through Serial SPI
char spiMessageBuffer[SPI_FRAME_LENGTH];

void setup()
{
  SetMemoryToNull(spiMessageBuffer, SPI_FRAME_LENGTH);

  // Safer: Copy the string literal into the buffer
  strncpy(spiMessageBuffer, spi_Message, sizeof(spiMessageBuffer) - 1);

  // Manually null-terminate the string if strncpy didn't do it
  spiMessageBuffer[sizeof(spiMessageBuffer) - 1] = '\0';

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
  delay(1);

  // Set the chp_select_pin to LOW. BEGIN sending serial data
  digitalWrite(chp_select_pin, LOW);

  // Start SCK Clock ticks on the pwm line (Pin 14)
  StartPwmSckClock();

  BroadcastSpiTransmission(spiMessageBuffer, SPI_FRAME_LENGTH);

  ResetPwmSckClock(); // <-- Reset PWM pin to HIGH, Default is HIGH

  // Set the chp_select_pin to HIGH. STOP sending serial data
  digitalWrite(chp_select_pin, HIGH);
}
