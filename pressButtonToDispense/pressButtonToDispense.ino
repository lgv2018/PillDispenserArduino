int photocellPin = 0;
int photocellReading;
bool foundHome = false;
int home = 0; 
bool pill = false;
int position = 0;
int calibrationPhotoCell;
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#define OLED_RESET 4

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


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
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(10);  // 10 rpm 
  Serial.println("Microstep steps");
  //myMotor->step(350, FORWARD, MICROSTEP);
    photocellReading = analogRead(photocellPin);
  calibrationPhotoCell = photocellReading;
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);
  photocellReading = 1023 - photocellReading;
  
  while (foundHome == false) {
      photocellReading = analogRead(photocellPin);
      Serial.print("Analog reading = ");
      Serial.println(photocellReading);
      String line = "Photo Cell:" + String(photocellReading);

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
  display.clearDisplay();
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Press Any Button to Dispense");
display.display();
  
  if (customKey){
       
       getPill();
       dropPill();
  }

  

    
 }
 void getPill() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Getting");
  display.println("Pill");
  display.display();
  pill = false;
  while(pill == false){
    myMotor->step(100, BACKWARD, MICROSTEP);
    position = position + 100;
    int steps = 0;
    while(steps < 30){
        myMotor->step(1, BACKWARD, MICROSTEP);
        position = position + 1;
        delay(100);
        steps = steps + 1;

      
      }
    myMotor->step(130, FORWARD, MICROSTEP);
    position = position - 130;

    photocellReading = analogRead(photocellPin);
    Serial.print("Analog reading = ");
    Serial.println(photocellReading);
    String line = "Photo Cell:" + String(photocellReading);
    if(photocellReading<calibrationPhotoCell+20){
      pill=true;
      
    }
   }
  display.clearDisplay();
  display.display();
  
 }
 void dropPill() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Dropping");
  display.println("Pill");
  display.display();

    myMotor->step(195, BACKWARD, MICROSTEP);
    position = position + 195;
     int steps = 0;
    while(steps < 40){
          myMotor->step(1, BACKWARD, MICROSTEP);
          delay(100);
          steps = steps + 1;
          position = position + 1;
         
      }
     display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Going");
  display.println("Home");
  display.display();
   myMotor->step(100, FORWARD, MICROSTEP);
   position = position - 80;
   steps = 0;
   while(steps < 40){
        myMotor->step(1, FORWARD, MICROSTEP);
        delay(200);
        steps = steps + 1;
        position = position - 1;
      
    }
    myMotor->step(95, FORWARD, MICROSTEP);
    position = position - 115;
  display.clearDisplay();
  display.display();
   

   //235
  
 }
 void displayLine(String line){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println(String(position));
  display.display();
  
  /*
  display.println(line);
  display.println("Threshold" + String(calibrationPhotoCell));
  display.display();*/
 }
  
  

  
  /*Serial.println("Microstep steps");
  myMotor->step(1, FORWARD, MICROSTEP);*/ 
 
  // put your main code here, to run repeatedly:


