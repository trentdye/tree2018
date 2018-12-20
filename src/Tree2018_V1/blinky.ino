void setupBlinky(){
  blinkState = true;
  timer1 = BLINK_INTERVAL;
}

void blinky(){
  if(timer1 >= BLINK_INTERVAL){
    timer1 = timer1 - BLINK_INTERVAL;
    for(int i=0; i<NUM_RED_LIGHTS; i++){
      digitalWrite(lights[i], blinkState);
    }
    digitalWrite(lights[YELLOW], HIGH);
    blinkState = !blinkState;
  }
}

