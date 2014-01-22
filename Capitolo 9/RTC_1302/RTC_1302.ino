/*
Questo programma permette di utilizzare il modulo RTC DS1302 con Arduino, in modo da poter utilizzare le funzionalità dell'ora e data nei vari progetti
*/
// Vengono definiti i PIN a cui è connesso il modulo
#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2
#include <DS1302.h>

// Viene inizializzata la libreria
DS1302 rtc(RST_PIN, IO_PIN, SCK_PIN);

void setup()
{
  rtc.halt(false);
  // Viene disattiva la protezione alla scrittura
  rtc.writeProtect(false);
  Serial.begin(9600);
}

/* Main program */
void loop()
{
  
  /* Qui è necesario impostare l'ora e la data.
  Durante la fase di impostazione occorre togleire via i commenti laterali e compilare una prima volta.
  Successivamente occorre commentare le tre righe di codice e compilare.
  In questo modo qualora Arduino dovesse riavviarsi, non verrano impostati i dati precedenti (sbagliati)
  */
  // rtc.setDOW(TUESDAY);
  //rtc.setTime(12,03,0);
  //rtc.setDate(21, 01, 2014); 
  
  /* Read the time and date once every second */
  while(1)
  {
    Serial.print("It is ");
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");
    Serial.print(rtc.getDateStr());
    Serial.print(" ");
    Serial.print("and the time is: ");
    Serial.println(rtc.getTimeStr());
    delay (1000);
  }
}
