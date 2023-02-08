

 #include "DHT.h"  
 DHT dht2(15,DHT11);


#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
//int sensor = A0; // new
#define Relay1            D6
#define Relay2            D5
#define Relay3            D2
#define Relay4            D1
#define slider            D7 // new
#define WLAN_SSID       "Rafsan"             // Your SSID
#define WLAN_PASS       "diu123456"        // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "RAFSAN"            // Replace it with your username
#define AIO_KEY         "aio_lyKx644pDl7wnblQpS0VdG9Y0auL"  // Replace with your Project Auth Key

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/


// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay1"); // FeedName
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay2");
Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay3");
Adafruit_MQTT_Subscribe Light4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay4");
Adafruit_MQTT_Subscribe regulat  = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Regulator"); //new
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperature");
Adafruit_MQTT_Publish neww = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Humidity");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(slider, OUTPUT);
  pinMode(A0,INPUT);// n
   //pinMode(sensor,INPUT);
  digitalWrite(D6,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D1,LOW);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light3);
  mqtt.subscribe(&Light2);
  mqtt.subscribe(&Light4);
  mqtt.subscribe(&regulat); //n
  //mqtt.Publish(&neww); //n
  
}

void loop() {
 
  MQTT_connect();
  
  //
  int pp = analogRead(A0);
  Serial.print(pp);
  analogWrite(slider,pp);
 //
 
 
 
 
 
 
 
 
 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Light1) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int Light1_State = atoi((char *)Light1.lastread);
      digitalWrite(Relay1, Light1_State);
      
    }
    if (subscription == &Light2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light2.lastread);
      int Light2_State = atoi((char *)Light2.lastread);
      digitalWrite(Relay2, Light2_State);
    }
    if (subscription == &Light3) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light3.lastread);
      int Light3_State = atoi((char *)Light3.lastread);
      digitalWrite(Relay3, Light3_State);
    }
    if (subscription == &Light4) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light4.lastread);
      int Light4_State = atoi((char *)Light4.lastread);
      digitalWrite(Relay4, Light4_State);
      
    }
    
    if (subscription == &regulat) {
      Serial.print(F("Got: "));
      Serial.println((char *)regulat.lastread);
      int regulat_State = atoi((char *)regulat.lastread);
      //analogWrite(slider, regulat_State); 
      
    }
  
  }
    // s
  
  //Serial.print(F("\nSending temp "));
  //Serial.print("x");
  //Serial.print("...");
  
  //int force_value = analogRead(sensor); // readddd
  
  float temperature  = dht2.readTemperature( );/* Get humidity value */ //n
  
  
  
  
  if (! photocell.publish(temperature)) {
    //Serial.println(F("Failed"));
  } else {
    //Serial.println(F("OK!"));
  }
   //delay(100); 
   
   
  float humidity  =     dht2.readHumidity();/* Get temperature value */ //n
  if (! neww.publish(humidity)) {
    //Serial.println(F("Failed"));
  } else {
    //Serial.println(F("OK!"));
  }
  //delay(100); 
  
  
 // e

  
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
