
#include "sclock-cred.h"
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
//#include "sclock-time.h"

#if defined(ESP8266)
ESP8266WiFiMulti wifiMulti;
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }
  Serial.println();
  Serial.println("sClock Starting...");

  // Get the display working early so we can
  // display something on the screen
  //sclockDisplayInit();

#if defined(ESP8266)
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASS);
  wifiMulti.addAP(WIFI_SSID_ALT1, WIFI_PASS_ALT1);

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
#else
  WiFi.mode(WIFI_AP_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  //WiFi.begin(WIFI_SSID_ALT1, WIFI_PASS_ALT1);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
#endif

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  sclockOtaSetup();
  sclockButtonSetup();
  sclockTimeSetup();
  //sclockDisplaySetup();
  //sclockRadioSetup();
  sclockWebSetup();
}

void loop() {
  sclockOtaLoop();
  sclockButtonLoop();
  sclockTimeLoop();
  //sclockDisplayLoop();
  //sclockRadioLoop();
  sclockWebLoop();

  //delay(1000);
}
