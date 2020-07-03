#include <ezTime.h>

int previousMinute = 0;
bool timeChanged = true;
Timezone myTime;

void sclockTimeSetup(void)
{
  bool status;
  
  setDebug(INFO);
  
  status = waitForSync();
  
  if (status == false) {
    Serial.println("Time sync failed");
  }
  
  myTime.setLocation("Australia/Sydney");
  Serial.println("Time: " + myTime.dateTime());

  previousMinute = minute();
}

void sclockTimeLoop(void)
{
  // Call the events system, this will periodically
  // do a NTP update
  events();

  // Check if the time minutes has changed, if it has
  // then flag that the time has changed
  if (previousMinute != minute())
  {
    //Serial.println("Time changed " + myTime.dateTime());
    timeChanged = true;
    previousMinute = minute();
  }
}

bool sclockTimeHasChanged() {
  if (timeChanged) 
  {
    timeChanged = false;
    return true;
  }
  return false;
}

String sclockTimeGet() {
  return myTime.dateTime("H:i");
}

String sclockTimeHoursGet() {
  return myTime.dateTime("H");
}

String sclockTimeMinutesGet() {
  return myTime.dateTime("i");
}
