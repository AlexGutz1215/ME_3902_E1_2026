#include "DHT.h"

#define DHTPIN 23
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Initializing");
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Not reading data from DHT 22");
  }

  Serial.print("Humidity in %: ");
  Serial.println(humidity);
  Serial.print("Temperature in degree C: ");
  Serial.println(temperature);

}
