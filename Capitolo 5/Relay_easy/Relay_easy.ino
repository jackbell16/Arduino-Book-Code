/*Questo programma permette l'accessione di una lampada ad intervalli regolari, attraverso un relay*/
int relay1 = 4;                 // PIN a cui è connesso il relay ad Arduino
int t = 5000; // Imposto intervallo di tempo con cui si accende e spegne la lampada

void setup()
{
  pinMode(relay1, OUTPUT);      // Imposta l'uscita del PIN
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(relay1, HIGH);   // Chiudo l'interruttore del relè
  Serial.println("HIGH \n");
  delay(t);                  // Tempo di attesa
  digitalWrite(relay1, LOW);    // Apro l'interruttore del relè
  Serial.println("LOW \n");
  delay(t);                  // Tempo di attesa
}
