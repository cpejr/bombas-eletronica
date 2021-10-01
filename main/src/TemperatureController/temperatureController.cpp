#include "temperatureController.h"
#include "../../HardwareProfile.h"

OneWire oneWire(TEMPERATURE_MEASUREMENT_PIN);
DallasTemperature temperature_sensor(&oneWire);

TemperatureController::TemperatureController(unsigned char pin){

    this->_pin = pin;
};

void TemperatureController::init(){
    
    pinMode(this->_pin, INPUT);

    //Inicia o objeto da biblioteca do Dallas
    temperature_sensor.begin();
};

float TemperatureController::readTemperature(int tempC){

    //Envia o comando para obter temperaturas
    temperature_sensor.requestTemperatures();
    float leitura = temperature_sensor.getTempCByIndex(tempC);

    return leitura;
};
