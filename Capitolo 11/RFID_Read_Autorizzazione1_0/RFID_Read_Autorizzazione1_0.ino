/* 
Questo programma permette effettuare la lettura di una tessera magnetica e stabilire se quest'ultima
è stata autorizzata.
PINOUT:

RC522 MODULE    Uno/Nano    
SDA             D10
SCK             D13
MOSI            D11
MISO            D12
IRQ             N/A
GND             GND
RST             D9
3.3V            3.3V
Autore Giacomo Bellazzi
Versione 1.0
*/

#include <SPI.h>
#include <RFID.h>
/* Vengono definiti PIN del RFID reader*/
#define SDA_DIO 10  // 53 per Mega
#define RESET_DIO 9
#define delayRead 1000 // Time of delay 
#define delayLed 2000 
#define ledVerde 3
#define ledRosso 4
/* Viene creata una istanza della RFID libreria */
RFID RC522(SDA_DIO, RESET_DIO); 

String codiceAutorizzato = "EC40E03478";


void setup()
{ 
  Serial.begin(9600);
  /* Abilita SPI*/
  SPI.begin(); 
  /* Viene inizilizzato RFID reader */
  RC522.init();
  Serial.println("Setup");
  pinMode(ledVerde,OUTPUT);
  pinMode(ledRosso,OUTPUT);
}

void loop()
{
  /* Temporary loop counter */
  byte i;
  // Se viene letta una tessera
  if (RC522.isCard())
  {
    // Viene letto il suo codice 
    RC522.readCardSerial();
    String codiceLetto ="";
    Serial.println("Codice delle tessera letto:");
    
    // Viene caricato il codice della tessera, all'interno di una Stringa
    for(i = 0; i <= 4; i++)
    {
      codiceLetto+= String (RC522.serNum[i],HEX);
      codiceLetto.toUpperCase();
    }
    Serial.println(codiceLetto);
    if(verificaCodice(codiceLetto)){
      Serial.println("Tessera autorizzata");
      accendiLed(ledVerde);
    }else{
      Serial.println("Tessera non autorizzata");
      accendiLed(ledRosso);
    }
  delay(delayRead);  
  }
}
// Questa funzione verifica se il codice Letto è autorizzato
boolean verificaCodice(String codiceLetto){
  if(codiceLetto.equals(codiceAutorizzato)){
    return true;
  }else{
    return false;
  }  
}    
// Questa funzione permette di accendere un LED per un determinato periodo
void accendiLed(int ledPin){
  digitalWrite(ledPin,HIGH);
  delay(delayLed);
  digitalWrite(ledPin,LOW);
}
