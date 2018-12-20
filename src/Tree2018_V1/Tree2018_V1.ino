#include <avr/sleep.h>
#include <avr/interrupt.h>

#define NUM_RED_LIGHTS 8
#define NUM_LIGHTS 9
#define BUILDUP_INTERVAL 1000
#define BUILDUP_HOLD_INTERVAL 3000
#define YELLOW 8

#define ALTERNATE_INTERVAL 1000
#define WALK_INTERVAL 950
#define REFRESH_INTERVAL 10
#define BUTTON_PIN 0
#define TEST_PIN 10
#define STRIPE_INTERVAL 500
#define BLINK_INTERVAL 1000

#include <elapsedMillis.h>
#include <Bounce2.h>
elapsedMillis timer1;
elapsedMillis timer2;

//uint8_t lights[] = {1,2,3,4,5,6,7,9,8}; //yellow light last
uint8_t lights[] = {6,8,9,5,2,1,3,4,7}; //yellow light last
uint8_t state; //0 = buildup 1=alternate 2=randomwalk 3=stripe

//buildup global variables
boolean isBuiltUp; 
uint8_t buildIndex;

//alternate global variables
uint8_t altState;

//randomWalk global variables
uint8_t currentIndex;
boolean onLightState;

//stripe global variables
uint8_t stripeIndex;
boolean stripeIncrementing; //true = building, false = decreasing

//blink global variables
boolean blinkState;

//arcade global variables

Bounce debouncer = Bounce(); 

void setup() {
  //set mode of all pins
  for(int i=0; i<NUM_LIGHTS; i++){
    pinMode(lights[i], OUTPUT);
  }
  resetTimers();

  state = 0;
  
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(TEST_PIN, INPUT_PULLUP);
  
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5);

  delay(50);
  if(digitalRead(TEST_PIN)==LOW){
    runTest();
    resetTimers();
    turnAllLightsOff();
  }
}

void resetTimers(){
  timer1 = 0;
  timer2 = 0;
}

void loop() {
  if(timer2 > 3600000UL){ 
    turnAllLightsOff(); 
    sleep();
    debouncer.attach(BUTTON_PIN);
    debouncer.interval(5);
    resetTimers(); 
    setupState(state);
    }
  
  switch(state){
    case 0:
      buildup();
      break;
    case 1:
      alternate();
      break;
    case 2:
      randomWalk();
      break;
    case 3:
      stripe();
      break;
    case 4:
      blinky();
      break;
    default:
      state=0;
      break;
  }

  debouncer.update();
  if(debouncer.fell()){
    timer2 = 0; //begin sleep countdown again, shows sign of activity
    state++;
    if(state>4) state = 0;
    turnAllLightsOff();
    setupState(state);
  }

  
}


void turnAllLightsOff(){
  for(int i=0; i<NUM_LIGHTS; i++){
    digitalWrite(lights[i], LOW);
  }
}

void setupState(uint8_t s){
  if(s==0) setupBuildup();
  else if(s==1) setupAlternate();
  else if(s==2) setupRandomWalk();
  else if(s==3) setupStripe();
  else if(s==4) setupBlinky();
}

