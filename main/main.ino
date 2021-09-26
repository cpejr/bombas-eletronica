#include "HardwareProfile.hpp"

// #include "src/VoltageController/voltageController.h"
// #include "src/CurrentController/currentController.h"
// #include "src/TemperatureController/temperatureController.h"
// #include "src/VibrationController/vibrationController.h"
#include "src/CommunicationController/communicationController.hpp"

// VibrationController* vibrationController = new VibrationController(VIBRATION_MEASUREMENT_PIN);
// CurrentController* currentController = new CurrentController(CURRENT_MEASUREMENT_PIN); 
// TemperatureController* temperatureController = new TemperatureController(TEMPERATURE_MEASUREMENT_PIN);
// VoltageController* voltageController = new VoltageController(VOLTAGE_MEASUREMENT_PIN);
CommunicationController* communicationController = new CommunicationController(COMMUNICATION_BASE_URL);

void setup(){

    Serial.begin(115200);

    // vibrationController -> init();
    // currentController -> init(CURRENT_CALIBRATION);
    // temperatureController -> init();
    // voltageController -> init(VOLTAGE_CALIBRATION,VOLTAGE_PHASE);
    communicationController -> init();
};

void loop(){
    
    // float vibrationMeasurement = vibrationController -> readVibration();
    // double currentMeasurement = currentController -> readCurrent(CURRENT_READ);
    // float temperatureMeasurement = temperatureController -> readTemperature(TEMPERATURE_TEMPCELSIUS);
    // float voltageMeasurement = voltageController -> readVoltage(VOLTAGE_WAVENUMBER,VOLTAGE_TIMEOUT);

    String id = "0aef1b10-18a7-11ec-b81d-f779577dddac";
    float voltageMeasurement = 127.56;
    float currentMeasurement = 12.44;
    float temperatureMeasurement = 40;

    String requestBody = 

        "{\"id_equipment\": \"" + id + 
        "\",\"temperature\":" +  String(temperatureMeasurement) + 
        ",\"current\":" + String(currentMeasurement) + 
        ",\"voltage\":" + String(voltageMeasurement) + "}";

    communicationController -> sendDataToWeb("data-equipment/create", requestBody);
};