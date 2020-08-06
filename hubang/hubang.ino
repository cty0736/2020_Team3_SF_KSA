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
  distance = duration*170.15/1000;
  Serial.print("length : ");
  Serial.println(distance);
  
    
  if(10 < distance && distance< 200){
      if(distance >35){
        tone(10, 3000,200);
        delay( (int)distance*5);
      }
      else {
        tone(10,3000,200);
      }      
    }

}
