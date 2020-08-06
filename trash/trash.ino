#define BUZ 10
#define delay(x) delay(x*1000)
#define BUZ_OFF 0

void setup(){
  pinMode(BUZ,OUTPUT);
  analogWrite(BUZ,127);
  delay(5);
  analogWrite(BUZ,BUZ_OFF);
}

void loop(){
}
