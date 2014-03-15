/* FILE:    MX05V_433MHZ_MODULE_HCMODU0007_RECEIVE_EXAMPLE.pde
   DATE:    03/03/13
   VERSION: 0.1
   AUTHOR:  Andrew Davies

This is an example of how to use the 433MHz wireless reciever module 
(HCMODU0007) which is the Rx part of the tranmitter and reciver module pair.
This example makes use of the VirtualWire library written by Mike McCauley.
This sketch in intended to be used with the Tx example code to recive analogue
input data sent from the transmitting Arduino. The received data is then output 
to the UART.

Rx MODULE CONNECTIONS:

PIN  DESCRIPTION      ARDUINO PIN
1    GND              GND
2    RX DATA          D2
3    RX DATA          N/A
4    VCC (5V)         VCC


You may copy, alter and reuse this code in any way you like, but please leave 
reference to HobbyComponents.com in your comments if you redistribute this code. 

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS LTD MAKES NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES, 
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY 
REASON WHATSOEVER.
*/


/*Include the VirtualWire library */
#include <VirtualWire.h>

/* Digital IO pin that will be used for receiving data from the receiver */
const int RX_DIO_Pin = 2;

void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);

    /* Initialises the DIO pin used to receive data from the Rx module */
    vw_set_rx_pin(RX_DIO_Pin);
    
    /* Receive at 2000 bits per second */
    vw_setup(2000);
    
    /* Enable the receiver */
    vw_rx_start(); 
}

/* Main program */
void loop()
{
  /* Set the receive buffer size to 2 bytes */
  uint8_t Buffer_Size = 2;
  
  /* Holds the recived data */
  unsigned int Data;
  
  /* The receive buffer */
  uint8_t RxBuffer[Buffer_Size];

    /* Has a message been received? */
    if (vw_get_message(RxBuffer, &Buffer_Size)) // Non-blocking
    {
        /* If so, then turn on the LED connected to DIO 13 
           to indicate this */
        digitalWrite(13, HIGH); 
   
        /* Store the received high and low byte data */
        Data = RxBuffer[0] << 8 | RxBuffer[1];

        /* Output this data to the UART */
   Serial.print("Analogue pin A0: ");
        Serial.println(Data);
   
        /* Turn off the LED on pin 13 to indicate that the 
           data has now been received */
        digitalWrite(13, LOW);
    }
}
