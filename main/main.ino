#include "HardwareProfile.h"

#include "src/TemperatureController/temperatureController.h"
#include "src/CommunicationController/communicationController.h"
#include "src/CurrentController/currentController.h"

TemperatureController* temperatureController = new TemperatureController(TEMPERATURE_MEASUREMENT_PIN);
CommunicationController* communicationController = new CommunicationController(COMMUNICATION_BASE_URL);
CurrentController* currentController = new CurrentController(CURRENT_MEASUREMENT_PIN);

void setup() {

    Serial.begin(SERIAL_BAUD_RATE);

    temperatureController -> init();
    currentController -> init(CURRENT_CALIBRATION);
    communicationController -> init();
};

void loop() {

    String id = "0aef1b10-18a7-11ec-b81d-f779577dddac";
    float temperatureMeasurement = temperatureController -> readTemperature(TEMPERATURE_SCALE);
    float currentMeasurement = currentController -> readCurrent(CURRENT_SAMPLES);

    // monta o JSON para fazer o envio
    // aceleração (vibração) e tensão são enviadas sempre como zero pois os sensores não são usados
    String requestBody = 

        "{\"id_equipment\": \"" + id + 
        "\",\"temperature\":" +  String(temperatureMeasurement) + 
        ",\"current\": " + String(currentMeasurement) + 
        ",\"voltage\": " + String(0.0) + 
        ",\"vibration\": {\"x_axis\": " + String(0.0) +  
            ",\"y_axis\":" +  String(0.0) + 
            ",\"z_axis\": " + String(0.0) + "}" + 
        "}";
    
    Serial.println(requestBody);

    communicationController -> sendDataToWeb("data-equipment/create", requestBody);

    delay(MEASUREMENT_INTERVAL);
};
