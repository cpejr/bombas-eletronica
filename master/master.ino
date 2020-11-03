#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "NET_2GCB0FA0";
const char* password = "4BCB0FA0";

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

void setup() {
  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
}
  
void loop() {

    
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   temp = ((temprature_sens_read() - 32) / 1.8);
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
  
  //delay(60000);  //Send a request every 1 minute
  delay(15000);
}
