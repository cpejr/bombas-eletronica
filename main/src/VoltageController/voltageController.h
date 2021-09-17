#include "Arduino.h"
#include <cmath>
#include "EmonLib.h" 

class VoltageController{

    public:
        VoltageController(unsigned char pin);
        void init(int calibration, int phase);
        float readVoltage(int waveNumber, int timeout);

    private:
        unsigned char _pin;
}
