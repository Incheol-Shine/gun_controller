#include<Servo.h>
Servo servo;

const int buttonPin = 8;
int down = 190;
int up = 150;

String s;
int data;
int buttonState = HIGH;

void setup() {
  // put your setup code here, to run once:
  servo.attach(7); // 서보모터 핀 번호
  pinMode(buttonPin, INPUT); // 리미트 스위치 핀 번호 - 자주씀
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  servo.write(down);
  while (buttonState == HIGH){
    buttonState = digitalRead(buttonPin);
  }
  delay(500);
  servo.write(up);
  delay(4000);
}
