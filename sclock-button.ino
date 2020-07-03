
const int BUTTON_PIN = 5; //D1;  // Input pin for touch button

int buttonState = 0;
bool button = false;

ICACHE_RAM_ATTR void buttonInterrupt() {
  button = true;
}

void sclockButtonSetup(void)
{
  // Setup the button input pin and interrupt
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, RISING);
}

void sclockButtonLoop(void)
{
  // If a touch is detected
  if (button == true) 
  {
    Serial.println("Button");

    // Check if the display is off
    // if it is then turn it on and do nothing else
    if (sclockDisplaySleeping()) {
      sclockDisplayWakeup();
    }
    else {
      // Toggle the radio
    }
    
    button = false;
  }
}
