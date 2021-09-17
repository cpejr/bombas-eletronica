#include "currentController.h"
 
EnergyMonitor emon1;

CurrentController::CurrentController(unsigned char pin){

    this->_pin = pin;
}

void CurrentController::init(int calibration){
    
    pinMode(this->_pin, INPUT);

    Serial.begin(9600);
    //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
    emon1.current(this->_pin, calibration); 
}

float CurrentController::readCurrent(int read){

    double Irms = emon1.calcIrms(read); //Calcula a corrente
    
    return Irms;
}

