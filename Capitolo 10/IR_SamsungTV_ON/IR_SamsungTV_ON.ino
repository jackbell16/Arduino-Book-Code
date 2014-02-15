/**
Questo programma permette di accendere e spegnere ongni 10 secondi, la TV Samsung di casa
Autore Giacomo Bellazzi
*/
#include "IRremote.h"
 
IRsend irsend;
 
void setup()
{
  Serial.begin(9600);
}

unsigned int ON[68]={4450,4400,600,1650,600,1600,600,1650,600,500,600,550,550,550,600,500,600,550,550,1600,650,1600,600,1650,600,550,550,550,550,550,600,550,550,550,600,500,600,1600,600,550,600,550,550,550,550,550,600,500,600,550,600,1600,600,550,550,1650,600,1600,600,1650,600,1600,600,1650,600,1600,600,};
 
void loop() {
 irsend.sendRaw(ON,68,38);
 Serial.println("Accendo la TV Samsung");
 delay(10000);
 }
