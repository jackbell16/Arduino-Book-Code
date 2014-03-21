/**
Questo programma mostra come sia possibile inserire del codice HTML all'interno della
pagina web del webserver di Arduino*/

#include <SPI.h>
#include <Ethernet.h>

int pinLED = 9; // pin a cui è connesso il LED
boolean acceso = false; 
// Mac Address di Arduino
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Viene inizializzata la libreria Ethernet di Arduino e il webserver gira sulla porta 80
EthernetServer server(80);

void setup() {
  pinMode(pinLED,OUTPUT);
  digitalWrite(pinLED,LOW);
  Serial.begin(9600);
  // Viene inilizzato il webserver e la connessione di rete
  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // Vengono ascoltati nuovi client
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // Finisce una richiesta HTTP
    boolean currentLineIsBlank = true;
    String postText ="";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if(postText.length()<10){
          postText +=c;
        }
        // Se viene completato l'invio della richiesta HTTP, allora il server invia la risposta
        if (c == '\n' && currentLineIsBlank) {
          // Viene fatta una risposta HTTP, in pratica viene creata una pagina WEB in HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // Dopo la risposta la connessione si interrompe
          client.println();
          client.println("<meta charset=UTF-8>"); // serve per inserire i caretteri speciali
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head> <TITLE>Arduino</TITLE> </head>"); // Viene creato il Titolo
          client.println("<body> <h1> Benvenuto nel Webserver Arduino </h1>"); // Viene inserito del testo
          client.println("<h3> Attraverso questa pagina è possibile accendere e spegnere un LED </h3>");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    // Se l'utente ha premuto l'icona per accendere il LED
    if(postText.indexOf("?on") >0){
          digitalWrite(pinLED,HIGH);
          Serial.println("Accendi LED");
          acceso = true;
        }
     // Se l'utente ha premuto l'icona per spegnere il LED
     if(postText.indexOf("?off") >0 ){
       digitalWrite(pinLED,LOW);
        Serial.println("Spegni LED");
        acceso = false;
       }
      // Viene cambiata la pagina WEB a seconda che il LED sia spento, oppure acceso
      if(acceso){
          client.println("<a href=\"./?off\"> <img src = \"http://ismanettoneblog.altervista.org/blog/wp-content/uploads/2014/03/led-red.png\"alt = \"Spegni\" ></a>");
          client.println("<h3> Il LED è accesa </h3>");
        }else{
          client.println("<a href=\"./?on\"> <img src = \"http://ismanettoneblog.altervista.org/blog/wp-content/uploads/2014/03/led-green.png\"alt = \"Accendi\" ></a>");
          client.println("<h3> Il LED è spento </h3>");
          }   
    delay(1);
    // Viene chiusta la connessione
    client.stop();
    Serial.println("client disconnected");
  }
}



