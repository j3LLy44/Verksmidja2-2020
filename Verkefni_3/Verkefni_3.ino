#include <LiquidCrystal.h>
#include <IRremote.h>

//Distance Sensor
const int trigPin = 13;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int echoPin = 12;  // Arduino pin tied to echo pin on the ultrasonic sensor.
int maxDistance = 200;

//LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//BUZZER
const int buzzer = 10; //Buzzer pin

//REMOTE
const int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  //REMOTE
  irrecv.enableIRIn();
  irrecv.blink13(true);
  
  // Distance Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  //LCD
  pinMode(9, OUTPUT);
  lcd.begin(16,2); //Tell Arduino to start 16 column 2 row LCD

  //BUZZER
  pinMode(10, OUTPUT);
}

//Stepper
int stepper = 0;

void loop() {
  //REMOTE
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    //Minus
    if(results.value == 0xFFE01F && maxDistance != 100)
    {
      maxDistance -= 100;
    }
    if(results.value == 0xFFA857 && maxDistance != 400)
    {
      maxDistance += 100;
    }
    irrecv.resume();
  }
  Serial.println(maxDistance);
  
  
  // Distance Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  int distance = (duration*0.0343)/2;
  
  //Serial.print("Distance:");
  //>>Serial.println(distance);

  //LCD
  analogWrite(9, 75);
  lcd.setCursor(0,0);  //Set lcd cursor to upper left corner, column 0, row 0
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.setCursor(14 , 0);
  lcd.print("cm");
  delay(10);
  lcd.setCursor(0 , 1);
  lcd.print("Max distance:");
  lcd.print(maxDistance);
  delay(10);
  if(stepper == 4)
  {
    lcd.clear();
    stepper = 0;
  }
  else
  {
    stepper++;
  }
  
  
   //BUZZER
   if (distance < maxDistance){
    digitalWrite(buzzer, HIGH);
    }
   if (distance >= maxDistance){
    digitalWrite(buzzer, LOW);
    }
}
