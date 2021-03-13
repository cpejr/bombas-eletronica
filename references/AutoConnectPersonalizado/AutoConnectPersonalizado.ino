#include <AutoConnect.h>
#include <AutoConnectAux.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer Server;
AutoConnect Portal(Server);

AutoConnectAux equipmentIdPage("/equipment_id", "Id do equipamento");
ACText(header, "Configurações do ID do equipamento");
ACText(caption, "Aqui você pode configurar o ID deste equipamento");
ACInput(input1, "", "INPUT");
ACSubmit(send, "HELLO", "/newIp");


void onNewIp() {
  String echo = Server.arg("input1");
  Serial.println(echo);
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
