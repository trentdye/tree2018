void setupBuildup(){
  timer1 = BUILDUP_INTERVAL;
  buildIndex = 0;
  isBuiltUp = false;
  }

void buildup() {
  if(!isBuiltUp){
    if(timer1 >= BUILDUP_INTERVAL){
      timer1 = timer1 - BUILDUP_INTERVAL;
      digitalWrite(lights[buildIndex],HIGH);
      buildIndex++;
      if(buildIndex >= NUM_LIGHTS){
        buildIndex = 0;
        isBuiltUp = true;
      }
    }
  }
  else {
    if(timer1 >= BUILDUP_HOLD_INTERVAL){
      timer1 = timer1 - BUILDUP_HOLD_INTERVAL;
      turnAllLightsOff();
      isBuiltUp = false;
    }
  }
}
