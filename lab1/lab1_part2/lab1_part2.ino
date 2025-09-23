  // ---------- Pins ----------
  const int REDPIN_1 = 3;
  const int YELLOWPIN_1 = 4;
  const int GREENPIN_1 = 5;

  const int REDPIN_2 = 8;
  const int YELLOWPIN_2 = 9;
  const int GREENPIN_2 = 10;

  // ---------- Duration for each light in each set (ms) ----------
  // Set order 1: RED (5s) -> GREEN (4s) -> YELLOW (1s)
  const unsigned long durations1[] = { 5000, 4000, 1000 };

  // SeT order 2: GREEN (4s) -> YELLOW (1s) -> RED (5s)
  const unsigned long durations2[] = { 4000, 1000, 5000 };

  //struct that has A light panel set's info
  struct LightSet {
    int red_pin, yellow_pin, green_pin; // light pins
    int step = 0; // 0,1,2
    int stepStart = 0; // millis() when current step started
  };

  // Two independent light sets
  LightSet Set1;

  LightSet Set2;

  //Turns on the appropriate light from the given pins
  void toggleLights(int red_pin, int yellow_pin, int green_pin, int r_value, int y_value, int g_value) {

    digitalWrite(red_pin, r_value ? HIGH : LOW);
    digitalWrite(yellow_pin, y_value ? HIGH : LOW);
    digitalWrite(green_pin, g_value ? HIGH : LOW);
  }

  // Change the current light that is to be displayed in each light set
  void updateStep(LightSet &S, int step, bool isSet1) {
    if (isSet1) {
      // Set 1: RED -> GREEN -> YELLOW
      if (step == 0) {
        toggleLights(S.red_pin, S.yellow_pin, S.green_pin, 1, 0, 0); // RED
      }  
      else if (step == 1) {
        toggleLights(S.red_pin, S.yellow_pin, S.green_pin, 0, 0, 1); // GREEN
      }  
      else{
        toggleLights(S.red_pin, S.yellow_pin, S.green_pin, 0, 1, 0); } // YELLOW

    } else {
      //NB: THE ORDER OF LIGHTS IN THIS SET IS DIFFERENT FROM SET1 BUT WITH THE SAME TIMES FOR EACH LIGHT
      // Set 2: GREEN -> YELLOW -> RED
      if (step == 0) {
        toggleLights(S.red_pin, S.yellow_pin, S.green_pin, 0, 0, 1); // GREEN
      }
      else if (step == 1) {
        toggleLights(S.red_pin, S.yellow_pin, S.green_pin, 0, 1, 0); // YELLOW
      }
      else toggleLights(S.red_pin, S.yellow_pin, S.green_pin, 1, 0, 0); // RED
    }
  }

  // Advance one light set independently (without using delay() to not stall the entire board)
  void checkNextLight(LightSet &S, const unsigned long durations[], bool isSet1) {
    int now = millis();

    if (now - S.stepStart >= durations[S.step]) {
      S.step = (S.step + 1) % 3; //INSTEAD OF DOING IF STEP >= 4 -> STEP =0 LIKE IN PART 1, WE USED MODULO 3 FOR THE 3 LIGHTS
      //the time at which that set has been activated
      S.stepStart = now;

      //update the step in the set i.e. next light in the set
      updateStep(S, S.step, isSet1);
    }
  }

  //turn off all leds
  void clearAllLed() {
    toggleLights(Set1.red_pin, Set1.yellow_pin, Set1.green_pin, 0, 0, 0);
    toggleLights(Set2.red_pin, Set2.yellow_pin, Set2.green_pin, 0, 0, 0);
  }

  void setup() {
    pinMode(REDPIN_1, OUTPUT);
    pinMode(YELLOWPIN_1, OUTPUT);
    pinMode(GREENPIN_1, OUTPUT);

    pinMode(REDPIN_2, OUTPUT);
    pinMode(YELLOWPIN_2, OUTPUT);
    pinMode(GREENPIN_2, OUTPUT);

    clearAllLed();

    // Initialize struct fields BEFORE using them
    Set1.red_pin = REDPIN_1;
    Set1.yellow_pin = YELLOWPIN_1;
    Set1.green_pin = GREENPIN_1;

    Set2.red_pin = REDPIN_2;
    Set2.yellow_pin = YELLOWPIN_2;
    Set2.green_pin = GREENPIN_2;

    Set1.step = 0;
    Set1.stepStart = millis();
    updateStep(Set1, Set1.step, true);

    Set2.step = 0;
    Set2.stepStart = millis();
    updateStep(Set2, Set2.step, false);
  }

  void loop() {
    // Each set advances on its own schedule, independently
    checkNextLight(Set1, durations1, true); //Set 1
    checkNextLight(Set2, durations2, false); //Set 2
  }
