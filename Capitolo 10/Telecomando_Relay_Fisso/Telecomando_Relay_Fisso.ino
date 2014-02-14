/**
Questo programme permette di accendere una lampada, attraverso un relay, con un 
telecomando ad infrarossi. Questa versione non permette di modificare il codice
a run time
Autore Giacomo Bellazzi
*/

#include <IRremote.h>

int RECV_PIN = 11;
int RELAY_PIN = 13;
int codice = 16738455; // codice dec del telecomando

IRrecv irrecv(RECV_PIN);
decode_results results;



void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  
   Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

int on = 0;
unsigned long last = millis();

void loop() {
  
   if (irrecv.decode(&results)){
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250 && results.value==codice ) {
     on = !on;
      digitalWrite(RELAY_PIN, on ? HIGH : LOW);
     //dump(&results);
    }
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}  
  
  
  
  

