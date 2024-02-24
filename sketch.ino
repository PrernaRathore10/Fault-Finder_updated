#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);


#define MSG_BUFFER_SIZE  (50)
#define LED1 17
#define  LED2 16
#define LDR1 32
#define LDR2 35
#define  MAINLDR 33
int LDR1_value = 0;
int LDR2_value = 0;
int MAINLDR_value = 0;
String LED1_status = "OFF";
String LED2_status = "OFF";
String MAINLDR_status = "OFF";

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      // Once connected, publish an announcement...
      client.publish("iotfrontier/mqtt", "iotfrontier");
      // ... and resubscribe
      client.subscribe("iotfrontier/mqtt");
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
  pinMode(LDR1, INPUT);     
  pinMode(LDR2, INPUT);     
  pinMode(MAINLDR, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

    LDR1_value = analogRead(LDR1);
    float lux1 = (4063 - LDR1_value)*100/4031;
    Serial.print("LDR 1 : ");
    Serial.println(LDR1_value);

    Serial.println(lux1);
    
    LDR2_value = analogRead(LDR2);
    float lux2 = (4063 - LDR2_value)*100/4031;
    Serial.print("LDR 2 : ");
    Serial.println(LDR2_value);

    Serial.println(lux2);

    
    MAINLDR_value = analogRead(MAINLDR);
    float lux3 = (4063 - MAINLDR_value)*100/4031;
    Serial.print("LDR 3 : ");
    Serial.println(MAINLDR_value);
    Serial.println(lux3);
    Serial.println();

    if (lux3 > 35 ){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      MAINLDR_status = "OFF";
    }
    else{
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      MAINLDR_status = "ON";
    }

    if (lux1 < 35 ){
      LED1_status = "OFF";
    }
    else{
      LED1_status = "ON";
    }
    if (lux2 < 35 ){
      LED2_status = "OFF";
    }
    else{
      LED2_status = "ON";
    }
    
    client.publish("iotfrontier/LDR1", String(LED1_status).c_str());
    client.publish("iotfrontier/LDR2", String(LED2_status).c_str());
    client.publish("iotfrontier/LDR3", String(MAINLDR_status).c_str());

    
  
  delay(2000);
}

