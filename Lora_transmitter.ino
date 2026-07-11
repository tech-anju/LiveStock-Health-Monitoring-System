#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2

void setup() {
  Serial.begin(115200);

  SPI.begin(18,19,23,5);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa Sender Started");
}

void loop() {
  Serial.println("Sending packet");

  LoRa.beginPacket();
  LoRa.print("HELLO RECEIVER");
  LoRa.endPacket();

  delay(2000);
}