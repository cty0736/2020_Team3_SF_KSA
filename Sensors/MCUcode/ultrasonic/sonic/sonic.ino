#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>
#define TRIGLEFT D1
#define ECHOLEFT D2
#define TRIGRIGHT D3
#define ECHORIGHT D4

const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";
const char* nodeName = "Factory-A-0";
char* topic = "sonic";
char* server = "192.168.0.53"; //MQTT broker IP address
WiFiClient wifiClient; //클라이언트로 작동
PubSubClient client(server, 1883, wifiClient);
 


void setup() {
Serial.begin(9600);
pinMode(TRIGLEFT, OUTPUT);
pinMode(ECHOLEFT, INPUT);
pinMode(TRIGRIGHT, OUTPUT);
pinMode(ECHORIGHT, INPUT);

WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println("\nWiFi Connected");

while ( !client.connect(nodeName) ){
Serial.print("*");
delay(1000);
}
Serial.println("\nConnected to broker");
}


void loop() {
  delay(1000);
  long duration_1, distance_1, duration_2, distance_2;
  
  digitalWrite(TRIGLEFT, LOW);  
  delayMicroseconds(3); 
  digitalWrite(TRIGLEFT, HIGH);
  delayMicroseconds(12); 
  digitalWrite(TRIGLEFT, LOW);
  
  duration_1 = pulseIn(ECHOLEFT, HIGH);  
  distance_1 = (duration_1/2)/29.1;
  delay(500);
  digitalWrite(TRIGRIGHT, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIGRIGHT, HIGH);
  delayMicroseconds(12);
  digitalWrite(TRIGRIGHT, LOW);

  duration_2 = pulseIn(ECHORIGHT, HIGH);
  distance_2 = (duration_2/2)/29.1;
    
  Serial.print(distance_1);
  Serial.println("Cm left");
  Serial.print(distance_2);
  Serial.println("Cm right");
  
  char data[2];
  data[0]=distance_1;
  data[1]=distance_2;

  client.publish(topic,data);
  }
