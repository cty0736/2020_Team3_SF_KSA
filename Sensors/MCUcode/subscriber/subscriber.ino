#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Ruckus_8";
const char* password = "ilovelyzeum8";
const char* nodeName = "Factory-A-0 Device";
char* topic = "led";
char* server = "192.168.0.44"; //MQTT broker address
char message_buff[100];
void callback(char* topic, byte* payload, unsigned int length) {
int i = 0, ledState;
//create character buffer with ending null terminator (string)
for(i=0; i<length; i++){
message_buff[i] = payload[i];
}
message_buff[i]= '\0';
String msgString = String(message_buff);
Serial.println("Payload: "+ msgString);
//전송된 메시가 "on"이면 LED를 On, "on" 아니면 LED off
ledState = (msgString == "on") ? HIGH : LOW;
digitalWrite(16, ledState);
}

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);
void setup() {
Serial.begin(9600);
pinMode(16, OUTPUT);
WiFi.begin(ssid, password);
while ( WiFi.status() != WL_CONNECTED ) {
Serial.print("."); delay(500);
}
while ( !client.connect(nodeName) ){
Serial.print("."); delay(1000);
}
client.subscribe(topic);
}
void loop() {
client.loop();
}
