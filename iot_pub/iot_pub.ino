#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

bool d1 = true;
bool d2 = true;
bool d3 = true;
bool d4 = true;
bool c = true;

#define clapP D0
////////////////////////////////////// Login details ///////////////////////////////////////////////////////////////
#define WLAN_SSID       "Niltech1"    
#define WLAN_PASS       "niltech12345"
#define MQTT_SERV      "io.adafruit.com"
#define MQTT_PORT  1883           
#define MQTT_NAME  "testID"
#define MQTT_PASS  "aio_XTns07LuHZNgKJMQSXuwuDgNaBp9"
////////////////////////////////// Feeds  ///////////////////////////////////////////////////////////////////////////
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Publish g1 = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/c1");
Adafruit_MQTT_Publish g2 = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/c2");
Adafruit_MQTT_Publish g3 = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/c3");
Adafruit_MQTT_Publish g4 = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/c4");
Adafruit_MQTT_Publish s = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/c5");


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
Serial.begin(9600);
if(!apds.begin()){
 Serial.println("failed to initialize device! Please check your wiring.");
}
else Serial.println("Device initialized!");
apds.enableProximity(true);
apds.enableGesture(true);

Serial.print("Connecting to ");
Serial.println(WLAN_SSID);
WiFi.begin(WLAN_SSID, WLAN_PASS);
while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 pinMode(clapP,INPUT);

Serial.println();
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.print(WiFi.localIP());

MQTT_connect();
 }

void loop() {
   uint8_t gesture = apds.readGesture();
  int clap = digitalRead(clapP);
  Serial.print("data : ");
  Serial.println(clap); 
  if(clap == 1){
    c= !c;
  if (! s.publish(c))
  {
    Serial.println(F("Failed"));
  }
  else
  {
      Serial.print("value : ");
      Serial.println(c);
    Serial.println(F("data sent"));
    delay(5000);
  }
  }
  
 if(gesture == APDS9960_DOWN){
 Serial.println("Down");
  if (! g1.publish(d1))
  {
    Serial.println(F("Failed"));
  }
  else
  {
      Serial.print("d1 : ");
      Serial.println(d1);
    Serial.println(F("data sent"));
    delay(5000);
  } 
 d1 = !d1;
 }
 if(gesture == APDS9960_UP){
 Serial.println("Up");
  if (! g2.publish(d2))
  {
    Serial.println(F("Failed"));
  }
  else
  {
      Serial.print("d2 : ");
      Serial.println(d2);
    Serial.println(F("data sent"));
    delay(5000);
  } 
 d2 = !d2;
 }
 if(gesture == APDS9960_LEFT){
 Serial.println("Left");
  if (! g3.publish(d3))
  {
    Serial.println(F("Failed"));
  }
  else
  {
      Serial.print("d3 : ");
      Serial.println(d3);
    Serial.println(F("data sent"));
    delay(5000);
  } 
 d3 = !d3;
 }
 if(gesture == APDS9960_RIGHT){
 Serial.println("Right");
  if (! g4.publish(d4))
  {
    Serial.println(F("Failed"));
  }
  else
  {
      Serial.print("d4 : ");
      Serial.println(d4);
    Serial.println(F("data sent"));
    delay(5000);
  } 
 d4 = !d4;
 }

}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected())
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0)
    {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0)
       {
         while (1);
       }
    }
  Serial.println("MQTT Connected!");
}
