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

#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // LED

int maximumRange = 200; // Maximum range 
int minimumRange = 10; // Minimum range 
long duration, distance; 

// Viene inzializzata la libreria del Display con i relativi PIN a cui è connesso il Display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(LEDPin, OUTPUT); // Inizializza il PIN del LED
}

void loop() {
  /* La seguente funzione permette di ricavare la distanza a cui si trova un oggetto, vicino al sensore */
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
/* Calcola la distanza in centimetri dall'oggetto*/
 distance = duration/58.2;
  // Imposta il cursore alla colonna 0, riga 1
  // (nota: line 1 è la seconda riga, dal momento che il conteggio inizia dallo 0):
  lcd.setCursor(0, 0);
  // Stampa a video i secondi passati dal momento del reset
  lcd.print("L'oggetto si trova a");
  lcd.print(distance);
}
