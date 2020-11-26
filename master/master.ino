//Bibliotecas de conexao wifi
#include <WiFi.h>
#include <HTTPClient.h>

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

//Configuracoes Rede
//const char* ssid = "Jota";
//const char* password = "jota12345";
const char* ssid = "NET_2GCB0FA0";
const char* password = "4BCB0FA0";
String systemURL = "http://bombastesteback.herokuapp.com/data/teste";


void setup() {
  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  temperature_sensor.begin();
  emon1.current(pino_sct, 60); //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
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
  
   http.begin(systemURL+"?temperature="+String(temp));  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header
   String body = "Oi";
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
