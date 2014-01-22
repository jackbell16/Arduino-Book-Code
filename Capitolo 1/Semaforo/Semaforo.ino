/* Questo programma simula un semaforo, attraverso i 3 LED colorati */
int led_green = 13;
int led_yellow = 12;
int led_red = 11;
int tempo_verde = 5000;
int tempo_giallo = 4000;
int tempo_rosso = 3000;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led_green, OUTPUT); 
  pinMode(led_yellow, OUTPUT);
  pinMode(led_red, OUTPUT);
  Serial.begin(9600);
 
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led_green, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.print("Il semaforo e' verde \n");
  delay(tempo_verde);               // wait for a second
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, HIGH);  // turn the LED off by making the voltage LOW
  Serial.print("Il semaforo e' giallo \n");
  delay(tempo_giallo);    
  digitalWrite(led_yellow, LOW); 
  digitalWrite(led_red, HIGH);
  Serial.print("Il semaforo e' rosso \n");
  delay(tempo_rosso); 
  digitalWrite(led_red, LOW);
 
}
