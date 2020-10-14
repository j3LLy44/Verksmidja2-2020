#include <LiquidCrystal.h>

//Distance Sensor
const int trigPin = 13;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int echoPin = 12;  // Arduino pin tied to echo pin on the ultrasonic sensor.
int maxDistance = 100;

//LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//BUZZER
const int buzzer = 10; //Buzzer pin

void setup() {
  // Distance Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  //LCD
  pinMode(9, OUTPUT);
  lcd.begin(16, 2);

  //BUZZER
  pinMode(10, OUTPUT);
}
int stepper = 0;
void loop() {
  // Distance Sensor
  stepper = stepper + 1;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  int distance = (duration*0.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  //LCD
  analogWrite(9, 75);
  lcd.print("Distance is:");
  lcd.setCursor(0 , 1);
  lcd.print(distance);
  Serial.println(distance);
  lcd.setCursor(1 , 2);
  lcd.print("cm");
  lcd.clear();
  
   //BUZZER
   if (distance > maxDistance){
    digitalWrite(10, HIGH);
    }
   if (distance <= maxDistance){
    digitalWrite(10, LOW);
    }
}
