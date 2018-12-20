void runTest(){
  for(int i=0; i<NUM_LIGHTS; i++){
    digitalWrite(lights[i], HIGH);
  }
  delay(100);
  for(int i=0; i<NUM_LIGHTS; i++){
    digitalWrite(lights[i], LOW);
  }
  delay(100);
  for(int i=0; i<NUM_LIGHTS; i++){
    digitalWrite(lights[i], HIGH);
  }
  delay(500);
  while(!debouncer.fell()){
    debouncer.update();
  }
}

