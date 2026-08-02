// Motor Driver Pin Definitions

const int enA = 14;
const int in1 = 27;
const int in2 = 26;

void setup()
{
  // Serial Monitor
  Serial.begin(115200);

  delay(500);

  // Intializing motor driver pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Start with motor off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);

  // Intructions to the user
  Serial.println("ESP 32 Trails");
  Serial.println("Type 'START' to turn motor on");
  Serial.println("Type 'STOP' to rurn motor off");
}

void loop()
{
  if (Serial.available() > 0) // checking if user has typed anything in the serial monitor
  {
    String command = Serial.readStringUntil('\n');

    command.trim();
    command.toUpperCase();
    // Clean up the string - not following the instructions

    Serial.print("Command Recieved");
    Serial.println(command);

    // Motor logic
    if (command=="START")
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 200);
      Serial.println("Motor is Running");
    }

    else if (command=="STOP")
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enA, 0);
      Serial.println("Motor is not Running");
    }

    else
    {
      Serial.println("Unknown command typed");
    }

  }
  
}
