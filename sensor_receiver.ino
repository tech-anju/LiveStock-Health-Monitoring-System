#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <math.h>

#define SS 5
#define RST 14
#define DIO0 2

// WiFi
const char* ssid = "Hi";
const char* password = "Anju1234";

// ThingSpeak
unsigned long channelID = 3319531;
const char * writeAPI = "PCBAXAA4HE6RPTFS";

WiFiClient client;

// Telegram
#define BOTtoken "8685039163:AAHy0PKziTDCy8E4kSyBUoQ3DfGG7ZCAvSQ"
#define CHAT_ID "6645660919"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOTtoken, secured_client);

unsigned long lastUpload = 0;

// Sensor values
float ambientTemp, humidity, bodyTemp;
int ax, ay, az;

int lastMovementState = -1;

void setup()
{
  Serial.begin(115200);

  SPI.begin(18,19,23,5);
  SPI.setFrequency(8000000);

  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  delay(10);
  digitalWrite(RST, HIGH);
  delay(10);

  LoRa.setPins(SS,RST,DIO0);

  if(!LoRa.begin(433E6)){
    Serial.println("LoRa init failed");
    while(1);
  }

  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(250E3);
  LoRa.setTxPower(14);
  LoRa.setSyncWord(0xF3);

  LoRa.receive();   // important

  // WiFi connect
  WiFi.begin(ssid,password);

  Serial.print("Connecting WiFi");

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  ThingSpeak.begin(client);

  secured_client.setInsecure();
  secured_client.setTimeout(15000);

  delay(2000);

  bot.sendMessage(CHAT_ID,"Gateway Started Successfully","");
}

void loop()
{

  int packetSize = LoRa.parsePacket();
  Serial.print("Packet size: ");
  Serial.println(packetSize);

  if(packetSize)
  {
    Serial.println("\nPacket detected!");

    String data = "";

    while(LoRa.available())
    {
      char c = (char)LoRa.read();
      data += c;
    }

    Serial.print("Raw Data: ");
    Serial.println(data);

    sscanf(data.c_str(),"%f,%f,%f,%d,%d,%d",
           &ambientTemp,&humidity,&bodyTemp,&ax,&ay,&az);

    float movement = sqrt((float)ax*ax + (float)ay*ay + (float)az*az);

    int movementState;

    if(movement > 20000)
        movementState = 2;
    else if(movement > 15000)
        movementState = 1;
    else
        movementState = 0;

    int heatStress = (ambientTemp > 35);
    int sleepState = (movementState == 0);
    int rumination = (movementState == 1);
    int alertCode = (bodyTemp > 39);

    Serial.println("\n===== Animal Health Status =====");

    Serial.print("Body Temperature: ");
    Serial.println(bodyTemp);

    Serial.print("Ambient Temperature: ");
    Serial.println(ambientTemp);

    Serial.print("Humidity: ");
    Serial.println(humidity);

    Serial.print("Movement Level: ");
    Serial.println(movementState);

    Serial.print("Heat Stress: ");
    Serial.println(heatStress);

    Serial.print("Sleep State: ");
    Serial.println(sleepState);

    Serial.print("Rumination: ");
    Serial.println(rumination);

    Serial.print("Alert Code: ");
    Serial.println(alertCode);

    Serial.println("===============================");

    // TELEGRAM ALERTS

    if(bodyTemp > 39)
    {
      String msg = "⚠️ FEVER ALERT\n";
      msg += "Body Temp: " + String(bodyTemp) + " C\n";
      msg += "Humidity: " + String(humidity) + "%";

      bot.sendMessage(CHAT_ID,msg,"");
    }

    if(ambientTemp > 35)
    {
      String msg = "🔥 HEAT STRESS ALERT\n";
      msg += "Ambient Temp: " + String(ambientTemp) + " C";

      bot.sendMessage(CHAT_ID,msg,"");
    }

    if(movementState != lastMovementState)
    {
      if(movementState == 0)
          bot.sendMessage(CHAT_ID,"💤 Animal Sleeping","");

      if(movementState == 2)
          bot.sendMessage(CHAT_ID,"⚡ High Animal Movement","");

      lastMovementState = movementState;
    }

    // THINGSPEAK UPDATE

    if(millis() - lastUpload > 15000)
    {
      ThingSpeak.setField(1, bodyTemp);
      ThingSpeak.setField(2, ambientTemp);
      ThingSpeak.setField(3, humidity);
      ThingSpeak.setField(4, movementState);
      ThingSpeak.setField(5, heatStress);
      ThingSpeak.setField(6, sleepState);
      ThingSpeak.setField(7, rumination);
      ThingSpeak.setField(8, alertCode);

      ThingSpeak.writeFields(channelID,writeAPI);

      Serial.println("Uploaded to ThingSpeak");

      lastUpload = millis();
    }
  }

  delay(100);
}