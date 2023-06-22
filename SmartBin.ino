#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Define the pins for the ultrasonic sensors
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
float depth;
const float DustbinHeight = 280;
int buzzerPin = 10;
int   servoPos = 0;

float distance1, distance2, duration1, duration2;


LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo;

void setup() {

  Serial.begin(9600);


  lcd.init();
  lcd.backlight();


  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzerPin,OUTPUT);

  servo.attach(9);
}

void loop() {

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

 
  distance1 = pulseIn(echoPin1, HIGH)*0.017;


  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  servoPos = servo.read();

  distance2 = pulseIn(echoPin2, HIGH) *0.017;

  depth = ((DustbinHeight - distance1)/DustbinHeight )*100;
  if (distance2<20){
    servo.write(0);
  }
  else{
    servo.write(80);
  }
  delay (1000);
  if (depth<5){
    digitalWrite(buzzerPin, HIGH);
  }
  else{
    digitalWrite(buzzerPin, LOW);
  }
  // if (servoPos == 90){
  //   lcd.setCursor(0,0);
  //   lcd.print("please, Close the lid");
  // }


  Serial.print("Distance 2:");
  Serial.print(distance2);
  Serial.print(" cm");

  Serial.println();

  lcd.setCursor(0, 0);
  lcd.print("Space Left: ");
  lcd.setCursor(1, 4);  
  lcd.print(depth); 
  lcd.print("%");


  delay(500);
}
