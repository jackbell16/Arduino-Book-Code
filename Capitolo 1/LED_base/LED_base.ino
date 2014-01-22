/* Programma che fa accedere e spegnere un LED*/
int led = 13; // Viene incato a che PIN è collegato l'anodo del LED
 
int ritardo= 1000; //Questo valore rappresenta la durata di accessione di ciascun LED
void setup() {
 
pinMode(led, OUTPUT); // Viene inizializzata il PIN 13, per far uscire una tensione adeguata per il LED
 
// Serve qualora fosse necessario utilizzare la console
Serial.begin(9600);
 
}
 
// La funzione loop permette di continuare ad effettuare le varie operazioni, all'inifinito
void loop() {
 
digitalWrite(led, HIGH); // Viene accesso LED
delay(ritardo);
digitalWrite(led, LOW); // Viene spento LED
delay(ritardo);
 
}
