#include <BluetoothSerial.h>

// Pin definitions
#define IN1 13  // Motor A forward
#define IN2 12  // Motor A backward
#//define ENA 27  // Motor A PWM (speed control)
#define IN3 14  // Motor B forward
#define IN4 25  // Motor B backward
//#define ENB 26  // Motor B PWM (speed control)

// Bluetooth setup
BluetoothSerial SerialBT;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  SerialBT.begin("ranger"); // Bluetooth device name
  Serial.println("Bluetooth Device is Ready to Pair");

  // Configure motor control pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //pinMode(ENA, OUTPUT);  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //pinMode(ENB, OUTPUT);

  // Set motors to stop initially
  stopMotors();
}

void loop() {
  // Check if data is available from Bluetooth
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.print("Received Command: ");
    Serial.println(command);

    // Execute command
    switch (command) {
      case 'F': // Forward
        forward(200); // Default speed: 200
        break;
      case 'B': // Backward
        backward(200); // Default speed: 200
        break;
      case 'L': // Left
        turnLeft(200); // Adjust speed for turning: 150
        break;
      case 'R': // Right
        turnRight(200); // Adjust speed for turning: 150
        break;
      case 'S': // Stop
        stopMotors();
        break;
      default:
        Serial.println("Invalid Command");
        break;
    }
  }
}

// Function to move forward
void forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //analogWrite(ENA, speed); // Set speed for motor A
  //analogWrite(ENB, speed); // Set speed for motor B
  SerialBT.println("Moving Forward");
}

// Function to move backward
void backward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //analogWrite(ENA, speed); // Set speed for motor A
  //analogWrite(ENB, speed); // Set speed for motor B
  SerialBT.println("Moving Backward");
}

// Function to turn left
void turnLeft(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //analogWrite(ENA, speed); // Reduce speed for motor A
  //analogWrite(ENB, speed);     // Full speed for motor B
  SerialBT.println("Turning Left");
}

// Function to turn right
void turnRight(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //analogWrite(ENA, speed);     // Full speed for motor A
  //analogWrite(ENB, speed); // Reduce speed for motor B
  SerialBT.println("Turning Right");
}

// Function to stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //analogWrite(ENA, 0);  // Disable motor A
  //analogWrite(ENB, 0);  // Disable motor B
  SerialBT.println("Stopped");
}
