
/*
 * Setup and start codes for serial communications
 * 
 */
 
// Set up the serial connection. For now we are using 
// Arduino Wiring, you will replace this later
// with bare-metal code.
void setupSerial()
{
  //Serial.begin(9600);
  
  //set baud rate to 9600 bits per second
  UBRR0L = 103;
  UBRR0H = 0;
  
  //set frame format: 8 data, no parity, 1 stop bit (8N1)
  UCSR0C = 0b110;
  UCSR0A = 0;
}

// Start the serial connection. For now we are using
// Arduino wiring and this function is empty. We will
// replace this later with bare-metal code.

void startSerial()
{
  // Enable USART transmitter and receiver
  // USART_RX_vect to be triggered when a character is received
  // USART_UDRE_vect intterupt triggered when sending data register is empty
  UCSR0B = 0b10111000;
}

// Read the serial port. Returns the read character in
// ch if available. Also returns TRUE if ch is valid. 
// This will be replaced later with bare-metal code.

int readSerial(char *buffer)
{

  int count=0;
  TBufferResult result;

  do{
    result = readBuffer(&_recvBuffer, &buffer[count]);
    if (result == BUFFER_OK){
      count++;
    } 
  } while (result == BUFFER_OK);
  
  return count;
}

/*
  while(Serial.available())
    buffer[count++] = Serial. read();
*/
}


// Write to the serial port. Replaced later with
// bare-metal code

void writeSerial(const char *buffer, int len)
{
  Serial.write(buffer, len);
  TBufferResult result = BUFFER_OK;
  for(int i = 1; i < len; i += 1){
    result = writeBuffer(&_xmitBuffer, buffer[i]);
  }
  //read and write data from UDR0
  UDR0 = buffer[0];
  UCSR0B |= 0b00100000;
}


ISR(USART_RX_vect){
  //read received data from UDR0 and write to buffer
  unsigned char data = UDR0;
  writeBuffer(&_recvBuffer, data);
}

ISR(USART_UDRE_vect){
  // read data to be sent from buffer to UDR0
  unsigned char data;
  TBufferResult result = readBuffer(&_xmitBuffer, &data);

  if(result == BUFFER_OK){
    UDR0 = data;
  } 
  else if(result == BUFFER_EMPTY){
      UCSR0B &= 0b11011111;
  }
}
