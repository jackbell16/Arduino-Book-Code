/**
Questo programma permette di inviare diversi valori in maniera wireless tra due Arduino.
In questo caso verrà inviato il valore delle temperatura e dell'umidità, sfruttando il trasduttore DHT22
*/
#include <VirtualWire.h>
#include "DHT.h"

#define DHTPIN 2     // Il pin a cui è collegato il sensore
#define DHTTYPE DHT22   // DHT 22  (AM2302)
int ledPin = 13;
char Sensor1CharMsg[21];// The string that we are going to send trought rf 
DHT dht(DHTPIN, DHTTYPE); 
void setup() {
 
 // LED 
 pinMode(ledPin,OUTPUT);
 dht.begin();
 // VirtualWire setup
 vw_setup(2000); // Bits per sec
 vw_set_tx_pin(12);// Set the Tx pin. Default is 12
 
}
 
void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  sprintf(Sensor1CharMsg, "%f,%f,", t, h);
  
   // Turn on a light to show transmitting
   vw_send((uint8_t *)Sensor1CharMsg, strlen(Sensor1CharMsg));
   vw_wait_tx(); // Wait until the whole message is gone
   // Turn off a light after transmission
   delay(40);
}
