void setupStripe(){
  timer1 = STRIPE_INTERVAL;
  stripeIndex = 0;
  stripeIncrementing = true;
}

void stripe(){
  if(timer1 >= STRIPE_INTERVAL){
    timer1 = timer1 - STRIPE_INTERVAL;
    if(stripeIncrementing){
      digitalWrite(lights[stripeIndex], HIGH);
    }
    else{
      digitalWrite(lights[stripeIndex],LOW);
    }
    stripeIndex++;
    if(stripeIndex >= NUM_LIGHTS){
      stripeIndex = 0;
      stripeIncrementing = !stripeIncrementing;
    }
  }
}

