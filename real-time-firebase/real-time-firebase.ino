#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Firebase settings
#define FIREBASE_HOST "real-time-sensor.firebaseio.com"
#define FIREBASE_AUTH "orjeTx5vMypP8busQE4H82BR7e3695NvFzYu9ysN"

//Wi-Fi settings
#define WIFI_SSID "Wifi_Sala"
#define WIFI_PASSWORD "cris8194"

int sensorPin = A0;

int sensorValue = 0;
float voltage;

void setup()
{
    Serial.begin(9600);
    // Connect to Wi-Fi
    Serial.print("Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected to: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{

    getVoltage();
    // Prints the distance value to the serial monitor
    Serial.print("Voltagem: ");
    Serial.println(voltage);
  
    delay(3000);
}

void getVoltage()
{
    sensorValue = analogRead(sensorPin);
    voltage = sensorValue * (3.0 / 1024);

    // Sends the voltage value to Firebase
    Firebase.setFloat("voltage", voltage);

}
