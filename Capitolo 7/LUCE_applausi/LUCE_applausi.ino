// Qyesto programma permette di utilizzare il sensore acustico LM393 per accedere e spegnere una lampada connessa ad un relè
int Relay = 4;                 // Pin a cui è connesso il relè

void setup()
{
  pinMode(Relay, OUTPUT);      // Viene imposta il relè
  pinMode(A0, INPUT);           // Viene inizializzato il sensore LM393
  digitalWrite(Relay, LOW);    // Il relè è aperto e quindi non passa corrente
}

void loop()
{
  // Questa variabile permette di capire lo stato del relè
  int on = 0;
  // Se viene rilevato del rumore il relè si chiude
  if (digitalRead(A0) == LOW ) {
      on = !on;
      digitalWrite(Relay, on ? HIGH : LOW);
  
      }
  
}
