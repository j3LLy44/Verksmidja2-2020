// Include the AccelStepper Library
#include <AccelStepper.h>
// Define step constant
#define FULLSTEP 4
// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(FULLSTEP,  8,  10,  9,  11);

// Servomótor breytur
#include <Servo.h>
Servo myservo;   // create servo object to control a servo
int servoPinni = 13; // pinninn sem servo mótorinn er tengdur við
int pos = 50;   // variable to store the servo position
bool direction = true; // segir til um hvort hendin er að fara upp eða niður
unsigned long servoTimiNuna = 0; // notað til að losna við delay
int servoHle = 25; // hraði á servo mótor, lægri tala => meiri hraði

// Breytur fyrir jólalögin
#include "jolalog.h" // inniheldur breyturnar jolalog og tempo ásamt skilgreiningum á nótum
int melodyPin = 6; // hátalarinn
int naestaNota = 0; // númer næstu nótu sem á að spila
unsigned long timiNuna = 0; // notað til að losna við delay
bool nyNota = true; // stjórnar hvort ný nóta er sótt 
int lengdNotu; // hversu lengi á nótan að hljóma
int hleMilliNota; // hlé á milli nóta sem spilaðar eru
float hleMargfaldari = 2.5; // notað til að stjórna hléinu milli nóta, hærri tala => lengri þagnir

void setup()  {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper.setMaxSpeed(1000.0);
  myStepper.setAcceleration(50.0);
  myStepper.setSpeed(200);
  myStepper.moveTo(400);
  
  myservo.attach(servoPinni);
  
  pinMode(melodyPin, OUTPUT);
}

void loop()  {
  // Stepper mótorinn
  // Change direction once the motor reaches target position
  if  (myStepper.distanceToGo()  ==  0) {
    myStepper.moveTo(-myStepper.currentPosition());
  }
  // Move the motor one step
  myStepper.run();
  
  // Servo mótorinn
  if(millis() - servoTimiNuna >= servoHle) {
    servoTimiNuna = millis();
    if (direction) {
      pos++;
    } else {
      pos--;
    }
    if (pos  ==  50  ||  pos  ==  120) {
      direction  =  !direction;
    }
    myservo.write(pos);
  }
  
  // Jólalögin
  if(nyNota) {
    // to calculate the note duration, take one second
    // divided by the note type. e.g. quarter note = 1000 / 4 etc.
    lengdNotu = 1000 / tempo[naestaNota];
    tone(melodyPin, jolalog[naestaNota], lengdNotu);
    nyNota = false;
    // to distinguish the notes, set a minimum time between them.
    hleMilliNota = lengdNotu * hleMargfaldari; 
  }
  if(millis() - timiNuna >= hleMilliNota) {
    // stop the tone playing:
    noTone(melodyPin);
    nyNota = true;
    timiNuna = millis();
    if(naestaNota < (sizeof(jolalog) / sizeof(int) - 1))  {
      naestaNota++;
    } else {
      naestaNota = 0;
    }
  } 
}
