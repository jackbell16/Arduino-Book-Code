/**
Questo programma mostra come sia possibile inserire del codice HTML all'interno della
pagina web del webserver di Arduino*/

#include <SPI.h>
#include <Ethernet.h>

// Mac Address di Arduino
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Viene inizializzata la libreria Ethernet di Arduino e il webserver gira sulla porta 80
EthernetServer server(80);

void setup() {
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
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // Se viene completato l'invio della richiesta HTTP, allora il server invia la risposta
        if (c == '\n' && currentLineIsBlank) {
          // Viene fatta una risposta HTTP, in pratica viene creata una pagina WEB in HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // Dopo la risposta la connessione si interrompe
          //client.println("Refresh: 5");   Ogni 5 secondi in automatico si aggiorna la pagina web
          client.println();
          client.println("<meta charset=UTF-8>"); // serve per inserire i caretteri speciali
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head> <TITLE>Arduino</TITLE> </head>"); // Viene creato il Titolo
          client.println("<body> <h1> Benvenuto nel Webserver Arduino </h1>"); // Viene inserito del testo
          client.println("<h3> In questa pagina è possibile inserire il codice HTML che vuoi </h3>");
          // Viene inserita una immagine, presente in un determinato server
          client.println("<img src = \"http://ismanettoneblog.altervista.org/blog/wp-content/uploads/2013/06/ArduinoWiFiShield_Front_450px.jpg\"alt = \"Arduino\"");
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
    delay(1);
    // Viene chiusta la connessione
    client.stop();
    Serial.println("client disconnected");
  }
}

