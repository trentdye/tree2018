void setupAlternate() {
  timer1 = ALTERNATE_INTERVAL;
  altState = 0;
  }

void alternate() {
  if(timer1 >= ALTERNATE_INTERVAL){
    timer1 = timer1 - ALTERNATE_INTERVAL;
    for(int i=0; i<NUM_RED_LIGHTS; i++){
      if(altState == 0 && (i==1 || i==3))
      {
        digitalWrite(lights[i], HIGH);
      }
      else if(altState == 1 && (i==0 || i==2 || i==4 || i==7))
      {
        digitalWrite(lights[i], HIGH);
      }
      else if(altState == 2 && (i==5 || i==6))
      {
        digitalWrite(lights[i], HIGH);
      }
      else{
        digitalWrite(lights[i], LOW);
      }
    }
    digitalWrite(lights[YELLOW], HIGH);
    altState++;
    if(altState > 2){
      altState = 0;
    }
  }
}
