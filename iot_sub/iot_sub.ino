#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define r1 D5
#define r2 D6
#define r3 D3
#define r4 D4



////////////////////////////////////// Login details ///////////////////////////////////////////////////////////////
#define WLAN_SSID       "Niltech1"    
#define WLAN_PASS       "niltech12345"
#define MQTT_SERV      "io.adafruit.com"
#define MQTT_PORT  1883           
#define MQTT_NAME  "testID"
#define MQTT_PASS  "aio_XTns07LuHZNgKJMQSXuwuDgNaBp9"
bool dev = LOW;
////////////////////////////////// Feeds  ///////////////////////////////////////////////////////////////////////////
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Subscribe a = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/c1");
Adafruit_MQTT_Subscribe b = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/c2");
Adafruit_MQTT_Subscribe c = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/c3");
Adafruit_MQTT_Subscribe d = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/c4");
Adafruit_MQTT_Subscribe all = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/c5");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
Serial.begin(9600);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);
pinMode(r3,OUTPUT);
pinMode(r4,OUTPUT);
digitalWrite(r1,HIGH);
digitalWrite(r2,HIGH);
digitalWrite(r3,HIGH);
digitalWrite(r4,HIGH);

Serial.print("Connecting to ");
Serial.println(WLAN_SSID);
WiFi.begin(WLAN_SSID, WLAN_PASS);
while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
Serial.println();
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.print(WiFi.localIP());

mqtt.subscribe(&a);
mqtt.subscribe(&b);
mqtt.subscribe(&c);
mqtt.subscribe(&d);
mqtt.subscribe(&all);

MQTT_connect();
 }

void loop() { 

  
  
  
  
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &a)
    {
    
      if (!strcmp((char*) a.lastread, "1"))
      {
        digitalWrite(r1,LOW);
        Serial.println("on");
     }
      if (!strcmp((char*) a.lastread, "0"))
      {  
                digitalWrite(r1,HIGH);
                        Serial.println("off");


      }
    }
      if (subscription == &b)
    {
    
      if (!strcmp((char*) b.lastread, "1"))
      {
        digitalWrite(r2,LOW);
        Serial.println("on");
     }
      if (!strcmp((char*) b.lastread, "0"))
      {  
                digitalWrite(r2,HIGH);
                        Serial.println("off");

    
    }
}
if (subscription == &c)
    {
    
      if (!strcmp((char*) c.lastread, "1"))
      {
        digitalWrite(r3,LOW);
        Serial.println("on");
     }
      if (!strcmp((char*) c.lastread, "0"))
      {  
                digitalWrite(r3,HIGH);
                        Serial.println("off");




  }
 }
 if (subscription == &d)
    {
    
      if (!strcmp((char*) d.lastread, "1"))
      {
        digitalWrite(r4,LOW);
        Serial.println("on");
     }
      if (!strcmp((char*) d.lastread, "0"))
      {  
                digitalWrite(r4,HIGH);
                        Serial.println("off");



      }
    }
     if (subscription == &all)
    {
    
      if (!strcmp((char*) all.lastread, "1"))
      {
        digitalWrite(r1,dev);
        digitalWrite(r2,dev);
        digitalWrite(r3,dev);
        digitalWrite(r4,dev);
        dev = !dev;
        Serial.println("on");
     }
    }
  }
}                    

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
