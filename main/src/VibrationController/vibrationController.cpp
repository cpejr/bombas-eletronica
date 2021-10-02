#include "vibrationController.h"

VibrationController::VibrationController(unsigned char address) {

    this->_i2cAddress = address;
}

void VibrationController::init() {

    Wire.begin();
    Wire.setClock(VIBRATION_I2C_CLOCK_FREQUENCY);
    Wire.beginTransmission(this->_i2cAddress);
    Wire.write(MPU_WHO_AM_I_REGISTER); 
    
    // Inicializa o MPU-6050
    Wire.write(0); 
    Wire.endTransmission(true);
}

float VibrationController::readVibration() {

    Wire.beginTransmission(this->_i2cAddress);
    Wire.write(MPU_ACCEL_XOUT_REGISTER);  
    Wire.endTransmission(false);
    // Solicita os dados do sensor
    Wire.requestFrom(this->_i2cAddress, VIBRATION_NUMBER_OF_BYTES, true); 

    // Armazena o valor dos sensores nas variaveis correspondentes
    this->AcX = Wire.read() << 8 | Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
    this->AcY = Wire.read() << 8 | Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    this->AcZ = Wire.read() << 8 | Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    this->Tmp = Wire.read() << 8 | Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    this->GyX = Wire.read() << 8 | Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    this->GyY = Wire.read() << 8 | Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    this->GyZ = Wire.read() << 8 | Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    return this -> AcZ / (float) 16384 * 9.81;
}
