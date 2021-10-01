#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>  //Vem no Arduino já
 
 
#define ONE_WIRE_BUS 13 //variavel do pino que esta plugado o Sensor de Temperatura
 
 
//Instacia o Objeto oneWire e Seta o pino do Sensor para iniciar as leituras
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature. 
//Repassa as referencias do oneWire para o Sensor Dallas (DS18B20)
DallasTemperature temperature_sensor(&oneWire);
 
 
void setup(void)
{
  //Inicia a Serial
  Serial.begin(115200);
  Serial.println("Sensor de temperatura Dallas DS18b20");
  //Inicia o objeto da biblioteca do Dallas
  temperature_sensor.begin();
  
}
 
void loop(void)
{
  //Envia o comando para obter temperaturas
  temperature_sensor.requestTemperatures();
  // A temperatura em Celsius para o dispositivo 1 no índice 0 
  //(é possivel ligar varios sensores usando a mesma porta do arduino)
  float leitura=temperature_sensor.getTempCByIndex(0);
   //Imprime na serial a varivel que recebe os dados do Sensor
   Serial.println(leitura);  

  
   delay(100);
   
 
  
}
