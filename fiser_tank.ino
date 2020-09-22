// DS3231 - Version: Latest 
#include <Wire.h>
#include <ds3231.h>
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
 
#define melodyPin A0
//Mario main theme melody
int mario[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
};
//Mario main them tempo
int mario_tempo[] = {
  24, 24, 24, 24,
  24, 24, 24, 24,
  24, 24, 24, 24,
  24, 24, 24, 24
};

//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3
};
/*
  Created By John Franklin Ruiz 31-08-2020
*/
struct ts t; 
int feedPin = 3;
int firstHourFeedFish = 8;
int firstMinuteFeedFish = 00;
int secondHourFeedFish = 19;
int secondMinuteFeedFish = 00;

int Lightpin = 6;
int hourTurnOnLight = 7;
int minuteTurnOnLight = 00;
int hourTurnOffLight = 14;
int minuteTurnOffLight = 00;

boolean alreadyLightOn = false;
boolean alreadyLightOff = false;
boolean alreadyFirstFood = false;
boolean alreadySecondFood = false;

int CANTIDAD_COMIDA = 3;
int PAUSA_ENTRE_COMIDAS = 30000; //30 seg
int song = 0; 
int TIEMPO_MOTOR = 300;

void setup() {
  pinMode(Lightpin, OUTPUT);
  pinMode(feedPin, OUTPUT);
  pinMode(melodyPin,OUTPUT);  
  
  digitalWrite(Lightpin, HIGH);
  digitalWrite(feedPin, HIGH);
  digitalWrite(melodyPin,HIGH);
  
  Serial.begin(9600);
  Wire.begin();
  
  DS3231_init(DS3231_INTCN);
  DS3231_get(&t);
  
  if(t.year < 2020){
    /*----------------------------------------------------------------------------
    Solo la primera vez ajusta la hora de resto asi se presione reset la hora se mantiene
    ----------------------------------------------------------------------------*/ 
    t.hour=12; 
    t.min=46;
    t.sec=0;
    t.mday=1;
    t.mon=9;
    t.year=2020;
    DS3231_set(t);     
  }
  
  evaluarLuz(t.hour);
}
 
void loop() {
  DS3231_get(&t);
  //printTime();
  if((t.hour == firstHourFeedFish)){
    if(t.min == firstMinuteFeedFish){
      if(!alreadyFirstFood){
        Serial.println("Ya es la 1 hora y minuto para dar comida");
        alimentarPeces();
        alreadyFirstFood = true;
      }
    }
  }
  else{
    alreadyFirstFood = false;
  }
  
  if((t.hour == secondHourFeedFish)){
    if(t.min == secondMinuteFeedFish){
      if(!alreadySecondFood){
        Serial.println("Ya es la 2 hora y minuto para dar comida");
        alimentarPeces();
        alreadySecondFood = true;
      }
    }
  }
  else{
     alreadySecondFood = false;
  }

  if(t.hour == hourTurnOnLight){
    if(t.min == minuteTurnOnLight){
      if(!alreadyLightOn){
        Serial.println("Ya es hora y minuto para prender la luz");
        encenderLuz();
        alreadyLightOn = true;
      }  
    }
  }
  else{
    alreadyLightOn = false;
  }
  
  if(t.hour == hourTurnOffLight){
    if(t.min == minuteTurnOffLight){
      if(!alreadyLightOff){
        Serial.println("Ya es hora y minuto para apagar la luz");
        apagarLuz();
        alreadyLightOff = true;
      }
    }
  }
  else{
    alreadyLightOff = false;
  }
  
}

void apagarLuz(){
  controlarLuz(HIGH);
}

void encenderLuz(){
  controlarLuz(LOW);
}

void printTime(){
  Serial.print("Date : ");
  Serial.print(t.mday);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print("\t Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.println(t.sec);
}

void alimentarPeces(){
    printTime();
    sing(1);
    Serial.println("Encendiendo lampara para alimentar a los peces");
    digitalWrite(Lightpin, LOW);
        
    for(int i = 1; i <= CANTIDAD_COMIDA; i++){
      digitalWrite(feedPin, LOW);
      delay(TIEMPO_MOTOR);
      digitalWrite(feedPin, HIGH);
      delay(TIEMPO_MOTOR);
      delay(PAUSA_ENTRE_COMIDAS);
    }
    evaluarLuz(t.hour);
    Serial.println("Apagando la luz pues ya se termino de dar comida a los peces");
}

void controlarLuz(int estado){
    printTime();
    sing(2);
    if (estado == LOW){
      Serial.println("Prendiendo la luz de la pecera");
    }
    else{
      Serial.println("Apagando la luz de la pecera");
    }
    digitalWrite(Lightpin, estado);
}

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 1) {
    Serial.println("Underworld Theme");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      buzz(melodyPin, underworld_melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
 
  } else if(song==2) {
 
    Serial.println("Sonido de Mario");
    int size = sizeof(mario) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / mario_tempo[thisNote];
 
      buzz(melodyPin, mario[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 2.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
  }
  else{
    digitalWrite(melodyPin, HIGH); 
    delay(1000); 
    digitalWrite(melodyPin, LOW); 
    delay(1000);
  }
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}

void evaluarLuz(int horaActual){
    if(horaActual < hourTurnOnLight){
    Serial.println("La luz deberia estar apagada");
    apagarLuz();
  }
  else if(horaActual >= hourTurnOnLight && horaActual < hourTurnOffLight){
    Serial.println("La luz deberia estar encendida");
    encenderLuz();
  }
  else if(horaActual >= hourTurnOffLight){
    Serial.println("La luz deberia estar apagada");
    apagarLuz();    
  }
  sing(3);
}