#include <Stepper.h> 

const int stepsPerRevolution = 450;
const int buttonPin = 2; 
const int buttonPinReverse = 3; 
int buttonState = LOW;
int buttonStateReverse = LOW;

Stepper myStepper(stepsPerRevolution, 8,10,9,11); 

void setup() {
  myStepper.setSpeed(60); 
  pinMode(buttonPin, INPUT);
  pinMode(buttonPinReverse, INPUT);
  Serial.begin(9600); // Serial.println(">> ON");
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  buttonStateReverse = digitalRead(buttonPinReverse);
  
  Serial.println(">> "+ buttonState);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    //horario
    //girar90positivo();
    myStepper.step(stepsPerRevolution); 
    buttonState = LOW;
    
    Serial.println(">> ON");
  
  }
  
  if (buttonStateReverse == HIGH) {
    //horario
    //girar90negativo();
    myStepper.step(-stepsPerRevolution);
    buttonState = LOW;
    Serial.println(">> ON");
  } 
}

void girar90positivo(){
    myStepper.step(stepsPerRevolution); 
    
}

void girar90negativo(){
    myStepper.step(-stepsPerRevolution); 
}

