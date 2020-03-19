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
int tensHours = 0;
int onesHours = 0;
int tensMinutes = 0;
int onesMinutes = 0;
int minutesMedTime = 0;

byte rowPins[ROWS] = {6, 5, 3, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9, 8, 7}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup() {
    Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.clearDisplay();
  display.display();
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("   Set up sequence       please wait.");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  loadTime();
  bool numberComplete = false;
  int charactersInputed = 0;

  while (numberComplete == false) {
      char customKey = customKeypad.getKey();
      if (customKey) {
        if (customKey == 'A'||customKey == 'B'||customKey == 'C'||customKey == 'D'||customKey == 'S'||customKey == 'E') {
          if (customKey == 'E'){
            charactersInputed = 0;
            tensHours = 0;
            onesHours = 0;
            tensMinutes = 0;
            onesMinutes = 0;
            loadTime();
            
            
          } else if(customKey == 'S') {
            minutesMedTime = tensHours * 10 * 60 + onesHours * 60 + tensMinutes * 10 + onesMinutes;
            Serial.println(String(minutesMedTime));
          }
          
        }else {
    
        
          Serial.println(customKey);
          if (charactersInputed == 0){
              tensHours = atoi(&customKey);
              
              charactersInputed++;
          } else if (charactersInputed == 1){
            onesHours = atoi(&customKey);
            charactersInputed++;
          } else if(charactersInputed == 2) {
            tensMinutes = atoi(&customKey);
            charactersInputed++;
          }else if(charactersInputed == 3) {
            onesMinutes = atoi(&customKey);
            charactersInputed++;
          } else {
            break;
          }
          loadTime();
              
              
        }
      }
    
  }
  
  
  

}
void loadTime(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Current Time 24H");
  display.setTextSize(2);
  display.println(String(tensHours)+ String(onesHours) + ":" + String(tensMinutes)+ String(onesMinutes));
  display.setTextSize(1);
  display.println("Stop to clear");
  display.display();
  
}
void loop() {
  // put your main code here, to run repeatedly:

}
