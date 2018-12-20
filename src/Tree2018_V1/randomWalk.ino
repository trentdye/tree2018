void setupRandomWalk() {
  timer1 = WALK_INTERVAL;
  currentIndex = 4;
  randomSeed(millis());
  onLightState = true;
  }

void randomWalk(){
 if(timer1 >= WALK_INTERVAL){
    timer1 = timer1 - WALK_INTERVAL;
    if(getRandDir(currentIndex)) currentIndex++;
    else currentIndex--;
 }
 for(int i=0; i<NUM_LIGHTS; i++){
      if(i==currentIndex){
        digitalWrite(lights[i],HIGH);
      }
      else{
        digitalWrite(lights[i], LOW);
      }
      
    }
}


boolean getRandDir(uint8_t cur){ //return false, decrease, true increase
  if(cur <= 0) return true;
  else if(cur >= NUM_LIGHTS-1) return false;
  else if(random(0,2)>0) return true;
  else return false;
}
