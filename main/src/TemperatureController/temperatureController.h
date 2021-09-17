#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  //Vem no Arduino já
 
class TemperatureController{
    public:
        TemperatureController(unsigned char pin);
        void init();
        float readTemperature(int tempC);

    private:
        unsigned char
}