const int REDPIN = 3;
const int YELOWPIN = 4;
const int GREENPIN = 5;

const int DIRECTION_CHANGE_PIN = 12;
int directionChange = 0;


void setup() {

  pinMode(REDPIN,OUTPUT);
  pinMode(YELOWPIN,OUTPUT);
  pinMode(GREENPIN,OUTPUT);

  pinMode(DIRECTION_CHANGE_PIN,INPUT);

}

void turnOnR(){
  digitalWrite(REDPIN,HIGH);
}

void turnOnY(){
  digitalWrite(YELOWPIN,HIGH);
}

void turnOnG(){
  digitalWrite(GREENPIN,HIGH);
}

void turnOffR(){
  digitalWrite(REDPIN,LOW);
}

void turnOffY(){
  digitalWrite(YELOWPIN,LOW);
}

void turnOffG(){
  digitalWrite(GREENPIN,LOW);
}

void rightMovement(){
  turnOnR();
  delay(2000);

  turnOffR();
  turnOnY();
  delay(1000);

  turnOffY();
  turnOnG();
  delay(500);

  turnOffG();

  //delay when all are off
  delay(500);
}

void leftMovement(){
  turnOnG();
  delay(500);

  turnOffG();
  turnOnY();
  delay(1000);

  turnOffY();
  turnOnR();
  delay(2000);

  turnOffR();
  
  delay(500);
}

void loop() {
  directionChange = digitalRead(DIRECTION_CHANGE_PIN);

  if(directionChange == HIGH){
    directionChange == 1? 0 : 1;
  }

  

  if(directionChange == 1){
    leftMovement();
  }

  else{
    rightMovement();
  }
  

}
