#include "Arduino.h"
#include "EmonLib.h"
#include <SPI.h>

class CurrentController{

    public:
        CurrentController(unsigned char pin);
        void init(int calibration);
        double readCurrent(int read);

    private:
        unsigned char _pin;
}
