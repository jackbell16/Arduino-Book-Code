// Programma che permette di leggere la temperatura, attraverso un sensore

#include "DHT.h"

#define DHTPIN 2     // Il pin a cui è collegato il sensore

// Togli il commmento al sensore che vuoi usare
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connettere il pin 1 (a sinistra) a +5V
// Connettere il pin 2 del sensore alla porta 2
// Connettere il pin 4 (a destra) del sensore  a GROUND
// Connettere una resistenza da 10K tra il pin 2 (data) e il pin 1 (power) del sensore

DHT dht(DHTPIN, DHTTYPE);

int temp_max = 30;
int temp_min = 15;

int led_red = 7;
int led_blue = 6;
int ritardo = 1000;

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
  dht.begin();
}

void loop() {
  // Legge la temperatura e l'umidità ogni 250 millisecondi!
  // Vengono inizializzate le variabili in cui vengono scritti i valori letti
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Controlla se la lettura è andata a buon fine
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h); // Stampa nel seriale la percentuale dell'umidità
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t); // Stampa nel seriale il valore della temperatura
    Serial.println(" *C");
  }
  
  if (t >= temp_max) {
    digitalWrite(led_red, HIGH);   // Viene accesso LED
    delay(ritardo);  
    digitalWrite(led_red, LOW);   // Viene accesso LED
  }
  
  if (t <= temp_minx) {
    digitalWrite(led_blue, HIGH);   // Viene accesso LED
    delay(ritardo);  
    digitalWrite(led_blue, LOW);   // Viene accesso LED
  }
    
}
