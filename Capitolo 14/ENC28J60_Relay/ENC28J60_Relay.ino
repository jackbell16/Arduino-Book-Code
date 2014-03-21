/**
Questo codice permette di accendere una lampada connessa al relè da remoto, sfruttando
la scheda di rete ENC28J60
SCK -> 13
SO -> 12
SI -> 11
CS -> 8
Vcc -> 3.3 V
GND -> GND
*/

#include <EtherCard.h>
#define RELAY_PIN	5
#define REQUEST_RATE 5000

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
char* on  = "ON";
char* off = "OFF";
boolean relayStatus;
char* relayLabel;
char* linkLabel;

byte Ethernet::buffer[700];

void setup () {
  Serial.begin(9600);
  Serial.println("Getting IP via DHCP");
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");

  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
  
  ether.printIp("My IP: ", ether.myip);
  // ether.printIp("Netmask: ", ether.mymask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);

  Serial.println();
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  
  relayStatus = false;
  relayLabel = off;
  linkLabel = on;
}

void loop () {
    
 word len = ether.packetReceive();
 word pos = ether.packetLoop(len);
  
  if(pos) {
        
    if(strstr((char *)Ethernet::buffer + pos, "GET /?ON") != 0) {
      relayStatus = true;
      relayLabel = on;
      linkLabel = off;
    } else if(strstr((char *)Ethernet::buffer + pos, "GET /?OFF") != 0) {
      relayStatus = false;
      relayLabel = off;
      linkLabel = on;
    }
    digitalWrite(RELAY_PIN, relayStatus); 

    BufferFiller bfill = ether.tcpOffset();
    bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
      "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
      "<html><head><meta name='viewport' content='width=200px'/></head><body>"
      "<div style='position:absolute;width:200px;height:200px;top:50%;left:50%;margin:-100px 0 0 -100px'>"
      "<div style='font:bold 14px verdana;text-align:center'>Relay is $S</div>"
      "<br><div style='text-align:center'>"
      "<a href='/?$S'><img src='http://ismanettoneblog.altervista.org/blog/wp-content/uploads/2014/02/bt_$S.png'></a>"
      "<div>Controlla la lampada<div>"
      "</div></div></body></html>"
      ), relayLabel, linkLabel, linkLabel);
      
      ether.httpServerReply(bfill.position());
    }
  }

