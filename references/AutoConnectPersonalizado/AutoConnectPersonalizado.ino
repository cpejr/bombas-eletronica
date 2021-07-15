#include <AutoConnect.h>
#include <AutoConnectAux.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

Preferences preferences;

WebServer Server;
AutoConnect Portal(Server);

//String systemURL = "http://bombastesteback.herokuapp.com/data/teste";
String systemURL = "http://192.168.1.104:3000/esp";

AutoConnectAux equipmentIdPage("/equipment_id", "Id do equipamento");
ACText(headerId, "Configurações do ID do equipamento");
ACText(captionId, "Aqui você pode configurar o ID deste equipamento");
ACInput(input1Id, "", "ID");
ACSubmit(sendId, "NEWIP", "/newIp");

AutoConnectAux equipmentResetPage("/equipment_reset", "Reset");
ACText(headerReset, "Reset de ID");
ACText(captionReset, "Caso clique no botão, o ID do equipamento será apagado de sua memória, e poderá ser reconfigurado");
ACSubmit(sendReset, "RESET", "/reset");

void onNewIp()
{
  String id = Server.arg("input1");

  HTTPClient http;

  http.begin(systemURL);                              //Specify destination for HTTP request
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  String body = "{\"id\":\"" + String(id) + "\"}";
  int httpResponseCode = http.POST(body); //Send the actual POST request

  if (httpResponseCode == 200)
  {

    String response = http.getString(); //Get the response to the request

    Serial.println(httpResponseCode); //Print return code
    Serial.println(response);         //Print request answer

    preferences.begin("equipment", false);

    String idString = String(id);

    preferences.putString("id", idString);

    preferences.end();
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  http.end(); //Free resources

  Server.sendHeader("Location", String("/_ac"), true);
  Server.send(302, "text/plain", "");
}

void onReset(){
  preferences.begin("equipment", false);
  preferences.remove("id");
  preferences.end();
  Server.sendHeader("Location", String("/_ac"), true);
  Server.send(302, "text/plain", "");
  ESP.restart();
}

void setup()
{
  Serial.begin(9600);
  preferences.begin("equipment", false);

  if (Portal.begin())
  {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
  }

  Serial.println("ID armazenado: ");
  String id = preferences.getString("id", "");
  if (id)
  {
    equipmentResetPage.add({headerReset, captionReset, sendReset});
    Portal.join(equipmentResetPage);
    Serial.println("Equipment Id: " + String(id));
    Server.on("/reset", onReset);
  }
  else
  {
    Serial.println("No id provided to this equipment yet!");
    equipmentIdPage.add({headerId, captionId, input1Id, sendId});
    Portal.join(equipmentIdPage);
    Server.on("/newIp", onNewIp);
  }
  preferences.end();
}
void loop()
{
  Portal.handleClient();
}