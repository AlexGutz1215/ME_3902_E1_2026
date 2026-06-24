const int LED1_Pin=2;

const int button1_Pin=3;

int button1_state=0;

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
	pinMode(LED1_Pin, OUTPUT); // Set the LED anode pin as an output

  pinMode(button1_Pin, INPUT);
}


void loop() {
  //Read button state
  button1_state = digitalRead(button1_Pin);

  // digitalWrite(LED1_Pin, HIGH); // Turn the LED on
  // delay(1000); // Wait for 1 second
  // digitalWrite(LED1_Pin, LOW); // Turn the LED off
  // delay(1000); // Wait for 1 second before repeating

  if (button1_state==HIGH)
  {
    Serial.println("Button is Pressed"); // Print a message to output terminal
    digitalWrite(LED1_Pin, HIGH); // Turn LED on
  }

  else
  {
    Serial.println("Button is no longer Pressed"); // Print a message to output terminal
    digitalWrite(LED1_Pin, LOW); // Turn LED off
  }
  delay(100);
}