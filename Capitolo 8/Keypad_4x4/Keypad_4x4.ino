/**
Questo programma permette di far inserire da un utente un codice con il KeyPad. Qualora il codice inserito sia corretto, viene accesso un LED.
Per inviare il codice, una volta digitato interamente è necessario premere *. Mentre per spegnere il LED, oppure re-digitare il codice è necessario premere #
Autore Giacomo Bellazzi
Versione 1.0
*/
#include <Keypad.h>
#define LED 13
const byte ROWS = 4; //quattro righe
const byte COLS = 4; //quattro colonne
char keyInsert[6];
// Queste variabili servono come verifica del corretto inserimento del codice
int i = 0;
int j = 0;
int s = 0;
int x = 0;
// Codice segreto
char code[7]= "11ABCD";
char Keys[ROWS][COLS]= //creo la matrice dei tasti della tastiera.
{
{'1','2','3','A'} ,
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte colPins[4] = {5,4,3,2}; // Pin a cui sono connesse le colonne
byte rowPins[4] = {9,8,7,6}; // Pin a cui sono connesse le righe

Keypad keypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS);

void setup(){
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop(){
  char key = keypad.getKey();
  if (i==0){
    Serial.println("Insert PIN to verify...");
    i++;
  }
  if (key != NO_KEY && j<6){
    Serial.print("*");
    //Serial.println(key);
    keyInsert[j]=key;
    j++;
  }
   if(key == '*') {
      Serial.println();
      Serial.println("Verifyng the code...");
      delay(1000);
      for(s=0; s<6;s++){
        if(keyInsert[s]==code[s]){
          x++;
      }
    } 
      if(x==6){
        Serial.println("The code is correct"); 
        digitalWrite(LED,HIGH); 
      //TODO possibili ulteriori implementazioni
      }else{
        Serial.println("The code is incorrect, please retry");
        delay(2000);
        x=0;
        i=0;
        j=0;
       }
      }  
    if(key == '#'){
        x=0;
        i=0;
        j=0;
        digitalWrite(LED,LOW); 
    }    
}
