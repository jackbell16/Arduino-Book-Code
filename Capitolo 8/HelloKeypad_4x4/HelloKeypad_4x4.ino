/*Questo programma mostra come usare la tastiera KeyPad 4x4 con Arduino Uno.
Il testo che viene premuto sulla KeyPad viene mostrato nel seriale
*/
#include <Keypad.h>

const byte ROWS = 4; //quattro righe
const byte COLS = 4; //quattro colonne
byte colPins[4] = {5,4,3,2}; // Pin a cui sono connesse le colonne
byte rowPins[4] = {9,8,7,6}; // Pin a cui sono connesse le righe
char Keys[4][4]= //creo la matrice dei tasti della tastiera.
{
{'1','2','3','A'} ,
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
Keypad keyp = Keypad(makeKeymap(Keys), rowPins, colPins,4,4);

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keyp.getKey();
  if (key){
    Serial.println(key);
  }
}
