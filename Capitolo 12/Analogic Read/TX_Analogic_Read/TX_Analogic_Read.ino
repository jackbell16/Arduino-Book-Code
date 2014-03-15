/* FILE:    MXFS03V_433MHZ_MODULE_HCMODU0007_TRANSMIT_EXAMPLE.pde
   DATE:    03/03/13
   VERSION: 0.1
   AUTHOR:  Andrew Davies

This is an example of how to use the 433MHz wireless transmitter module 
(HCMODU0007) which is the Tx part of the tranmitter and receiver module pair.
This example makes use of the VirtualWire library written by Mike McCauley.
The sketch will read a value from the analogue input A0 and transmit it as 
2 bytes to the receiver module once every second.

Tx MODULE CONNECTIONS:

PIN  DESCRIPTION      ARDUINO PIN
1    GND              GND
2    VCC (3.5-12V)    VCC
3    TX DATA          D2


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

/* Digital IO pin that will be used for sending data to the transmitter */
const int TX_DIO_Pin = 2;


void setup()
{
  pinMode(13, OUTPUT);
  /* Initialises the DIO pin used to send data to the Tx module */
  vw_set_tx_pin(TX_DIO_Pin);
  /* Set the transmit logic level (LOW = transmit for this 
     version of module)*/ 
  vw_set_ptt_inverted(true); 
  
  /* Transmit at 2000 bits per second */
  vw_setup(2000);    // Bits per sec
}

/* Main program */
void loop()
{
  /* Temporarily holds the value read from analogue input A0 */
  unsigned int Data;
  /* The transmit buffer that will hold the data to be 
     transmitted. */
  byte TxBuffer[2];
  
  /* Read the analogue input A0... */
  Data = analogRead(A0);
  /* ...and store it as high and low bytes in the transmit 
     buffer */
  TxBuffer[0] = Data >> 8;
  TxBuffer[1] = Data;
  
  /* Turn on the LED on pin 13 to indicate that we are about 
    to transmit data */
  digitalWrite(13, HIGH); 
  /* Send the data (2 bytes) */
  vw_send((byte *)TxBuffer, 2);
  /* Wait until the data has been sent */
  vw_wait_tx(); 
  
  /* Turn off the LED on pin 13 to indicate that we have 
     now sent the data */
  digitalWrite(13, LOW); 
  
  /* Do nothing for a second. Lower this delay to send 
     data quicker */
  delay(1000);
}
