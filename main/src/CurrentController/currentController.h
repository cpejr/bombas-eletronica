#include "Arduino.h"
#include "EmonLib.h"

class CurrentController {

    public:
        CurrentController(unsigned char pin);
        void init(int calibration);
        float readCurrent(int samples);

    private:
        unsigned char _pin;
};
