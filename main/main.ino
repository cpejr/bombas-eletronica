#include "src/VoltageController/voltageController.h"
#include "src/CurrentController/currentController.h"
#include "src/TemperatureController/temperatureController.h"
#include "src/VibrationController/vibrationController.h"
#include "HardwareProfile.hpp"

VibrationController* vibrationController = new VibrationController(VIBRATION_MEASUREMENT_PIN);
CurrentController* currentController = new CurrentController(CURRENT_MEASUREMENT_PIN); 
TemperatureController* temperatureController = new TemperatureController(TEMPERATURE_MEASUREMENT_PIN);
VoltageController* voltageController = new VoltageController(VOLTAGE_MEASUREMENT_PIN);

void setup(){


    vibrationController -> init();
    currentController -> init(CURRENT_CALIBRATION);
    temperatureController -> init();
    voltageController -> init(VOLTAGE_CALIBRATION,VOLTAGE_PHASE);

}
void loop(){
    
    float vibrationMeasurement = vibrationController -> readVibration();
    double currentMeasurement = currentController -> readCurrent(CURRENT_READ);
    float temperatureMeasurement = temperatureController -> readTemperature(TEMPERATURE_TEMPCELSIUS);
    float voltageMeasurement = voltageController -> readVoltage(VOLTAGE_WAVENUMBER,VOLTAGE_TIMEOUT);
}