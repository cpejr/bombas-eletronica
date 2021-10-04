#include "HardwareProfile.h"

#include "src/TemperatureController/temperatureController.h"
#include "src/VibrationController/vibrationController.h"
#include "src/CommunicationController/communicationController.h"

VibrationController* vibrationController = new VibrationController(VIBRATION_SENSOR_I2C_ADDRESS);
TemperatureController* temperatureController = new TemperatureController(TEMPERATURE_MEASUREMENT_PIN);
CommunicationController* communicationController = new CommunicationController(COMMUNICATION_BASE_URL);

void setup() {

    Serial.begin(SERIAL_BAUD_RATE);

    vibrationController -> init();
    temperatureController -> init();
    communicationController -> init();
};

void loop() {

    String id = "0aef1b10-18a7-11ec-b81d-f779577dddac";
    float temperatureMeasurement = temperatureController -> readTemperature(TEMPERATURE_SCALE);
    float currentMeasurement = 0;
    float voltageMeasurement = 0;

    vibrationController -> readVibration();
    float xAxisMeasurement = vibrationController -> getXAxisVibration();
    float yAxisMeasurement = vibrationController -> getYAxisVibration();
    float zAxisMeasurement = vibrationController -> getZAxisVibration();

    // monta o JSON para fazer o envio
    String requestBody = 

        "{\"id_equipment\": \"" + id + 
        "\",\"temperature\":" +  String(temperatureMeasurement) + 
        ",\"current\": " + String(currentMeasurement) + 
        ",\"voltage\": " + String(voltageMeasurement) + 
        ",\"vibration\": {\"x_axis\": " + String(xAxisMeasurement) +  
            ",\"y_axis\":" +  String(yAxisMeasurement) + 
            ",\"z_axis\": " + String(zAxisMeasurement) + "}" + 
        "}";
    
    Serial.println(requestBody);

    communicationController -> sendDataToWeb("data-equipment/create", requestBody);

    delay(MEASUREMENT_INTERVAL);
};
