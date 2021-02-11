//Bibliotecas de conexao wifi
#include <WiFi.h>
#include <HTTPClient.h>

//Bibliotecas do AutoConnect
#include <AutoConnect.h>
#include <WebServer.h>

//Bibliotecas sensor de temperatura
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  //Vem no Arduino já

//Bibliotecas sensor de Corrente
#include "EmonLib.h"
#include <SPI.h>

//Configuracoes Temperatura
#define ONE_WIRE_BUS 4 //variavel do pino 4 que esta plugado o Sensor de Temperatura
OneWire oneWire(ONE_WIRE_BUS); //Instacia o Objeto oneWire e Seta o pino do Sensor para iniciar as leituras
DallasTemperature temperature_sensor(&oneWire); //Repassa as referencias do oneWire para o Sensor Dallas (DS18B20)

//Configuracoes Corrente
EnergyMonitor emon1;
int rede = 5; //Tensao da rede eletrica
int pino_sct = 25; //Pino do sensor SCT

//Configuracoes do Autoconnect
WebServer Server;
AutoConnect Portal(Server);
void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

String systemURL = "http://bombastesteback.herokuapp.com/data/teste";


void setup() {
  delay(1000);
  Serial.begin(115200);
  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
  }
}
  
void loop() {

    
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   //Sensor de Temperatura
   temperature_sensor.requestTemperatures();
   float temp=temperature_sensor.getTempCByIndex(0);
   Serial.print("Temperatura : ");
   Serial.println(temp); 

   //Sensor de Corrente
   double Irms = emon1.calcIrms(1480); //Calcula a corrente
   Serial.print("Corrente : ");
   Serial.println(Irms); //Mostra o valor da corrente no serial monitor e display
   
   
   HTTPClient http;   
  
   http.begin(systemURL);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header
   String body = "{\"temperature\":\"32\",\"current\":\"10\",\"voltage\":\"24.25\",\"vibrations\":\"10\"}";
   int httpResponseCode = http.POST(body);   //Send the actual POST request
  
   if(httpResponseCode>0){

    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
 }else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(300000);  //Send a request every 5 minute
}
