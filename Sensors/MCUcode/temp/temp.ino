#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";
const char* nodeName = "Factory-A-0";
char* topic = "temp";
char* server = "192.168.0.53";
WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);
char data[10];


void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status()!= WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Connected");
  
  while(!client.connect(nodeName)){
    Serial.print("*");
    delay(1000);
  }
  Serial.println("\nConnected to broker");
}
void loop(){
  float voltage = analogRead(A0) * 3.3/1024.0;
  float temperature = 100.0*voltage - 50.0;
  String Str = String(temperature);
  Str.toCharArray(data,Str.length());
  client.publish(topic,data);
  delay(2000);
  }
