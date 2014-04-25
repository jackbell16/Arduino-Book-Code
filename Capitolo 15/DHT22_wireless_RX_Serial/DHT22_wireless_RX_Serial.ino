/**
Questo programma permette di ricevere i dati della temperatura e dell'umidità, che vengono inviati da Arduino posto fuori casa,
sfruttando i sensori Wireless 433 MHz
Versione 1.0
Autore Giacomo Bellazzi
*/
#include <DataCoder.h>
#include <VirtualWire.h>

const int rx_pin = 11;
const int led_pin = 13;
const int baudRate = 800;

void setup()
{
  delay(1000);
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  digitalWrite(led_pin,LOW);
  SetupRFDataRxnLink(rx_pin, baudRate);
}

void loop()
{
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
        Serial.println("Temperature: ");
        Serial.print(inArray[0]);
        Serial.print(" ° Humidity: ");
        Serial.print(inArray[1]);
  }
}

