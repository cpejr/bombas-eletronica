#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  //Vem no Arduino já

#define ONE_WIRE_BUS 2 //variavel do pino 2 que esta plugado o Sensor de Temperatura

 
//Instacia o Objeto oneWire e Seta o pino do Sensor para iniciar as leituras
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature. 
//Repassa as referencias do oneWire para o Sensor Dallas (DS18B20)
DallasTemperature temperature_sensor(&oneWire);

const char* ssid = "NET_2GCB0FA0";
const char* password = "4BCB0FA0";

String systemURL = "http://bombastesteback.herokuapp.com/data/teste";

void setup() {
  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  temperature_sensor.begin();
  
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
   // A temperatura em Celsius para o dispositivo 1 no índice 0 (é possivel ligar varios sensores usando a mesma porta do arduino)
   float temp=temperature_sensor.getTempCByIndex(0);
   Serial.println(temp); 
   
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
  //delay(15000);
}
