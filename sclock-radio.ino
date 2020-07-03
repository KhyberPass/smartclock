
#include <Wire.h>
#include <TEA5767N.h>

TEA5767N radio = TEA5767N();

bool radioOn;

/*
  This code shows some of the uses of the TEA5767N API.
*/

void sclockRadioSetup(void)
{
  Serial.print("RadioSetup S "); Serial.println(millis());

  radioOn = false;
  
#if 0
  // 8266 is pins 4 and 5
  // ESP32 is pins 23 and 22
  if (TWCR == 0) // do this check so that Wire only gets initialized once
  {
    Serial.println("Beginning wire library...");
    Wire.begin(0,2);
  }  
#endif

  //Sets the radio station
  radio.selectFrequency(105.7);

#if 0  
  delay(5000);
  
  //Mutes the radio
  radio.mute();
  delay(2000);
  //Unmutes the radio
  radio.turnTheSoundBackOn();
  delay(2000);
  
  //Observation: At this point your Serial Monitor window
  //should be already open if you want to see the results.
  Serial.print("Stereo or Mono? ");
  Serial.println(radio.isStereo() ? "Stereo" : "Mono");
  //Mutes right channel
  radio.muteRight();
  delay(2000);
  //Should go mono
  Serial.print("Stereo or Mono? ");
  Serial.println(radio.isStereo() ? "Stereo" : "Mono");
  //Unmutes right channel
  radio.turnTheRightSoundBackOn();
  delay(2000);
  //Mutes left channel
  radio.muteLeft();
  //Should also be mono
  Serial.print("Stereo or Mono? ");
  Serial.println(radio.isStereo() ? "Stereo" : "Mono");
  delay(2000);
  //Unmutes left channel
  radio.turnTheLeftSoundBackOn();
  delay(2000);

  //Turns the radio off
  radio.setStandByOn();
  delay(2000);
  //Turns the radio on
  radio.setStandByOff();
  delay(2000);
  
  
  radio.selectFrequency(105.7);

  //Read frequenci in MHz
  Serial.print("Station selected: ");
  Serial.print(radio.readFrequencyInMHz(), 1);
  Serial.println(" MHz");
  
  //Shows reception signal level
  Serial.print("Signal level: ");
  Serial.println(radio.getSignalLevel());
  
  //Reception stereo or mono?
  Serial.print("Stereo or Mono? ");
  Serial.println(radio.isStereo() ? "Stereo" : "Mono");

#endif
  Serial.print("RadioSetup E "); Serial.println(millis());
}

void sclockRadioLoop(void)
{
  
}

void sclockRadioOn()
{
  radioOn = true;
  radio.setStandByOff();  
}

void sclockRadioOff()
{
  radioOn = false;
  radio.setStandByOn();
}

void sclockRadioSearch() {
  byte isBandLimitReached = 0;

  //Search Up is the default
  Serial.println("Search Up in progress...");
  radio.setSearchMidStopLevel();
  isBandLimitReached = radio.startsSearchMutingFromBeginning();
  
  Serial.print("Band limit reached? ");
  Serial.println(isBandLimitReached ? "Yes" : "No");
  delay(2000);
  
  float freq = radio.readFrequencyInMHz();
  Serial.print("Station found: ");
  Serial.print(freq, 1);
  Serial.println(" MHz");
  delay(2000);
  
  while (!isBandLimitReached) {
    
    Serial.println("Search Up in progress...");
    //If you want listen to station search, use radio.searchNext() instead
    isBandLimitReached = radio.searchNextMuting();
    
    Serial.print("Band limit reached? ");
    Serial.println(isBandLimitReached ? "Yes" : "No");
    delay(2000);
    
    freq = radio.readFrequencyInMHz();
    Serial.print("Station found: ");
    Serial.print(freq, 1);
    Serial.println(" MHz");
    delay(2000);
  }
  
  Serial.println("Band Limit Reached, searching down...");
  
  radio.setSearchDown();
  radio.setSearchMidStopLevel();
  
  Serial.println("Search Down in progress...");
  isBandLimitReached = radio.searchNextMuting();
  
  Serial.print("Band limit reached? ");
  Serial.println(isBandLimitReached ? "Yes" : "No");
  delay(2000);
  
  freq = radio.readFrequencyInMHz();
  Serial.print("Station found: ");
  Serial.print(freq, 1);
  Serial.println(" MHz");
  delay(2000);
  
  while (!isBandLimitReached) {
    
    Serial.println("Search Down in progress...");
    isBandLimitReached = radio.searchNextMuting();
    
    Serial.print("Band limit reached? ");
    Serial.println(isBandLimitReached ? "Yes" : "No");
    delay(2000);
        
    freq = radio.readFrequencyInMHz();
    Serial.print("Station found: ");
    Serial.print(freq, 1);
    Serial.println(" MHz");
    delay(2000);
  }

}
