#define trig 8
#define echo 9

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
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
  distance = duration*170/1000;

  
  int sensorValue = analogRead(A0);  
  if(sensorValue > 200){
    if(distance < 100){
      digitalWrite(13,HIGH);
      delay(2000);
      } else{
        digitalWrite(13,LOW);
    }
  }else{
    digitalWrite(13,LOW);
  }
  Serial.println(sensorValue);
}
