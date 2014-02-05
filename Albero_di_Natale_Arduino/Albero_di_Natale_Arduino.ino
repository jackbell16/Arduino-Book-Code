/**
Questo porgramma permette di creare un piccolo albero di Natale, 
con le luci che si accendo attraverso un telecomando ad infrarossi.
Inoltre grazie ad un buzzer, è possibile far suonare le principali canzoni natalizie.
AUTHOR GIACOMO BELLAZZI
VERSION 1.0
*/
#include <IRremote.h>
#define time1 300
#define T0 16738455
#define T1 16724175
#define T2 16718055
#define T3 16743045
#define T4 16716015
#define T5 16726215
#define T6 16734885



int speakerPin = 9;
int RECV_PIN = 7;
int buttonPin = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long last = millis();
long randNumber;
int ledPattern = true;
int sequenza = -1;
int s = -1;
int led[6] = {13,12,11,10,9,8};
const int beatLength = 50; 
int switchState = LOW;
boolean buttonClear = true;
int songChoice;



void setup(){
  for(int j = 0; j==5; j++){
    pinMode(led[j], OUTPUT);
  }
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(speakerPin,OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  randomSeed(analogRead(0));
}
void loop(){
 // ledOn(13,12);
 // ledOn(13,11);
 // ledOn(12,11);
 updateStatus();
 Sequenza(sequenza);
 Serial.println(sequenza);
  
 playTune(songChoice);
 songChoice=0;
 irrecv.resume();
 
 
}
  
void ledOn(int led1, int led2){
  digitalWrite(led1,HIGH);
  delay(time1);
  digitalWrite(led2,HIGH);
  delay(time1);
  digitalWrite(led1,LOW);
  delay(time1);
  digitalWrite(led2,LOW);
  delay(time1);
  updateStatus();
}

void ledOnRandom(int led[]){
  randNumber = random(0,5);
  for(int i = 0; i<randNumber;i++){
    digitalWrite(led[i],HIGH);
  }
  delay(time1);
  for(int i = 0; i<randNumber;i++){
    digitalWrite(led[i],LOW);
  }
}

int IRcode(int codeRead){
 switch(codeRead) {
    case T0:
    s=0;
    break;
    case T1:
    s=1; 
    break;
     case T2:
    s=2; 
    break;
    case T3:
    s=3;
    break;
    case T4:
    s=4;
    break;
  }
  return s;
 }
void Sequenza(int sequenza){
  switch(sequenza){
    case 0:
    Serial.println("Playing Jingle Bells");
    songChoice = 1;
    break;
    case 1:
    Serial.println("Playing The Holly and the Ivy ");
    songChoice = 2;
    break;
    case 2:
    Serial.println("Playing We Wish You a Merry Christmas ");
    songChoice = 3;
    break;
    case 3:
    Serial.println("Playing Deck the Halls");
    songChoice = 4;
    break;
    case 4:
    ledOn(13,12);
    break;
    case -1:
    Serial.println("Non riprodurre");
    delay(1000);
    break;
  }
} 

void updateStatus(){
  if (irrecv.decode(&results)) {
   if (millis() - last > 250) {
    sequenza=IRcode(results.value);
    }
    last = millis();      
    irrecv.resume();
    }
}  




void alternateLeds() {
  if (ledPattern == true) {
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], HIGH);
    ledPattern = false;
  } else {
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], LOW);
    ledPattern = true;
  }
}

// Generate a tone by passing a square wave of a certain period to the piezo
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

/* This works out what period, in microseconds, to use for the square wave for a given note. To calculate these,
p = ((1 / freq) * 1,000,000) / 2. We divide by 2 because the signal will be HIGH for p microseconds and then LOW
for p microseconds. Frequencies for the notes obtained from http://www.phy.mtu.edu/~suits/notefreqs.html
The range defined below covers 2 octaves from C4 (middle C, or 261.63Hz) to B5 (987.77Hz). Feel free to modify. */
void playNote(char note, int duration, boolean sharp) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 851, 758, 716, 636, 568, 506 };
  
  // these are the "sharp" versions of each note e.g. the first value is for "c#"
  char names_sharp[] = { 'c', 'd', 'f', 'g', 'a', 'C', 'D', 'F', 'G', 'A' };
  int tones_sharp[] = { 1804, 1607, 1351, 1204, 1073, 902, 804, 676, 602, 536 };
  
  // play the tone corresponding to the note name
  if (sharp == false) {
    for (int i = 0; i < 14; i++) {
      if (names[i] == note) {
        playTone(tones[i], duration);
      }
    }
  } else {
    for (int i = 0; i < 10; i++) {
      if (names_sharp[i] == note) {
        playTone(tones_sharp[i], duration);
      }
    }
  }
}

/* Code for using a microswitch as a start/stop toggle
Note: to stop a song half way through, you may have to hold the button down for a moment */
void updateSwitchState() {
  int val = digitalRead(buttonPin);
  if (val == HIGH) {
    buttonClear = true;
  } else {
    if (buttonClear == true) {
      if (switchState == LOW) {
        switchState = HIGH;
      } else {
        switchState = LOW;
      }
      buttonClear = false;
    }
  }
}

void parseTune(char notes[], int beatLength, boolean loopSong) {
  boolean play = true;
  
  // 1 iteration of this loop == 1 note played
  for (int i = 0; notes[i] != '.' && play == true; i++) { // stop iteration if '.' is the next char
    updateSwitchState();
    updateStatus();
    if (irrecv.decode(&results) ) { // For every note, check to see if the button has been pressed to stop the tune
      play = false;
    } else {
      if (notes[i] == ',') { // ',' signifies a rest
      
        // Look at the number (max. 2 digits) following from the ',' to work out the duration of the rest
        char len[3];
        int count = 0;
        while (notes[i+1] >= '0' && notes[i+1] <= '9' && count < 2) {
          len[count] = notes[i+1];
          count++;
          i++;
        }
        len[count] = '\0';
        int duration = atoi(len);
        
        delay(duration * beatLength); // rest duration
      } else { // play the next note, represented by a series of characters e.g. 'c4', 'a#12'
        alternateLeds(); // alternate the red and green LEDs every note to make them "dance"
        char note = notes[i];
        boolean sharp;
        
        // if the next character is a '#' then we must make the note a sharp
        if (notes[i+1] == '#') {
          i++;
          sharp = true;
        } else {
          sharp = false;
        }
        
        // Look at the number (max. 2 digits) following from the note name to work out the note duration
        char len[3];
        int count = 0;
        while (notes[i+1] >= '0' && notes[i+1] <= '9' && count < 2) {
          len[count] = notes[i+1];
          count++;
          i++;
        }
        len[count] = '\0';
        int duration = atoi(len);
        
        playNote(note, duration * beatLength, sharp);
      }
      
      delay(beatLength / 2); // pause between notes
    }
  }
  if (loopSong == false) {
    sequenza=-1;
  }
   
  
}

// Write your tunes in here using the grammar described at the top of this file. Can have up to 4 tunes.
void playTune (int tune) {
  if (tune == 1) { // Jingle Bells
    char notes[] = "b4b4b8b4b4b8b4D4g6a2b12,4C4C4C6C2C4b4b4b2b2b4a4a4b4a8D8b4b4b8b4b4b8b4D4g6a2b12,4,C4C4C6C2C4b4b4b2b2D4D4C4a4g12,8.";
    parseTune(notes, beatLength, false);
  } else if (tune == 2) { // The Holly and the Ivy
    char notes[] = "g4g2g2g4E4D4b6g2g2g2g4E4D8D2C2b2a2g4b2b2e2e2d4g2a2b2C2b4a4g8,8.";
    parseTune(notes, beatLength * 1.50, false);
  } else if (tune == 3) { // We Wish You a Merry Christmas
    char notes[] = "d4g4g2a2g2f#2e4c4e4a4a2b2a2g2f#4d4f#4b4b2C2b2a2g4e4d2d2e4a4f#4g8,8.";
    parseTune(notes, beatLength * 1.25, false);
  } else if (tune == 4) { // Deck the Halls
    char notes[] = "D6C2b4a4g4a4b4g4a2b2C2a2b6a2g4f#4g6,2D6C2b4a4g4a4b4g4a2b2C2a2b6a2g4f#4g6,2a6b2C4a4b6C2D4a4b2C#2D4E2F#2G4F#4E4D6,2D6C2b4a4g4a4b4g4E2E2E2E2D6C2b4a4g8,8.";
    parseTune(notes, beatLength, false);
  }
}


