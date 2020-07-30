#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";
const char* nodeName = "Factory-A-0";
char* topic = "temp";
char* server = "192.168.0.53"; //MQTT broker IP address
WiFiClient wifiClient; //클라이언트로 작동
PubSubClient client(server, 1883, wifiClient);


void setup() {
Serial.begin(9600);
dht.begin();

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
  delay(2000);
  float h = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  if(isnan(h) || isnan(temperature)){
    Serial.println("Failled to read from DHt sensor!");
    h = 101.0;
    
  }
  char data[2];
  data[1]=h;
  data[0]=temperature;
//  data.toCharArray(data1,data.length());
  Serial.print("Temp : ");
  Serial.println(temperature);
  Serial.println(h);

//  String Str1 = String(temperature);
//  Str1.toCharArray(data1,Str1.length());
//  String Str2 = String(h);
//  Str2.toCharArray(data2,Str2.length());

  client.publish(topic,data);
  }
