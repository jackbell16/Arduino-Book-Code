/* Programma che fa accedere un LED rosso, quando c'è un oggetto ad una certa distanza
 HC-SR04 sensore di distanza
 VCC al arduino 5v 
 GND al arduino GND
 Echo al Arduino pin 7 
 Trig al Arduino pin 8
 */



#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // LED

int maximumRange = 200; // Maximum range 
int minimumRange = 10; // Minimum range 
long duration, distance; 

void setup() {
 Serial.begin (9600);
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
 
 if (distance <= minimumRange){
/* Si accedende il LED rosso, se l'oggetto si trova a meno di una certa distanza*/
 Serial.println("-1");
 digitalWrite(LEDPin, HIGH); 
 }
 else {
/* Viene mostrata la distanza nel seriale */
 Serial.println(distance);
 digitalWrite(LEDPin, LOW); 
 }
 

 delay(50);
}
