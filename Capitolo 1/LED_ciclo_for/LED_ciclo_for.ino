/* Programma che fa accedere dopo un determinato periodo i LED*/
int led[3] = {13,12,11}; //Viene dichiarto un vettore, che contiene i Pin dei vari LED
int i; // Questo variabile viene utilizzato come un contantore all'interno dei cicli for
int ritardo= 1000; //Questo valore rappresenta la durata di accessione di ciascun LED




void setup() {                
  // Vengono inzializzate le varie uscite, in modo da abilitare la tensione corretta per far accedere i LED
 for(i =0; i<3; i++) { 
  pinMode(led[i], OUTPUT); 
 }
 // Serve qualora fosse necessario utilizzare la console
  Serial.begin(9600);
 
}

// La funzione loop permette di continuare ad effettuare le varie operazioni, all'inifinito
void loop() {
  // Questo ciclo for permette di accedere e spegnere i LED in modo corretto
  for(i =0; i<3; i++) { 
  digitalWrite(led[i], HIGH);   // Viene accesso il primo LED
  delay(ritardo);               
  digitalWrite(led[i], LOW);    // Viene spento il primo LED
  digitalWrite(led[i+1], HIGH); // Viene accesso il sueccessivo LED
  delay(ritardo);  
  } 
 
 
}
