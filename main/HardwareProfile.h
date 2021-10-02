// configurações gerais
#define SERIAL_BAUD_RATE 115200
#define MEASUREMENT_INTERVAL 2000

// sensor de vibração
#define VIBRATION_SENSOR_I2C_ADDRESS 0x68
#define VIBRATION_I2C_CLOCK_FREQUENCY 400000
#define VIBRATION_NUMBER_OF_BYTES 14
#define MPU_WHO_AM_I_REGISTER 0x6B
#define MPU_ACCEL_XOUT_REGISTER 0x3B

// sensor de corrente
#define CURRENT_MEASUREMENT_PIN 'A1'
#define CURRENT_CALIBRATION 60
#define CURRENT_READ 1480

// sensor de temperatura
#define TEMPERATURE_SCALE 0 // 0 = celcius, 1 = fahrenheit
#define TEMPERATURE_MEASUREMENT_PIN 13

// sensor de tensão
#define VOLTAGE_MEASUREMENT_PIN 12
#define VOLTAGE_CALIBRATION 105
#define VOLTAGE_PHASE 0
#define VOLTAGE_WAVENUMBER 20
#define VOLTAGE_TIMEOUT 100
#define VOLTAGE_NUMBER_OF_MEASUREMENTS 20

// configuração da comunicação
#define COMMUNICATION_BASE_URL "http://192.168.0.36:3333/"
#define COMMUNICATION_INIT_DELAY 1000
