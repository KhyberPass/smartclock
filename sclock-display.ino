#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMono24pt7b.h>
//#include <Fonts/FreeSans24pt7b.h>
//#include <Fonts/FreeSerif24pt7b.h>

#include "sclock-time.h"
#define SSD1306_I2C_ADDRESS 0x3C

int displayState = 1;

static uint32_t prevMillis;
#define DisplayTimeout 30000

// Reset pin not used on 4-pin OLED module
Adafruit_SSD1306 display(-1);  // -1 = no reset pin

// 128 x 64 pixel display
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void sclockDisplayInit() {
  // Initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print("Booting");
  display.display();
}

void sclockDisplaySetup() {
  Serial.print("DisplaySetup S "); Serial.println(millis());

  prevMillis = millis();

  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  Serial.print("DisplaySetup E "); Serial.println(millis());
}

void sclockDisplayLoop() {
  // Backlight timer control
  if (millis() - prevMillis > DisplayTimeout) {
    sclockDisplayTimer();
    prevMillis = millis();
  }

  // Update time if it has changed
  if (sclockTimeHasChanged())
  {
    //Serial.println("Time changed");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
//    display.setFont(&FreeSans24pt7b);
//    display.setFont(&FreeSerif24pt7b);
    display.setFont(&FreeMono24pt7b);
    display.setCursor(0,60);
    String str = sclockTimeHoursGet();
    display.print(str);
    // Shuffle a bit and add the :
// Time Bounds 5 32 47 30 
// : Bounds 11 41 7 21 
    int16_t  x1, y1;
    uint16_t w, h;
    display.getTextBounds(str, 0, 60, &x1, &y1, &w, &h);
    Serial.printf("Bounds %d %d %d %d", x1, y1, w, h);

    display.setCursor(w,60);
    display.print(":");   
     
    display.setCursor(w+20,60);
    display.print(sclockTimeMinutesGet());
    display.display();
    display.setFont();
  }
}

void sclockDisplayTimer() {
  //Serial.print("Display Timer ");

  // If the display timer has
  // triggered then turn it off
  sclockDisplayOff();
}

bool sclockDisplaySleeping() {
  if (displayState)
    return false;
    
  return true;
}

void sclockDisplayWakeup() {
  // If the display is off turn it on
  // and reset the timer
  if (displayState == 0)
  {
    sclockDisplayOn();
    prevMillis = millis();
  }
}

void sclockDisplayToggle() {
  if (displayState)
  {
    displayCommand(SSD1306_DISPLAYOFF);
    displayState = 0;
  }
  else
  {
    displayCommand(SSD1306_DISPLAYON);
    displayState = 1;
  }
}

void sclockDisplayOff() {
  displayCommand(SSD1306_DISPLAYOFF);
  displayState = 0;
}

void sclockDisplayOn() {
  displayCommand(SSD1306_DISPLAYON);
  displayState = 1;
}


void displayCommand(uint8_t c) {
  uint8_t control = 0x00;   // Co = 0, D/C = 0
  Wire.beginTransmission(SSD1306_I2C_ADDRESS);
  Wire.write(control);
  Wire.write(c);
  Wire.endTransmission();
}
