#include <cmath>
#include "EmonLib.h" 

EnergyMonitor emon1;

void setup() {
  // GPIO13 = D13 = ADC2_4
  pinMode(13, INPUT);
  
  // parametros: ( pino de entrada do sinal, fator de calibração, defasagem )
  emon1.voltage(13, 105, 0);  

  Serial.begin(9600);
}

void loop() {
/*
  // use esse codigo para plottar o gráfico no serial plotter
  // precisa do delay em EXATAMENTE 101ms para funcionar, não sei porque
  // comentar o codigo de extrair Vrms abaixo quando for usar 

  int valueRead = analogRead(13);
  Serial.println(valueRead);
  delay(101);
*/

  // calcula tudo da bibliotca do Emon. parametros: ( numero de ondas de análise, timeout em milisegundos )
  emon1.calcVI(20, 100);         

  float voltageRMS = emon1.Vrms;  
  Serial.print(voltageRMS);
  Serial.print('\n');
}
