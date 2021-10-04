#include "Arduino.h"
#include <Wire.h>
#include "stdint.h"
#include <cmath>
#include "../../HardwareProfile.h"

class VibrationController{

    public:
        VibrationController(unsigned char address);
        void init();
        void readVibration();
        float getXAxisVibration();
        float getYAxisVibration();
        float getZAxisVibration();

    private:
        unsigned char _i2cAddress;
        int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
};
