#ifndef COMMUNICATION_CONTROLLER_H
#define COMMUNICATION_CONTROLLER_H

#include "Arduino.h"
#include "../../HardwareProfile.h"

//Bibliotecas de conexao wifi
#include <WiFi.h>
#include <HTTPClient.h>

//Bibliotecas do AutoConnect
#include <AutoConnect.h>
#include <WebServer.h>

class CommunicationController {

    public:
        CommunicationController(String stringUrl);
        void init(void);
        void sendDataToWeb(String route, String requestBody);

    private:
        String _baseUrl;
};

#endif
