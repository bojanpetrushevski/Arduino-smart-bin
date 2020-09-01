#include <Servo.h>   //servo library
#include <SoftwareSerial.h>
Servo servo;
int trigPin1 = 5;
int echoPin1 = 6;
int trigPin2 = 2;
int echoPin2 = 3;
int servoPin = 7;
int ledPin = 13;
bool isBinOpened = false;
long duration1, duration2, dist1, dist2;


void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledPin, OUTPUT);
  servo.write(0);         //close cap on power on
  delay(100);
  servo.detach();
}


long measure(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034) / 2; //obtain distance
}

void blinkLED()
{
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  delay(300);
}

void stopLED() {
  digitalWrite(13, LOW);
}

void loop() {
  dist1 = measure(trigPin1, echoPin1);
  checkServo();
  dist2 = measure(trigPin2, echoPin2);
  checkLED();
}

void checkServo() {
//  Serial.println(dist1);
  if (isBinOpened) {
    if (dist1 >= 10) {
      isBinOpened = false;
      servo.write(150);
      delay(1000);
      servo.detach();
    }
  }
  else {
    if (dist1 < 10) {
      isBinOpened = true;
      servo.attach(servoPin);
      delay(1);
      servo.write(0);
      delay(3000);
    }
  }
}

void checkLED() {
  Serial.println(dist2);
  if (dist2 < 5) {
    blinkLED();
  }
  else {
    stopLED();
  }
}
