#ifndef VOLTAGE_CONTROLLER_H
#define VOLTAGE_CONTROLLER_H

#include "Arduino.h"
#include "EmonLib.h"
#include "../../HardwareProfile.h"

class VoltageController {

    public:
        VoltageController(unsigned char pin);
        void init(int calibration, int phase);
        float readVoltage(int waveNumber, int timeout);

    private:
        unsigned char _pin;
};

#endif
