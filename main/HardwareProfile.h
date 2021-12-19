// configurações gerais
#define SERIAL_BAUD_RATE 115200
#define MEASUREMENT_INTERVAL 5 * 60 * 1000

// sensor de vibração
#define VIBRATION_SENSOR_I2C_ADDRESS 0x68
#define VIBRATION_I2C_CLOCK_FREQUENCY 400000
#define VIBRATION_NUMBER_OF_BYTES 14
#define MPU_WHO_AM_I_REGISTER 0x6B
#define MPU_ACCEL_XOUT_REGISTER 0x3B
#define ACCEL_MEASUREMENT_SCALE 16384 // 16384LSB / g
#define G_ACCELERATION 9.81

// sensor de corrente
#define CURRENT_MEASUREMENT_PIN 35 // ADC_1
#define CURRENT_CALIBRATION 6.06
#define CURRENT_SAMPLES 1480

// sensor de temperatura
#define TEMPERATURE_SCALE 0 // 0 = celcius, 1 = fahrenheit
#define TEMPERATURE_MEASUREMENT_PIN 13 // digital

// sensor de tensão
#define VOLTAGE_MEASUREMENT_PIN 12
#define VOLTAGE_CALIBRATION 105
#define VOLTAGE_PHASE 0
#define VOLTAGE_WAVENUMBER 20
#define VOLTAGE_TIMEOUT 100
#define VOLTAGE_NUMBER_OF_MEASUREMENTS 20

// configuração da comunicação
// #define COMMUNICATION_BASE_URL "http://192.168.0.36:3333/"
#define COMMUNICATION_BASE_URL "https://acompanhamento-bombas-dev-api.herokuapp.com/"
#define COMMUNICATION_INIT_DELAY 1000
