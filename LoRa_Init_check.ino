#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2

void setup() {
  Serial.begin(115200);
  
  LoRa.setPins(SS, RST, DIO0);

  Serial.println("Checking LoRa...");

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init FAILED");
    while (1);
  }

  Serial.println("LoRa init SUCCESS");
}

void loop() {
}