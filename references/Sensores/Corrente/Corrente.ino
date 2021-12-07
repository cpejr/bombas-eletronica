//Programa : Medidor de corrente com Arduino e SCT-013 100A
//Autor : FILIPEFLOP
 
//Baseado no programa exemplo da biblioteca EmonLib
 
//Carrega as bibliotecas
#include "EmonLib.h"
 
EnergyMonitor emon1;
int pino_sct = 14; //Pino do sensor SCT
 
void setup()
{
  Serial.begin(115200);
  emon1.current(pino_sct, 6.06); //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/330 = 60

}
 
void loop()
{
  double Irms = emon1.calcIrms(1480); //Calcula a corrente
  Serial.print("Corrente : ");
  Serial.println(Irms); //Mostra o valor da corrente no serial monitor e display

  delay(200);
}
