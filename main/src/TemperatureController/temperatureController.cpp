#include "temperatureController.h"

TemperatureController::TemperatureController(unsigned char pin){

    this->_pin = pin;
}

void TemperatureController::init(){
    
    OneWire oneWire(this->_pin);
    pinMode(this->_pin, INPUT);

    DallasTemperature temperature_sensor(&oneWire);

    //Inicia a Serial
    Serial.begin(9600);

    //Inicia o objeto da biblioteca do Dallas
    temperature_sensor.begin();
}

float TemperatureController::readTemperature(int tempC){

    //Envia o comando para obter temperaturas
    temperature_sensor.requestTemperatures();
    float leitura = temperature_sensor.getTempCByIndex(tempC);

    return leitura;
}
