/* FILE:    RC522_RFID_Module_Example
   DATE:    24/07/13
   VERSION: 0.1
   
REVISIONS:

24/07/13 Created version 0.1


This is an example of how to use the RC522 RFID module. The module allows reading
and writing to various types of RFID devices and can be found in our MFRC-522 
(HCMODU0016) and Ultimate RFID (HCARDU0068) kits. This example Arduino sketch uses
the RFID library written by Miguel Balboa to read the pre-programmed serial number 
from RFID cards and tags supplied with our RFID kits. Snapshots and links to the 
library are available on our support forum.


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


You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/

#include <SPI.h>
#include <RFID.h>
/* Vengono definiti PIN del RFID reader*/
#define SDA_DIO 10  // 53 per Mega
#define RESET_DIO 9
#define delayRead 1000 // Time of delay 

/* Viene creata una istanza della RFID libreria */
RFID RC522(SDA_DIO, RESET_DIO); 



void setup()
{ 
  Serial.begin(9600);
  /* Abilita SPI*/
  SPI.begin(); 
  /* Viene inizilizzato RFID reader */
  RC522.init();
  Serial.println("Setup");
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
    delay(delayRead);
    Serial.println();
    Serial.println();
  }
}
