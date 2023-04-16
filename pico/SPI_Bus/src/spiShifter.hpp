#ifndef SPI_SHIFTER_HPP
#define SPI_SHIFTER_HPP


void BroadcastSpiTransmission(char *buf, unsigned int frameLength)
{
  for (unsigned int i = 0; i < frameLength - 7; i++)
  {
    // Determine if at the end of transmission.  Exit from Broadcast function if true
    if( buf[i] == '\x03' && buf[i+1] == '\x04' && buf[i+2] == '\x06' && buf[i+3] == '\x00' )
    {
      return;
    }
  }
}


void SetMemoryToNull(char *buf, unsigned int frameLength)
{
  for (unsigned int i = 0; i < frameLength - 1; i++)
  {
    buf[i] = '\0';
  }
}


#endif // SPI_SHIFTER_HPP