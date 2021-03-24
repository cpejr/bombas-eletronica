#include <AutoConnect.h>
#include <AutoConnectAux.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer Server;
AutoConnect Portal(Server);

//String systemURL = "http://bombastesteback.herokuapp.com/data/teste";
String systemURL = "http://192.168.1.104:3000/esp";

AutoConnectAux equipmentIdPage("/equipment_id", "Id do equipamento");
ACText(header, "Configurações do ID do equipamento");
ACText(caption, "Aqui você pode configurar o ID deste equipamento");
ACInput(input1, "", "INPUT");
ACSubmit(send, "HELLO", "/newIp");


void onNewIp() {
  String id = Server.arg("input1");
  Serial.println(id);

  HTTPClient http;   
  
   http.begin(systemURL);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header
   String body = "{\"id\":\""+String(id)+"\"}";
   int httpResponseCode = http.POST(body);   //Send the actual POST request
  
   if(httpResponseCode==200){

    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
   
  Server.sendHeader("Location", String("/_ac"), true);
  Server.send(302, "text/plain", "");

  
}

void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

void setup() {
  Serial.begin(9600);
  equipmentIdPage.add({header, caption, input1, send});
  Portal.join(equipmentIdPage);
  Server.on("/", rootPage);
  Server.on("/newIp", onNewIp);
  if (Portal.begin()) {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
  }
}
void loop() {
 Portal.handleClient();
}
