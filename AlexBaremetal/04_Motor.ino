
/*
 * Alex's motor drivers.
 * 
 */

// Set up Alex's motors. Right now this is empty, but
// later you will replace it with code to set up the PWMs
// to drive the motors.
void setupMotors()
{
  /* Our motor set up is:  
   *    A1IN - Pin 5, PD5, OC0B
   *    A2IN - Pin 6, PD6, OC0A
   *    B1IN - Pin 10, PB2, OC1B
   *    B2In - pIN 11, PB3, OC2A
   */
  // pulse wave modulation (PWM) set up used to 
  // power and control the power and direction of motors
  
  //step 1: initialise count register 0
  TCNT0 = 0;
  // type: PWM phase correct 
  // clear OC0A & OC0B on compare match when up-counting, set when downn-counting
  TCCR0A = 0b10100001; 
  
  OCR0A = 0;
  OCR0B = 0;
  
  TIMSK0 |= 0b110;
  
  //step 2: initialise count register 1
  TCNT1 = 0;
  TCCR1A = 0b10100001;;
  
  OCR1A = 0;
  OCR1B = 0;
  
  TIMSK1 |= 0b110;
    
}

// Start the PWM for Alex's motors.
void startMotors()
{
  //pre scalar = 64
  TCCR0B = 0b00000011;
  TCCR1B = 0b00000011;
  TCCR2B = 0b00000011;

  DDRB |= (LF | LR);
  DDRD |= (RF | RR);
}

// Convert percentages to PWM values
int pwmVal(float speed)
{
  if(speed < 0.0)
    speed = 0;

  if(speed > 100.0)
    speed = 100.0;

  return (int) ((speed / 100.0) * 255.0);
}

// Move Alex forward "dist" cm at speed "speed".
// "speed" is expressed as a percentage. E.g. 50 is
// move forward at half speed.
// Specifying a distance of 0 means Alex will
// continue moving forward indefinitely.
void forward(float dist, float speed)
{
  if(dist > 0)
      deltaDist = dist;
  else
      deltaDist=9999999;
  
  newDist=forwardDist + deltaDist;
  
  dir = FORWARD;
  
  int val = pwmVal(speed);

  OCR0A = val-4;
  OCR0B = 0;
  OCR1BH = 0;
  OCR1BL = val;
  
  /*
  analogWrite(LF, val);
  analogWrite(RF, val-4);
  analogWrite(LR,0);
  analogWrite(RR, 0);
  */
}

// Reverse Alex "dist" cm at speed "speed".
// "speed" is expressed as a percentage. E.g. 50 is
// reverse at half speed.
// Specifying a distance of 0 means Alex will
// continue reversing indefinitely.
void reverse(float dist, float speed)
{
  if(dist > 0)
      deltaDist = dist;
  else
      deltaDist=9999999;
  
  newDist=reverseDist + deltaDist;
  
  dir = BACKWARD;
  
  int val = pwmVal(speed);

  // For now we will ignore dist and 
  // reverse indefinitely. We will fix this
  // in Week 9.

  // LF = Left forward pin, LR = Left reverse pin
  // RF = Right forward pin, RR = Right reverse pin
  // This will be replaced later with bare-metal code.
  /*analogWrite(LR, val);
  analogWrite(RR, val-5);
  analogWrite(LF, 0);
  analogWrite(RF, 0);*/
  OCR0A = 0;
  OCR0B = val;
  OCR2A = val;
  OCR1BL = 0;
  OCR1BH = 0;
}

unsigned long computeDeltaTicks (float ang)
{
  unsigned long ticks = (unsigned long)((ang*0.60*AlexCircum*COUNTS_PER_REV)/(360.0*WHEEL_CIRC));
  return ticks;
}

// Turn Alex left "ang" degrees at speed "speed".
// "speed" is expressed as a percentage. E.g. 50 is
// turn left at half speed.
// Specifying an angle of 0 degrees will cause Alex to
// turn left indefinitely.
void left(float ang, float speed)
{

  if(ang > 0)
      deltaTicks = computeDeltaTicks (ang);
  else
      deltaTicks=9999999;
  
  targetTicks=leftReverseTicksTurns + deltaTicks;
  
  dir = LEFT;
  int val = pwmVal(speed);

  // For now we will ignore ang. We will fix this in Week 9.
  // We will also replace this code with bare-metal later.
  // To turn left we reverse the left wheel and move
  // the right wheel forward.
  /*analogWrite(LR, val);
  analogWrite(RF, val);
  analogWrite(LF, 0);
  analogWrite(RR, 0);*/
  OCR0A = val;
  OCR0B = 0;
  OCR2A = val;
  OCR1BL = 0;
  OCR1BH = 0;
}

// Turn Alex right "ang" degrees at speed "speed".
// "speed" is expressed as a percentage. E.g. 50 is
// turn left at half speed.
// Specifying an angle of 0 degrees will cause Alex to
// turn right indefinitely.
void right(float ang, float speed)
{
  
  if(ang > 0)
      deltaTicks = computeDeltaTicks (ang);
  else
      deltaTicks=9999999;
  
  targetTicks=rightReverseTicksTurns + deltaTicks;
  
  dir = RIGHT;
  int val = pwmVal(speed);

  // For now we will ignore ang. We will fix this in Week 9.
  // We will also replace this code with bare-metal later.
  // To turn right we reverse the right wheel and move
  // the left wheel forward.
  /*analogWrite(RR, val);
  analogWrite(LF, val);
  analogWrite(LR, 0);
  analogWrite(RF, 0);*/
  OCR0A = 0;
  OCR0B = val;
  OCR1A = 0;
  OCR1BH = 0;
  OCR1BL = val;
}

// Stop Alex. To replace with bare-metal code later.
void stop()
{
  /*analogWrite(LF, 0);
  analogWrite(LR, 0);
  analogWrite(RF, 0);
  analogWrite(RR, 0);*/
  dir = STOP;
  OCR0A = 0;
  OCR0B = 0;
  OCR1A = 0;
  OCR1BH = 0;
  OCR1BL = 0;
}
