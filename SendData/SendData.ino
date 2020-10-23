#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "Jota";
const char* password = "jota12345";

String devURL = "http://192.168.1.102:3000/teste?id=09712&temperature=20";
String systemURL = "http://bombastesteback.herokuapp.com/data/teste?temperature=22";
  
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
  
   HTTPClient http;   
  
   http.begin(systemURL);  //Specify destination for HTTP request
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
  
  delay(60000);  //Send a request every 1 minute
  
}
