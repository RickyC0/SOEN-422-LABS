const int REDPIN = 3;
const int YELOWPIN = 4;
const int GREENPIN = 5;

const int DIRECTION_CHANGE_PIN = 12;

int direction = 0;
int stepIndex = 0;
unsigned long lastStepTime = 0;

const unsigned long stepPauseDurations[] = { 2000, 1000, 500, 500 };

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(YELOWPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(DIRECTION_CHANGE_PIN, INPUT_PULLUP);

  clearAllLed();

  lastStepTime = millis();  // start the timer
}

void setLights(int r, int y, int g) {
  digitalWrite(REDPIN, r);
  digitalWrite(YELOWPIN, y);
  digitalWrite(GREENPIN, g);
}

void showStep(int direction, int currentSate) {
  // if the state is forward aka direction ==0
  //  1 0 0 : the red is on
  //  0 1 0 : the red is on
  //  0 0 1 : the red is on
  //  0 0 0 : all is off

  // if the state is forward aka direction ==1
  //  0 0 1 : the red is on
  //  0 1 0 : the red is on
  //  1 0 0 : the red is on
  //  0 0 0 : all is off

  if (direction == 0) {  // RED -> YELLOW -> GREEN
    if (currentSate == 0) setLights(1, 0, 0);
    else if (currentSate == 1) setLights(0, 1, 0);
    else if (currentSate == 2) setLights(0, 0, 1);
    else clearAllLed();
  } else {  // GREEN -> YELLOW -> RED
    if (currentSate == 0) setLights(0, 0, 1);
    else if (currentSate == 1) setLights(0, 1, 0);
    else if (currentSate == 2) setLights(1, 0, 0);
    else clearAllLed();
  }
}

// clear LEDs immediately
void clearAllLed() {
  digitalWrite(REDPIN, LOW);
  digitalWrite(YELOWPIN, LOW);
  digitalWrite(GREENPIN, LOW);
}

void loop() {
  int buttonState = digitalRead(DIRECTION_CHANGE_PIN);

  //semaphore to lock the direction switch button in case the user is holding the button
  //since if the user hold the button, if loop() method will keep on looping and switching direction because buttonState will always be HIGH, => both edge lights (Green and Red) will be on
  static bool lock_direction =false;

  // check of we did press the button and reset the current state
  if (buttonState == HIGH && !lock_direction) {
    // this will interupt the system and cancel all and switch the direction mid transition
    // we assume that this is correct
    direction = (direction==0)? 1:0;
    stepIndex = 0;
    lastStepTime = millis();


    lock_direction = true;

  }else if(buttonState == LOW){
    lock_direction = false;
  }

  // Step timing
  if (millis() - lastStepTime >= stepPauseDurations[stepIndex]) {

    // change the current state of the board moving from red to yellow to green to nothing at all
    stepIndex += 1;
    if (stepIndex >= 4) {  // make sure we are with a 4 state system: {0,1,2,3}
      stepIndex = 0;
    }
    lastStepTime = millis();
  }

  showStep(direction, stepIndex);
}
