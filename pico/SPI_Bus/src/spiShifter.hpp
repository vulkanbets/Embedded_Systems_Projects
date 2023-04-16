#ifndef SPI_SHIFTER_HPP
#define SPI_SHIFTER_HPP

// This Macro must be changed every time the frequency of PWM changes
#define WAIT_COUNTER 36

volatile char volatileTimer = 0;

// Define the GPIO pin number for the MOSI signal
const uint mosi_pin = 16;

void SendSpiByte(char byteParam)
{
  // <-- Start PWM SCK Signal on PIN "pwm_pin"
  pwm_set_enabled(slice_num, true);

  // Send each corresponding BIT in the char byte
  for (unsigned int byteCounter = 0; byteCounter < 8; byteCounter++)
  {
    // While SCK is HIGH Wait until SCK goes LOW
    while( gpio_get(pwm_pin) ) {
      tight_loop_contents();
    }

    // Set MOSI line to corresponding bit
    digitalWrite(mosi_pin, byteParam & (1 << byteCounter));

    // While SCK is LOW Wait until SCK goes HIGH
    while( !gpio_get(pwm_pin) ) {
      tight_loop_contents();
    }
    
    if(byteCounter == 7) {
      // After PWM is HIGH -> De-activate SCK Signal on PIN "pwm_pin"
      pwm_set_enabled(slice_num, false);

      // Custom delay (HACK) for final Bit sent in a Byte
      for (unsigned int i = 0; i < WAIT_COUNTER; i++) {
        volatileTimer = volatileTimer + i;
      }

      digitalWrite(mosi_pin, HIGH); // <-- Reset MOSI line to High (Default)
      
      break;
    }
  }

  // Custom delay (HACK) loop. Buffer a few clock cycles before next SPI packet is sent.
  for (unsigned int i = 0; i < 140; i++) {
    volatileTimer = volatileTimer + i;
  }

  return;
}


void BroadcastSpiTransmission(char *buf, unsigned int frameLength)
{
  for (unsigned int i = 0; i < frameLength - 7; i++)
  {
    // Determine if end of transmission.  Exit from Broadcast function if true
    if( buf[i] == '\x03' && buf[i+1] == '\x04' && buf[i+2] == '\x06' && buf[i+3] == '\x00' ) {
      return;
    }

    SendSpiByte( buf[i] );
  }
}


void SetMemoryToNull(char *buf, unsigned int frameLength)
{
  for (unsigned int i = 0; i < frameLength - 1; i++) {
    buf[i] = '\0';
  }
}


#endif // SPI_SHIFTER_HPP