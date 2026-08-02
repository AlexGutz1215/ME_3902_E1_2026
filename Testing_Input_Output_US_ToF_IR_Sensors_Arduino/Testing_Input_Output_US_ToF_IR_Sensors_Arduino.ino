//Code to be Updated

#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Define the pin numbers for the Infrared obstacle avoidance sensor
const int sensorPin = 2;
// Global variables and pin definitions
// Define the pins for the HC-SR04 sensor
const int trigPin5 = 7; // Pin that triggers the ultrasonic pulse
const int echoPin5 = 4; // Pin that receives the echo signal

// Variables to store the pulse duration and calculated distance
float duration5, distance5;
VL53L0X sensor;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
  pinMode(sensorPin, INPUT);  // Set sensorPin as input
  // Setup function: runs once at startup
  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin5, OUTPUT); // Set trigger pin as output
  pinMode(echoPin5, INPUT);  // Set echo pin as input
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
  delay(500);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  {
    while(true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Hello, World!");
  display.display();
  delay(1000);
}


void loop() {
  // ---- Read IR obstacle sensor ----
  int irValue = digitalRead(sensorPin);  // Read the digital value from the sensor

  delay(50);  // Main loop: continuously measures distance

  // ---- Read HC-SR04 ultrasonic sensor ----
  // Ensure the trigger pin is LOW to start
  digitalWrite(trigPin5, LOW);
  delayMicroseconds(2); // Short delay to allow sensor stabilization

  // Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10); // Pulse duration
  digitalWrite(trigPin5, LOW);

  // Read the duration of the echo pulse (in microseconds)
  duration5 = pulseIn(echoPin5, HIGH);

  // Calculate the distance (cm) using the speed of sound (0.0343 cm/us)
  // Dividing by 2 accounts for the round-trip distance
  distance5 = (duration5 * 0.0343) / 2;

  // ---- Read VL53L0X time-of-flight sensor ----
  int vl53Range = sensor.readRangeContinuousMillimeters();
  bool vl53Timeout = sensor.timeoutOccurred();

  // ---- Print each sensor's output independently to the Serial Monitor ----
  Serial.print("IR Sensor: ");
  Serial.println(irValue);

  Serial.print("HC-SR04 Duration: ");
  Serial.println(duration5);

  Serial.print("HC-SR04 Distance: ");
  Serial.println(distance5);

  Serial.print("VL53L0X Range: ");
  Serial.print(vl53Range);
  if (vl53Timeout) { Serial.print(" TIMEOUT"); }
  Serial.println();

  // ---- Print each sensor's output independently to the OLED display ----
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Sensor Readings");

  display.setCursor(0, 12);
  display.print("IR: ");
  display.println(irValue);

  display.setCursor(0, 24);
  display.print("Duration: ");
  display.println(duration5);

  display.setCursor(0, 36);
  display.print("Distance: ");
  display.print(distance5);
  display.println(" cm");

  display.setCursor(0, 48);
  display.print("VL53L0X: ");
  display.print(vl53Range);
  display.print(" mm");
  if (vl53Timeout) { display.print(" TO"); }

  display.display();

  // Short delay before the next measurement
  delay(100);
}