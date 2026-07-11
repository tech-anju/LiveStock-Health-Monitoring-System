#include <Wire.h>
#include <DHT.h>

#define MPU_ADDR 0x68
#define MLX_ADDR 0x5A

#define DHTPIN 13
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

int16_t accelX, accelY, accelZ;

void setup() {

  Serial.begin(115200);

  Wire.begin(21,22);

  dht.begin();

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("All Sensors Ready");
}

void loop() {

  // ---------- MPU6050 ----------
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR,6,true);

  accelX = Wire.read()<<8 | Wire.read();
  accelY = Wire.read()<<8 | Wire.read();
  accelZ = Wire.read()<<8 | Wire.read();

  // ---------- DHT22 ----------
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // ---------- MLX90614 ----------
  uint16_t data;

  // Object temperature
  Wire.beginTransmission(MLX_ADDR);
  Wire.write(0x07);
  Wire.endTransmission(false);
  Wire.requestFrom(MLX_ADDR,3);

  data = Wire.read();
  data |= Wire.read() << 8;
  Wire.read();

  float objectTemp = data * 0.02 - 273.15;

  // Ambient temperature
  Wire.beginTransmission(MLX_ADDR);
  Wire.write(0x06);
  Wire.endTransmission(false);
  Wire.requestFrom(MLX_ADDR,3);

  data = Wire.read();
  data |= Wire.read() << 8;
  Wire.read();

  float ambientTemp = data * 0.02 - 273.15;

  // ---------- Serial Output ----------
  Serial.println("---------------------------");

  Serial.print("DHT Temp: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("MLX Object Temp: ");
  Serial.print(objectTemp);
  Serial.println(" C");

  Serial.print("MLX Ambient Temp: ");
  Serial.print(ambientTemp);
  Serial.println(" C");

  Serial.print("Accel X: ");
  Serial.println(accelX);

  Serial.print("Accel Y: ");
  Serial.println(accelY);

  Serial.print("Accel Z: ");
  Serial.println(accelZ);

  delay(2000);
}