
/*
 * Colour detection of victim
 * 
 */
void setupColour()
{
 
  // Set Sensor output as input and the rest as output
  DDRB = ( S1 | S2 | S3 )
  DDRD = (S4 | ~(sensorOut))
  // Set Frequency scaling to 20%
  PORTB |= S0; //write to high
  PORTB &= ~(S1); //write to low
}

// Function to read Red Pulse Widths
int getRedPW() {
 
  // Set sensor to read Red only
  PORTB &= ~(S2); //write to low
  PORTB &= ~(S3); //write to low
  
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Green Pulse Widths
int getGreenPW() {
 
  // Set sensor to read Green only
  PORTB |= S2; //write to high
  PORTB |= S3; //write to high
  
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Blue Pulse Widths
int getBluePW() {
 
  // Set sensor to read Blue only
  PORTB &= ~(S2); //write to low
  PORTB |= S3; //write to high
  
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}


int getColour() {
  // Read Red value
  int color;
  for (int i = 0; i < 4; i ++){
    redPW = getRedPW();
    // Map to value from 0-255
    redValue = map(redPW, redMin,redMax,255,0);
    //Delay to stabilize sensor
    delay(50);
    
    // Read Green value
    greenPW = getGreenPW();
    greenValue = map(greenPW, greenMin,greenMax,255,0);
    delay(50);
    
    // Read Blue value
    bluePW = getBluePW();
    blueValue = map(bluePW, blueMin,blueMax,255,0);
    delay(50);
    
    if ((redValue - greenValue >= 75) && (redValue - blueValue >= 75) && (abs(greenValue - blueValue) <= 20)) {
      color = 0;
      PLAY_RED();
    }
    else if ((greenValue - redValue > 0) && (greenValue - blueValue > 20)){
      color = 1;
      PLAY_GREEN();
    }
    else {
      color = 2;
      PLAY_NONSENSE();
    }
  }
  return color;
 
}
