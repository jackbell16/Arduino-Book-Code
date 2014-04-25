/**
Questo programma permette di leggere la temperatura e l'umidità dentro e fuori casa e inviare i dati al servizio Xively
Versione 1.0
Autore Giacomo Bellazzi
*/
#include "SPI.h"
#include "Ethernet.h"
#include "HttpClient.h"
#include "DataCoder.h"
#include "VirtualWire.h"
#include "Xively.h"
#include "DHT.h"

#define DHTPIN 3    
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
int rx_pin = 11;
int baudRate = 800;
// MAC address for your Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Your Xively key to let you upload data
char xivelyKey[] = "INSERIRE IL PROPRIO VALORE";
// Define the strings for our datastream IDs
char tIN[] = "TemperaturaDentro";
char hIN[] = "UmiditaDentro";
char tOUT[] = "TemperaturaFuori";
char hOUT[] = "UmiditaFouri";
XivelyDatastream datastreams[] = {
  XivelyDatastream(tIN, strlen(tIN), DATASTREAM_FLOAT),
  XivelyDatastream(hIN, strlen(hIN), DATASTREAM_FLOAT),
  XivelyDatastream(tOUT, strlen(tOUT), DATASTREAM_FLOAT),
  XivelyDatastream(hOUT, strlen(hOUT), DATASTREAM_FLOAT),
  
 };
// INSERIRE IL PROPRIO VALORE
XivelyFeed feed(12345678, datastreams, 4 /* number of datastreams */);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting single datastream upload to Xively...");
  Serial.println();
  dht.begin();
  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  SetupRFDataRxnLink(rx_pin, baudRate);
}

void loop() {
  float hIN = dht.readHumidity();
  float tIN = dht.readTemperature();
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  union RFData inDataSeq;//To store incoming data
  float inArray[2];//To store decoded information
  if(RFLinkDataAvailable(buf, &buflen))
  {
        for(int i =0; i< buflen; i++)
        {
          inDataSeq.s[i] = buf[i];
        }
        DecodeRFData(inArray, inDataSeq);
        float tOUT = inArray[0];
        float hOUT = inArray[1];
        // Setting data to send to Xively
        datastreams[0].setFloat(tIN);
        datastreams[1].setFloat(hIN);
        datastreams[2].setFloat(tOUT);
        datastreams[3].setFloat(hOUT);
        Serial.println("Uploading it to Xively");
        int ret = xivelyclient.put(feed, xivelyKey);
        Serial.print("xivelyclient.put returned ");
        Serial.println(ret);
  }
}
