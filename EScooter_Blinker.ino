#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define PIN_NEO_PIXEL 15
#define NUM_PIXELS 30
#define BUTTON_PIN_R 19
#define BUTTON_PIN_L 18

int lastState_L = HIGH;
int lastState_R = HIGH;
int a = 1;

int currentState_L;
int currentState_R;

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void blinker_l() {
  for (int i=0; i<5; i++) {
    NeoPixel.fill(NeoPixel.Color(0, 0, 0), 0, 7);
    // turn pixels to green one-by-one with delay between each pixel
    for (int pixel = 0; pixel < 7; pixel++) {           // for each pixel
      NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 255, 0));  // it only takes effect if pixels.show() is called
      NeoPixel.show();   
      
      delay(70);
    }

  currentState_L = digitalRead(BUTTON_PIN_L);

  if(lastState_L == HIGH && currentState_L == LOW) {
    i = 3;
    //lastState_L = currentState_L;
    }
  }
  NeoPixel.fill(NeoPixel.Color(255, 0, 0), 0, 7);
  NeoPixel.show();  
}

void blinker_r() {
  for (int i=0; i<5; i++) {
    NeoPixel.fill(NeoPixel.Color(0, 0, 0), 7, 7);
    // turn pixels to green one-by-one with delay between each pixel
    for (int pixel = 7; pixel < 15; pixel++) {
      NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 255, 0));
      NeoPixel.show();
  
      delay(70);
    }

  currentState_R = digitalRead(BUTTON_PIN_R);

  if(lastState_R == HIGH && currentState_R == LOW) {
    i = 3;
    }
    
  }
    NeoPixel.fill(NeoPixel.Color(255, 0, 0), 7, 7);
    NeoPixel.show();   
}

void setup() {
  NeoPixel.begin();
  
  lcd.init();
  lcd.backlight();

  pinMode(BUTTON_PIN_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_L, INPUT_PULLUP);

  NeoPixel.fill(NeoPixel.Color(255, 0, 0), 0, 7);
  NeoPixel.fill(NeoPixel.Color(255, 0, 0), 8, 7);
  NeoPixel.show();
  NeoPixel.show();  

}

void loop() {
  currentState_L = digitalRead(BUTTON_PIN_L);
  currentState_R = digitalRead(BUTTON_PIN_R);

  if(lastState_L == HIGH && currentState_L == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Blinker links");
    blinker_l();
    lcd.clear();
    //lastState_L = currentState_L;

  } else if (lastState_R == HIGH && currentState_R == LOW) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Blinker rechts");
    blinker_r();
    lcd.clear();
    //lastState_R = currentState_R;
    }
}