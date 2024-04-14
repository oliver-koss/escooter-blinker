#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>

#include "time.h"

#include <TinyGPSPlus.h>

TinyGPSPlus gps;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define PIN_NEO_PIXEL 15
#define NUM_PIXELS 22
#define BUTTON_PIN_R 19
#define BUTTON_PIN_L 18

ezButton button_l(BUTTON_PIN_L);
ezButton button_r(BUTTON_PIN_R);

int a = 1;


Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void blinker_l() {
  for (int i=0; i<2; i++) {
    NeoPixel.fill(NeoPixel.Color(0, 0, 0), 0, 9);
    Serial.println(i);
    
    for (int pixel = 9; pixel>-1; pixel--) {
      NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 255, 0));
      NeoPixel.show();   
      
      delay(70);
    }
//  if(digitalRead(button_r.isPressed())) {
//    i = 3;
//    }
  }
  NeoPixel.fill(NeoPixel.Color(209/5, 134/5, 0), 0, 6);

  NeoPixel.fill(NeoPixel.Color(255, 0, 0), 6, 4);
  NeoPixel.show();  
}

void blinker_r() {
  for (int i=0; i<2; i++) {
    NeoPixel.fill(NeoPixel.Color(0, 0, 0), 12, 10);

    for (int pixel = 12; pixel < 22; pixel++) {
      NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 255, 0));
      NeoPixel.show();
  
      delay(70);
    }

  //currentState_R = digitalRead(BUTTON_PIN_R);

//  if(lastState_R == HIGH && currentState_R == LOW) {
//    i = 3;
//    }
    
  }
    NeoPixel.fill(NeoPixel.Color(209/5, 134/5, 0), 16, 6);

    NeoPixel.fill(NeoPixel.Color(255, 0, 0), 12, 4);
    NeoPixel.show();   
}

void gettime() {
  byte Hour = gps.time.hour();
  byte Minute = gps.time.minute();
  byte Second = gps.time.second();

 // setTime(Hour, Minute, Second);
 // adjusttime(2, 0);
  }

void emergency() {
  NeoPixel.fill(NeoPixel.Color(255, 255, 0), 0, NUM_PIXELS);
  NeoPixel.show(); 
  delay(200);
  NeoPixel.fill(NeoPixel.Color(0, 0, 0), 0, NUM_PIXELS);
  NeoPixel.show(); 
  delay(200);
}

void startup(){
  for (int pixel = 0; pixel < 6; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(209/5, 134/5, 0));
    NeoPixel.show();
    delay(70);   
  }
  for (int pixel = 6; pixel < 16; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 0));
    NeoPixel.show();  
    delay(70); 
  }
  for (int pixel = 16; pixel < 22; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(209/5, 134/5, 0));
    NeoPixel.show();
    delay(70);   
  }
}

void setup() {

  Serial.begin(9600);
  Serial2.begin(9600);

  NeoPixel.begin();
  
  button_l.setDebounceTime(100);
  button_r.setDebounceTime(100);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enabled."); 

  startup();

}

void loop() {

  button_l.loop();
  button_r.loop();


  if(button_l.getState() == 0 && button_r.getState() == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Blinker links");
    Serial.println("Blinker links");
    blinker_l();
    lcd.clear();

  } else if (button_r.getState() == 0 && button_l.getState() == 1) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Blinker rechts");
    Serial.println("Blinker rechts");
    blinker_r();
    lcd.clear();
  }



//  Serial.write(Serial2.read());
  if (gps.encode(Serial2.read())){
    if (gps.time.isUpdated()) {
      byte Hour = gps.time.hour();
      byte Minute = gps.time.minute();
      byte Second = gps.time.second();
      
      int HourMESZ = Hour + 2;
      
      lcd.clear();
      lcd.setCursor(0, 1);
      
      lcd.print(HourMESZ);
      lcd.print(":");
      lcd.print(Minute);
      lcd.print(":");
      lcd.print(Second);

      lcd.setCursor(0, 0);
      lcd.print("Speed: ");
      lcd.print(gps.speed.kmph());
    }
  }
}
