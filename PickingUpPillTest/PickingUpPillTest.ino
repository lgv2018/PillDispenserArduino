int photocellPin = 0;
int photocellReading;
bool foundHome = false;
int home = 0; 
int number = 0;
#include <Wire.h>
#include <Adafruit_MotorShield.h>

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
  /*Serial.println("Microstep steps");
  myMotor->step(350, FORWARD, MICROSTEP);*/
 
}

void loop() {
  myMotor->step(1, FORWARD, MICROSTEP);
  delay(100);
  number = number + 1;
  Serial.println(number);
  /*photocellReading = analogRead(photocellPin);
      Serial.print("Analog reading = ");
      Serial.println(photocellReading);*/

  
  /*Serial.println("Microstep steps");
  myMotor->step(1, FORWARD, MICROSTEP);*/ 
 
  // put your main code here, to run repeatedly:

}
