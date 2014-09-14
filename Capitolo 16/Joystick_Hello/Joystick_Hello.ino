/**
Questo programa spiega come utilizzare il Joystick con Arduino

Versione 1.0
Autore Giacomo Bellazzi
*/

int A = 2;
int B = 3;
int C = 4;
int D = 5;
int x = A0;
int y = A1;
char key[] = {'A','B','C','D'};


void setup() {
 Serial.begin(9600);
}

void loop() {
  keyPressed(A);
  keyPressed(B);
  keyPressed(C);
  keyPressed(D);
  joystick();
  delay(100);
}

/* Questa funzione mostra se un pin è stato mostrato*/
void keyPressed(int index){
  if(digitalRead(index)==0){
    Serial.print(key[index-2]);
    Serial.print(" has been pressed");
    Serial.print("\n");
  }
}  
/* Questa funziona mostra lo spostamendo x e y del joystick*/  
void joystick(){
  Serial.print("x: ");
  Serial.print(analogRead(x));  
  Serial.print(" y: ");
  Serial.print(analogRead(y)); 
  Serial.print("\n");
}  
    
