#include <AutoConnect.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer Server;
AutoConnect Portal(Server);

//String systemURL = "http://bombastesteback.herokuapp.com/data/teste";
String systemURL = "http://192.168.1.104:3000/esp";

void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("Começou");
  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
    
  }
}
void loop() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   
    
 }else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(10000);  //Send a request every 5 minute
  Portal.handleClient();
}
