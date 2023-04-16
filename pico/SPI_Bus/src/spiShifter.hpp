#ifndef SPI_SHIFTER_HPP
#define SPI_SHIFTER_HPP


char byteToSend;

// Define the GPIO pin number for the MOSI signal
const uint mosi_pin = 16;

// Individual bits sent though MOSI SPI line
unsigned int bitToSend;


void SendSpiByte()
{
  // 'S' is just a test case
  byteToSend = 'S';
  byteToSend = ~byteToSend;

  // While pwm_pin is HIGH Wait until pwm_pin goes LOW
  while( gpio_get(pwm_pin) ) {
    tight_loop_contents();
  }

  // Send each corresponding BIT in the char byte
  for (unsigned int byteCounter = 0; byteCounter < 8; byteCounter++)
  {
    bitToSend = byteToSend & (1 << byteCounter);

    digitalWrite(mosi_pin, bitToSend); // Set MOSI line to corresponding bit

    // While SCK is LOW Wait until SCK goes HIGH
    while( !gpio_get(pwm_pin) ) {
      tight_loop_contents();
    }
    // While SCK is HIGH Wait until SCK goes LOW
    while( gpio_get(pwm_pin) ) {
      tight_loop_contents();
    }
    if(byteCounter == 7) {
      digitalWrite(mosi_pin, HIGH); // <-- Reset MOSI line to High (Default)
      return;
    }
  }

  return;
}


void BroadcastSpiTransmission(char *buf, unsigned int frameLength)
{
  // for (unsigned int i = 0; i < frameLength - 7; i++)
  // {
  //   // Determine if end of transmission.  Exit from Broadcast function if true
  //   if( buf[i] == '\x03' && buf[i+1] == '\x04' && buf[i+2] == '\x06' && buf[i+3] == '\x00' ) {
  //     ResetPwmSckClock();     // <-- Reset PWM pin to HIGH, Default is HIGH
  //     digitalWrite(mosi_pin, HIGH); // <-- Reset MOSI line to High (Default)
  //     return;
  //   }

  //   // TODO: change this to buf[i] <> 'S' is just a test case
  //   byteToSend = 'S';

  //   // Start SCK Clock ticks on the pwm line (Pin 14)
  //   StartPwmSckClock();

  //   // While pwm_pin is HIGH Wait until pwm_pin goes LOW
  //   while( gpio_get(pwm_pin) ) {
  //     tight_loop_contents();
  //   }

  //   // Send each corresponding BIT in the char byte
  //   for (unsigned int byteCounter = 0; byteCounter < 8; byteCounter++)
  //   {
  //     bitToSend = byteToSend & (1 << byteCounter);

  //     digitalWrite(mosi_pin, bitToSend); // Set MOSI line to corresponding bit

  //     // While pwm_pin is LOW Wait until pwm_pin goes HIGH
  //     while( !gpio_get(pwm_pin) ) {
  //       tight_loop_contents();
  //     }
  //     // While pwm_pin is HIGH Wait until pwm_pin goes LOW
  //     while( gpio_get(pwm_pin) ) {
  //       tight_loop_contents();
  //     }
      
  //   }

  //   ResetPwmSckClock(); // <-- Reset PWM pin to HIGH, Default is HIGH

  //   digitalWrite(mosi_pin, HIGH); // <-- Reset MOSI line to High (Default)
  // }

  // digitalWrite(mosi_pin, HIGH); // <-- Reset MOSI line to High (Default)
}


void SetMemoryToNull(char *buf, unsigned int frameLength)
{
  for (unsigned int i = 0; i < frameLength - 1; i++) {
    buf[i] = '\0';
  }
}


#endif // SPI_SHIFTER_HPP