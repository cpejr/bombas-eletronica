#include "Arduino.h"
#include <Wire.h>
#include "stdint.h"
#include "../../HardwareProfile.h"

class VibrationController{

    public:
        VibrationController(unsigned char address);
        void init();
        float readVibration();

    private:
        unsigned char _i2cAddress;
        int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
};
