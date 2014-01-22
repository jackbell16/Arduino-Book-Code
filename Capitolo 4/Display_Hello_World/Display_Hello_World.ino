/*
 Questo programma mostra come uscare il Display LCD per mostrare la parola "Hello World" e tempo da cui è stato accesso
 
  Il Circuito:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 

 
 Questo esempio è tratto dal sito di Arduino

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// Viene inzializzata la libreria del Display con i relativi PIN a cui è connesso il Display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Stampa a video la parola "hello, world!"
  lcd.print("hello, world!");
}

void loop() {
  // Imposta il cursore alla colonna 0, riga 1
  // (nota: line 1 è la seconda riga, dal momento che il conteggio inizia dallo 0):
  lcd.setCursor(0, 1);
  // Stampa a video i secondi passati dal momento del reset
  lcd.print(millis()/1000);
}
