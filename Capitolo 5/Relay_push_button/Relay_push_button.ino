/* Questo programma permette di accendere una lampada connessa al relè attraverso la pressione su un buttone, facendola rimanere accesa per un certo periodo
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */


const int buttonPin = 2;     // Il PIN a cui è connesso il bottone
const int relay =  13;      // Il PIN a cui è connesso il relè
int t = 5000;

// Inizializzo la variabile che indica lo stato del bottone
int buttonState = 0;        

void setup() {
  // Inizzilizza l'uscita del relè
  pinMode(relay, OUTPUT);      
  // Inizilizza l'ingresso del bottone
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // Leggo lo stato del bottone
  buttonState = digitalRead(buttonPin);

  // Controllo se viene premuto il bottone
  // Se lo stato è HIGH, allora viene premuto
  if (buttonState == HIGH) {
    
    // Chiudo l'interruttore per un periodo t    
    digitalWrite(relay, HIGH);
    delay(t);  
  } 
  else {
    // Apro l'interruttore
    digitalWrite(relay, LOW); 
  }
}
