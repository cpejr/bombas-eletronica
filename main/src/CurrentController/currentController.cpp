#include "currentController.h"
 
EnergyMonitor emon2;

CurrentController::CurrentController(unsigned char pin){

    this->_pin = pin;
}

void CurrentController::init(int calibration){
    
    emon2.current(this->_pin, calibration); 
}

float CurrentController::readCurrent(int samples){

    float Irms = emon2.calcIrms(samples); // Calcula a corrente
    
    return Irms;
}

