/**
Questo programa permette di utilizzare la Joystick shield per comandare l'elicottero Syma S-107G

Versione 1.0
Autore Giacomo Bellazzi
*/
#define RED 12    // the output pin of the IR LED

int A = 2;
int B = 3;
int C = 4;
int D = 5;
int x = A0;
int y = A1;
int throttleValue = 63; //Initial value

void setup() {
    pinMode(RED, OUTPUT);    // set IR LED (Pin 4) to Output
    int Channel = 0;          //Channel A = 0, Channel B = 128
    pinMode(A,INPUT);
    pinMode(B,INPUT);
    pinMode(C,INPUT);
    pinMode(D,INPUT);
    Serial.begin(9600);
}

void loop() {
    int Throttle, Rudder, Elevator, RudderTrim;
    int Channel;
    Throttle = throttleValue;
    Rudder = leftRightToPerc(analogRead(x));   
    Elevator = upDownToPerc(analogRead(y));  
    RudderTrim = 0;
    Serial.println(Throttle);
    //Serial.println(Rudder);
    //Serial.println(Elevator); 
    //Transmit(0,63,50,0);
    Transmit(Rudder, Elevator, Throttle, RudderTrim);
    throttle();
}

void Transmit(byte rudder, byte elevator, byte throttle, byte trim) {
    static byte Code[4];
    byte mask = 128;     //bitmask
    int i;
 
    Code[0] = rudder; // 0 -> 127; 63 is the midpoint.
    Code[1] = elevator; // 0 -> 127; 63 is the midpoint.
    Code[2] = throttle; // 0 -> 127; 0 is throttle off
    Code[3] = trim;    // Haven't messed with this
     
    OutPulse(2002);  // Start 38Khz pulse for 2000us (2002us is evenly divided by 26)
    delayMicroseconds(2000);  // 2000us off.
 
    for (i = 0; i<4; i++) {        // Loops through the Code[]
        for (mask = 128; mask > 0; mask >>=1) {    // See Arduino reference for bit masking (really cool stuff!)
        OutPulse(312);         // Sends 312 pulse each loop
 
            if(Code[i] & mask) {          //If both bit positions are 1 you get 1             
                delayMicroseconds(688);     // send 1 (700 off)
            }
            else {
                delayMicroseconds(288);     // send 0 (300 off)
            }
        } //End mask loop
    }  //End i loop
 
    OutPulse(312);  //Send 300 microsecond Closing Pulse
    delay(60);      
 
} // End Transmit
 
 
void OutPulse(int Pulse) {  //sends 38Khz pulses over the Pulse Length
    
    int par=Pulse/26;
    par+=-1;
    for(int p = 0; p < par; p++) {  //Takes about 26 microseconds per loop
        digitalWrite(RED, HIGH);
          delayMicroseconds(10);
        digitalWrite(RED, LOW);
          delayMicroseconds(10);
    }
}  //End Out



int leftRightToPerc(int value){
  return (int) (127-value*0.12414467);
  }
int upDownToPerc(int value){
  return (int) (127-value*0.12414467);
}  

// Viene aumentato il valore della potenza/quota 
void throttle(){
  if(hasBeenPressed(C)&&throttleValue!=0){
    throttleValue--;
  }
  if(hasBeenPressed(A)&&throttleValue!=127){
    throttleValue++;
  }
}



// Stabilisce se un push button è stato premuto
boolean hasBeenPressed(int key){
  if(digitalRead(key)==0){
    return true;
  }else{
    return false;
  }
}   
