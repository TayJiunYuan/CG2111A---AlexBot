
/*
 * Alex's setup and run codes
 * 
 */

// Clears all our counters
void clearCounters()
{
  leftForwardTicks=0;
  leftReverseTicks=0;
  rightForwardTicks=0;
  rightReverseTicks=0;
  leftForwardTicksTurns=0;
  leftReverseTicksTurns=0;
  rightForwardTicksTurns=0;
  rightReverseTicksTurns=0;
  leftRevs=0;
  rightRevs=0;
  forwardDist=0;
  reverseDist=0; 
}

// Clears one particular counter
void clearOneCounter(int which)
{
  clearCounters();
}
// Intialize Vincet's internal states

void initializeState()
{
  clearCounters();
}


void setup() {
  // put your setup code here, to run once:

  cli();
  setupEINT();
  setupSerial();
  startSerial();
  setupMotors();
  startMotors();
  enablePullups();
  initializeState();
  setupColour();
  sei();

  AlexDiagonal = sqrt((ALEX_LENGTH*ALEX_LENGTH)+(ALEX_BREADTH * ALEX_BREADTH));
  AlexCircum = PI * AlexDiagonal;
}


void loop() {

 // put your main code here, to run repeatedly:
  TPacket recvPacket; // This holds commands from the Pi

  TResult result = readPacket(&recvPacket);
  
  if(result == PACKET_OK){
    handlePacket(&recvPacket);
  }
  else
    if(result == PACKET_BAD)
    {
      sendBadPacket();
    }
    else
      if(result == PACKET_CHECKSUM_BAD)
      {
        sendBadChecksum();
      } 
  if (deltaDist > 0){
      if (dir == FORWARD){
          if (forwardDist > newDist){
              deltaDist = 0;
              newDist = 0;
              stop();
          }
      }

      else if(dir == BACKWARD){
           if (reverseDist > newDist){
              deltaDist = 0;
              newDist = 0;
              stop();
          } 
      }

      else if(dir == STOP){
          deltaDist = 0;
          newDist = 0;
          stop();
      }      
      
  } 
  if (deltaTicks > 0){
      if (dir == LEFT){
          if (leftReverseTicksTurns >= targetTicks){
              deltaTicks = 0;
              targetTicks = 0;
              stop();
          }
      }

      else if(dir == RIGHT){

      if (rightReverseTicksTurns >= targetTicks){
              deltaTicks = 0;
              targetTicks = 0;
              stop();
          } 
      }

      else 
        if(dir == STOP){
          deltaTicks = 0;
          targetTicks = 0;
          stop();
      }
   }
}
