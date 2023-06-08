
/*
 * Setup and start codes for external interrupts and 
 * pullup resistors.
 * 
 */
// Enable pull up resistors on pins 2 and 3
void enablePullups()
{
  // Use bare-metal to enable the pull-up resistors on pins
  // 2 and 3. These are pins PD2 and PD3 respectively.
  // We set bits 2 and 3 in DDRD to 0 to make them inputs. 
  DDRD = (~(pin_2) & ~(pin_3));
  PORTD |= (pin_2|pin_3);
  
}

// Functions to be called by INT0 and INT1 ISRs.
void leftISR()
{
  switch(dir)
  {
  case(FORWARD):
    leftForwardTicks++;
//    Serial.print("LEFT FORWARD: ");
//    Serial.println(leftForwardTicks);
    forwardDist = (unsigned long) ((float) leftForwardTicks / COUNTS_PER_REV * WHEEL_CIRC);
  break;
  
  case(BACKWARD):
    leftReverseTicks++;
//    Serial.print("LEFT BACKWARD: ");
//    Serial.println(leftReverseTicks);
    reverseDist = (unsigned long) ((float) leftReverseTicks / COUNTS_PER_REV * WHEEL_CIRC);
  break;
  
  case(LEFT):
    leftReverseTicksTurns++;
//    Serial.print("LEFT LEFTTURN: ");
//    Serial.println(leftReverseTicksTurns);
  break;
  
  case(RIGHT):
    leftForwardTicksTurns++;
//    Serial.print("LEFT RIGHTTURN: ");
//    Serial.println(leftForwardTicksTurns);
  break;
  }
  
}

void rightISR()
{
  switch(dir)
  {
  case(FORWARD):
    rightForwardTicks++;
//    Serial.print("RIGHT FORWARD: ");
//    Serial.println(rightForwardTicks);
  break;
  
  case(BACKWARD):
    rightReverseTicks++;
//    Serial.print("RIGHT BACKWARD: ");
//    Serial.println(rightReverseTicks);
  break;
  
  case(LEFT):
    rightForwardTicksTurns++;
//    Serial.print("RIGHT LEFTTURN: ");
//    Serial.println(rightForwardTicksTurns);
  break;
  
  case(RIGHT):
    rightReverseTicksTurns++;
//    Serial.print("RIGHT RIGHTTURN: ");
//    Serial.println(rightReverseTicksTurns);
  break;
  }
}

// Set up the external interrupt pins INT0 and INT1
// for falling edge triggered. Use bare-metal.
void setupEINT()
{
  // Use bare-metal to configure pins 2 and 3 to be
  // falling edge triggered. Remember to enable
  // the INT0 and INT1 interrupts.
  EICRA |= 0b00001010;
  EIMSK |= 0b00000011;
  sei();
}

// Implement the external interrupt ISRs below.
// INT0 ISR should call leftISR while INT1 ISR
// should call rightISR.
ISR(INT0_vect)
{
  leftISR();
}

ISR(INT1_vect)
{
  rightISR();
}
