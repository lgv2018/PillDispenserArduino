int photocellPin = 0;
int photocellReading;
bool foundHome = false;
int home = 0; 
bool pill = false;
int calibrationPhotoCell;
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'4','1','S','7'},
  {'5','2','0','8'},
  {'6','3','E','9'},
  {'B','A','D','C'}
};
byte rowPins[ROWS] = {6, 5, 3, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9, 8, 7}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(10);  // 10 rpm 
  Serial.println("Microstep steps");
  myMotor->step(350, FORWARD, MICROSTEP);
    photocellReading = analogRead(photocellPin);
  calibrationPhotoCell = photocellReading;
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);
  photocellReading = 1023 - photocellReading;
  
  while (foundHome == false) {
      photocellReading = analogRead(photocellPin);
      Serial.print("Analog reading = ");
      Serial.println(photocellReading);
      if (photocellReading > calibrationPhotoCell+20) {
        foundHome = true;
        delay(1000);
        
      } else {
        myMotor->step(1, BACKWARD, MICROSTEP);
      }
      photocellReading = 1023 - photocellReading;
    
    
  }

 
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
       
       getPill();
       dropPill();
  }

  

    
 }
 void getPill() {
  pill = false;
  while(pill == false){
    myMotor->step(100, BACKWARD, MICROSTEP);
    int steps = 0;
    while(steps < 30){
        myMotor->step(1, BACKWARD, MICROSTEP);
        delay(100);
        steps = steps + 1;
      
      }
    myMotor->step(130, FORWARD, MICROSTEP);
    photocellReading = analogRead(photocellPin);
    Serial.print("Analog reading = ");
    Serial.println(photocellReading);
    if(photocellReading<calibrationPhotoCell+10){
      pill=true;
      
    }
   }
  
 }
 void dropPill() {

    myMotor->step(195, BACKWARD, MICROSTEP);
     int steps = 0;
    while(steps < 40){
          myMotor->step(1, BACKWARD, MICROSTEP);
          delay(100);
          steps = steps + 1;
      }
   myMotor->step(235, FORWARD, MICROSTEP);
  
 }
  
  

  
  /*Serial.println("Microstep steps");
  myMotor->step(1, FORWARD, MICROSTEP);*/ 
 
  // put your main code here, to run repeatedly:


