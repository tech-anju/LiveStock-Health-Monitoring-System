#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_MLX90614.h>
#include <MPU6050.h>

#define SS 5
#define RST 14
#define DIO0 2

#define DHTPIN 13
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
MPU6050 mpu;

unsigned long lastSend = 0;

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

  if(!LoRa.begin(433E6))
  {
    Serial.println("LoRa init failed");
    while(1);
  }

  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(250E3);
  LoRa.setTxPower(14);
  LoRa.setSyncWord(0xF3);
  // Start sensors
  Wire.begin(21,22);
  dht.begin();
  mlx.begin();
  mpu.initialize();

  Serial.println("Sensor Node Started");
}

void loop()
{
  if(millis() - lastSend > 2000)
  {
    float ambientTemp = dht.readTemperature();
    float humidity = dht.readHumidity();
    float bodyTemp = mlx.readObjectTempC();

    int16_t ax,ay,az,gx,gy,gz;
    mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);

    String data = String(ambientTemp) + "," +
                  String(humidity) + "," +
                  String(bodyTemp) + "," +
                  String(ax) + "," +
                  String(ay) + "," +
                  String(az);

    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket(true);

    Serial.println("Packet sent:");
    Serial.println(data);

    lastSend = millis();
  }
}