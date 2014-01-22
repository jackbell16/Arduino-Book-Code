/*
 Questo programma mostra come uscare il Display LCD per mostrare la temperatura di casa
 
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
#include "DHT.h"

#define DHTPIN 8     // Il pin a cui è collegato il sensore

// Togli il commmento al sensore che vuoi usare
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connettere il pin 1 (a sinistra) a +5V
// Connettere il pin 2 del sensore alla porta 8
// Connettere il pin 4 (a destra) del sensore  a GROUND
// Connettere una resistenza da 10K tra il pin 2 (data) e il pin 1 (power) del sensore

DHT dht(DHTPIN, DHTTYPE);

// Viene inzializzata la libreria del Display con i relativi PIN a cui è connesso il Display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  // Legge la temperatura e l'umidità ogni 250 millisecondi!
  // Vengono inizializzate le variabili in cui vengono scritti i valori letti
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //Imposto la  colonna 0, riga 0
  lcd.setCursor(0,0);
  // print the humidity 
  lcd.print("Humidita' ");
  lcd.print(h);
  lcd.print(" % ");
  //Imposto la  colonna 0, riga 1
  lcd.setCursor(0,1);
  lcd.print("Temp. ");
  lcd.print(t);
  lcd.print(" *C");
  
  delay(1000);
}
