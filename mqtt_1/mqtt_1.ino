#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h> // Include Wire.h to control I2C
#include <LiquidCrystal_I2C.h> //Download & include the code library can be downloaded below
 
 
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); // Initialize LCD Display at address 0x27 


 // Update these with values suitable for your network.

const char* ssid = "Shankii";
const char* password = "shankaRR";
const char* mqtt_server = "192.168.1.9";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {
 

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  
  Serial.println("");
  lcd.setCursor(0,1);
  lcd.print("WiFi connected");
  lcd.setCursor(0,1);
  lcd.print("IP address: ");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  


 
  if ((char)payload[0] == '1') 
  {
    
    digitalWrite(D4,HIGH);
    Serial.print("unlocked");
     
 
  lcd.setCursor(0,1);
  lcd.print("UNLOCKED....");
  delay(1000);
  
    delay(5000);
     digitalWrite(D4,LOW);
      lcd.setCursor(0,1);
  lcd.print("IT IS LOCKED");
  delay(2000);
   lcd.setCursor(0,1);
   lcd.print("                                     ");
  
  delay(2000);
  
      
   
    
}
 
 
 
 }       



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    lcd.setCursor(0,1);
    lcd.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      lcd.setCursor(0,1);
      lcd.print("connected");
      lcd.setCursor(0,1);
      lcd.print("                ");
      // Once connected, publish an announcement...
      client.publish("lock", "hello world");
      // ... and resubscribe
      client.subscribe("lck");
      client.subscribe("clientid");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // Initialize the BUILTIN_LED pin as an output
 lcd.begin (16,2);
  pinMode(D4, OUTPUT); 
  pinMode(D6, OUTPUT); 
  pinMode(D7, INPUT); 
   
  Serial.begin(115200);
  setup_wifi();
lcd.setBacklight(HIGH); // Set backlight to of
 
    lcd.setCursor(0,0); // Move cursor to 0
  lcd.print("ID:72277689"); 
  
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  
}
