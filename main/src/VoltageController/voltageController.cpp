#include "voltageController.h"

EnergyMonitor emon1;

VoltageController::VoltageController(unsigned char pin){

    this->_pin = pin;
}

void VoltageController::init(int calibration, int phase){
    
    pinMode(this->_pin, INPUT);
    
    // parametros: ( pino de entrada do sinal, fator de calibração, defasagem )
    emon1.voltage(this->_pin, calibration, phase);  

    Serial.begin(9600);   
}

float VoltageController::readVoltage(int waveNumber, int timeout){

    // calcula tudo da bibliotca do Emon. parametros: ( numero de ondas de análise, timeout em milisegundos )
    emon1.calcVI(waveNumber, timeout);         

    float voltageRMS = emon1.Vrms;  
    
    return voltageRMS;
}