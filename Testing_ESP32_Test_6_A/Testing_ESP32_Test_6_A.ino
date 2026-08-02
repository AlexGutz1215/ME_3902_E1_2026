#include "DHT.h"
#include "math.h"

#define DHTPIN 23
#define DHTTYPE DHT22

#define THERMISTORPIN 34

DHT dht(DHTPIN, DHTTYPE);

const float SeriesResistor = 10000; // 10 k resistor
const float NominalResistance = 10000; // resistance at 25 degrees
const float NominalTemperature = 25.0;
const float BCoefficient = 3950.0; // Spec sheet
const float ADCMax = 4095.0; // ESP32 ADC resolution

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

  float AdcVal = analogRead(THERMISTORPIN);

  if (AdcVal >= ADCMax) AdcVal - ADCMax - 1;
  if (AdcVal <= 0) AdcVal = 1;
  // To avoid issues with /0

  float resistance = SeriesResistor / ((ADCMax/AdcVal) - 1.0);

  float steinhart;
  steinhart = resistance / NominalResistance;
  steinhart = log(steinhart);
  steinhart /= BCoefficient;
  steinhart += 1.0/(NominalTemperature + 273.15);
  steinhart = 1.0/steinhart;

  float tempC = steinhart - 273.15;

  Serial.print("Thermistor Temp in deg C: ");
  Serial.println(tempC);

  delay(1000);

}
