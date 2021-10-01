#include "communicationController.h"
 
WebServer Server;
AutoConnect Portal(Server);

void rootPage() {
    char content[] = "Hello, world";
    Server.send(200, "text/plain", content);
}

CommunicationController::CommunicationController(String stringUrl){

    this->_baseUrl = stringUrl;
};

void CommunicationController::init(void) {

    delay(COMMUNICATION_INIT_DELAY);

    Server.on("/", rootPage);
    if (Portal.begin()) {
        Serial.println("HTTP server:" + WiFi.localIP().toString());
    };

}

void CommunicationController::sendDataToWeb(String route, String requestBody) {

    if (WiFi.status() == WL_CONNECTED) {   // Check WiFi connection status

        HTTPClient http;   

        String urlRequest = this->_baseUrl + route;

        http.begin(urlRequest);  
        http.addHeader("Content-Type", "application/json");      
        int httpResponseCode = http.POST(requestBody);   // Send the actual POST request
        
        if (httpResponseCode > 0) {

            String response = http.getString();                       
        
            Serial.println(httpResponseCode);   
            Serial.println(response);           
            
        } else {
        
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        
        }
  
        http.end();  // Free resources
  
    } else {
    
        Serial.println("Error in WiFi connection");   
    
    }
};

