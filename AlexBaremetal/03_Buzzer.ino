
/*
 * Buzzer to play different tunes corresponding to
 * the colour detected by the colour sensor
 * 
 */
void PLAY_RED(){
  for(int i = 0; i<RED_SIZE; i=i+2){
    tone(BUZZER, red[i], red[i+1]);
  }
}

void PLAY_GREEN(){
  for(int i = 0; i<GREEN_SIZE; i=i+2){
    tone(BUZZER, green[i], green[i+1]);
  }
}

void PLAY_NONSENSE(){
  for(int i = 0; i<NONSENSE_SIZE; i=i+2){
    tone(BUZZER, nonsense[i],nonsense[i+1]);
    delay(50);
  }
}
