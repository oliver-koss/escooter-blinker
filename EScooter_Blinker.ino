#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define PIN_NEO_PIXEL_L 15
#define PIN_NEO_PIXEL_R 2
#define NUM_PIXELS 30
#define BUTTON_PIN_R 19
#define BUTTON_PIN_L 18

int lastState_L = HIGH;
int lastState_R = HIGH;
int a = 1;

int currentState_L;
int currentState_R;

Adafruit_NeoPixel NeoPixel_L(NUM_PIXELS, PIN_NEO_PIXEL_L, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NeoPixel_R(NUM_PIXELS, PIN_NEO_PIXEL_R, NEO_GRB + NEO_KHZ800);

void blinker_l() {
  for (int i=0; i<5; i++) {
    NeoPixel_L.fill(NeoPixel_L.Color(0, 0, 0), 0, 7);
    // turn pixels to green one-by-one with delay between each pixel
    for (int pixel = 0; pixel < 7; pixel++) {           // for each pixel
      NeoPixel_L.setPixelColor(pixel, NeoPixel_L.Color(255, 255, 0));  // it only takes effect if pixels.show() is called
      NeoPixel_L.show();   
      
      delay(70);
    }
  }
  NeoPixel_L.fill(NeoPixel_L.Color(255, 0, 0), 0, 7);
  NeoPixel_L.show();  
}

void blinker_r() {
  for (int i=0; i<5; i++) {
    NeoPixel_R.fill(NeoPixel_R.Color(0, 0, 0), 0, 7);
    // turn pixels to green one-by-one with delay between each pixel
    for (int pixel = 0; pixel < 7; pixel++) {
      NeoPixel_R.setPixelColor(pixel, NeoPixel_R.Color(255, 255, 0));
      NeoPixel_R.show();
  
      delay(70);
    }
  }
    NeoPixel_R.fill(NeoPixel_R.Color(255, 0, 0), 0, 7);
    NeoPixel_R.show();   
}

void setup() {
  NeoPixel_L.begin();  // initialize NeoPixel strip object (REQUIRED)
  NeoPixel_R.begin();
  
  lcd.init();
  lcd.backlight();

  pinMode(BUTTON_PIN_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_L, INPUT_PULLUP);

  NeoPixel_L.fill(NeoPixel_L.Color(255, 0, 0), 0, 10);
  NeoPixel_R.fill(NeoPixel_R.Color(255, 0, 0), 0, 10);
  NeoPixel_L.show();
  NeoPixel_R.show();  

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
