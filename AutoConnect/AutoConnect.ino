#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>
#include <HTTPClient.h>

WebServer Server;
AutoConnect Portal(Server);

String systemURL = "http://bombastesteback.herokuapp.com/data/teste";

// -------------- codigo da temperatura----------
#ifdef __cplusplus
  extern "C" {
 #endif
 
  uint8_t temprature_sens_read();
 
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

int temp;
// --------- fim codigo da temperatura
void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
  }
}
void loop() {
  Portal.handleClient();
}
