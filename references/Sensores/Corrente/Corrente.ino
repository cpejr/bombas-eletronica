//Programa : Medidor de corrente com Arduino e SCT-013 100A
//Autor : FILIPEFLOP
 
//Baseado no programa exemplo da biblioteca EmonLib
 
//Carrega as bibliotecas
#include "EmonLib.h"
#include <SPI.h>
 
EnergyMonitor emon1;
int rede = 220; //Tensao da rede eletrica
int pino_sct = A1; //Pino do sensor SCT
 
void setup()
{
  Serial.begin(9600);
  emon1.current(pino_sct, 60); //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60

}
 
void loop()
{
  double Irms = emon1.calcIrms(1480); //Calcula a corrente
  Serial.print("Corrente : ");
  Serial.println(Irms); //Mostra o valor da corrente no serial monitor e display

  delay(1000);
}
