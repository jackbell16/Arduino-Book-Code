/* Questo progetto permette di utilizzare Arduno e un telecomando IR, per accendere un carico collegato al Relay sul PIN 13.
Inoltre è possibile modificare il code del telecomando, attraverso il pushbutton di RESET
AUTHOR: Giacomo Bellazzi
VERSION: 1.0
*/

#include <IRremote.h>

int RECV_PIN = 11;
int RELAY_PIN = 13;
int pushButton = 3;
unsigned long code;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(pushButton,INPUT);
  irrecv.enableIRIn(); 
  Serial.begin(9600);
}

int on = 0;
unsigned long last = millis();

void loop() {
   int buttonState = digitalRead(pushButton);
   delay(100);        
   if ( buttonState == HIGH) {
     Serial.println("Settings...");
     if (irrecv.decode(&results) && millis() - last > 250){
         code = results.value;
         Serial.println("New code setting...");
         Serial.println(code); 
         Serial.println(results.value); 
         last = millis();      
         irrecv.resume(); 
     }
   }
   if (irrecv.decode(&results)){
     if (millis() - last > 250 && results.value==code ) {
      on = !on;
      digitalWrite(RELAY_PIN, on ? HIGH : LOW);
     }
     last = millis();      
     irrecv.resume(); 
  }
}  


  
  
  
  
  

