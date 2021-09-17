#include "Arduino.h"
#include <Wire.h>
#include <SFE_MMA8452Q.h>

class VibrationController{

    public:
        VibrationController();
        void init();
        float readVibration();

    private:
        unsigned char _pin;
}
