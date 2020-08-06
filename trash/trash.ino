#define trig 8
#define echo 9
#define spin 10
#include <Servo.h>
Servo sServo;

void setup(){
  Serial.begin(9600);
  sServo.attach(spin);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop(){
  long duration, distance;

  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration = pulseIn(echo,HIGH);
  distance = duration*170.15/1000;
  Serial.print("length : ");
  Serial.println(distance);
  if(distance < 100){
      sServo.write(90);
      delay(2000);
    } else{
        sServo.write(0);
    }
}
