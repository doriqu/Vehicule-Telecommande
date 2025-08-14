#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(10, 11); // RX, TX for Bluetooth

// Servo object creation
Servo myServo;

float duration;
float distance;

// L298N pin definitions
int in1 = 8;  // IN1 Sense1 M1
int in2 = 7;  // IN2 Sense2 M1
int in3 = 6;  // IN3 Sense2 M2
int in4 = 5;  // IN4 Sense1 M2

// Ultrasonic sensor pin definitions
int echoPin = 2;
int triggerPin = 4;

// LED pin definitions
int leftLed = 12;
int rightLed = 13;

//Direction of servo
char etat = "CENTER";

// FUNCTION PROTOTYPES
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopRobot();
float calculateDistance();
bool checkObstacle();
void blinkLeftLed();
void blinkRightLed();

void setup() {
  // L298N Pin Initialization
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // LED Pins
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);

  // Ultrasonic Sensors: Pin Initialization
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);

  // Attach servo to its pin
  myServo.attach(3);
  myServo.write(90); // Set initial servo position (center)
  delay(500);
  myServo.detach();
  
  blinkLeftLed();
  blinkRightLed();

  Serial.begin(9600);     // Initialize serial port
  BTSerial.begin(9600);   // Initialize Bluetooth
  Serial.println("Robot Started");
}

void loop() {
  if (BTSerial.available()) {
    Serial.println("Let's go!");
    char command = BTSerial.read(); // Read received command
    switch (command) {
      case 'F':
        // Check if an obstacle prevents moving forward
        if (etat != "CENTER") {
          myServo.attach(3);
          myServo.write(90); // Return servo to front direction
          delay(500);
          etat = "CENTER";
          myServo.detach();
        }

        if (checkObstacle() == true) {
          Serial.println("IMPOSSIBLE TO MOVE FORWARD");
          break;
        } else {
          moveForward();
          break;
        }

      case 'B':
        moveBackward();
        break;

      case 'L':
        // Check if an obstacle prevents turning left
       if (etat != "LEFT") {
          myServo.attach(3);
          myServo.write(180); // Return servo to left direction
          delay(500);
          etat = "LEFT";
          myServo.detach();
        }

        if (checkObstacle() == true) {
          Serial.println("IMPOSSIBLE TO GO LEFT");
          break;
        } else {
          blinkLeftLed();
          turnLeft();
          break;
        }

      case 'R':
        // Check if an obstacle prevents turning right
       if (etat != "RIGHT") {
          myServo.attach(3);
          myServo.write(0); // Return servo to front direction
          delay(500);
          etat = "RIGHT";
          myServo.detach();
        }

        if (checkObstacle() == true) {
          Serial.println("IMPOSSIBLE TO GO RIGHT");
          break;
        } else {
          blinkRightLed();
          turnRight();
          break;
        }
      case 'S':
        stopRobot();
        break;
    }
    delay(100);
  }
}

// Function to move forward (both motors forward)
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Function to move backward (both motors backward)
void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to turn left (right motor normal speed, left motor slow speed)
void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}

// Function to turn right (left motor slow speed, right motor normal speed)
void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Function to read distance from a potential obstacle in front
float calculateDistance() {
  // Set the trigger to low
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Set the trigger to high
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Read echo sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance); // This prints the distance
  return distance;
}

// Verification function
bool checkObstacle() {
  float currentDistance = calculateDistance(); // Call calculateDistance once
  if ((currentDistance < 13) && (currentDistance != 0)) {
    return true;
  } else {
    return false;
  }
}

// Function to blink the left LED
void blinkLeftLed() {
  Serial.println("LEFT");
  digitalWrite(leftLed, HIGH);
  delay(60);
  digitalWrite(leftLed, LOW);
  delay(60);
  digitalWrite(leftLed, HIGH);
  delay(60);
  digitalWrite(leftLed, LOW);
  delay(60);
}

// Function to blink the right LED
void blinkRightLed() {
  Serial.println("RIGHT");
  digitalWrite(rightLed, HIGH);
  delay(60);
  digitalWrite(rightLed, LOW);
  delay(60);
  digitalWrite(rightLed, HIGH);
  delay(60);
  digitalWrite(rightLed, LOW);
  delay(60);
}