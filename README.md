# 🚗 Bluetooth-Controlled Robot Car with Arduino

A remote-controlled vehicle project capable of moving forward, backward, turning, and detecting obstacles using an ultrasonic sensor.  
The robot also includes *turn signal LEDs* to indicate direction and can be controlled via *Bluetooth* from a smartphone.

## 📌 Features
- *Bluetooth control* from a mobile app.
- *Movements*: forward, backward, turn left/right, stop.
- *Obstacle detection* with HC-SR04 ultrasonic sensor.
- *Turn signal LEDs* to indicate direction during turns.
- *Servo motor* to rotate the ultrasonic sensor.
- *Safety*: prevents movement if an obstacle is detected within 13 cm.

## 🔧 Components Used
- Arduino board Uno
- Bluetooth module HC-05 
- L298N motor driver
- 2 DC motors
- HC-SR04 ultrasonic sensor
- Servo motor
- LEDs + resistors
- Battery or power supply
- Robot chassis

## 📲 Bluetooth Commands
| Command | Action |
|---------|--------|
|    F    | Move forward |
|    B    | Move backward |
|    L    | Turn left (left LED blinks) |
|    R    | Turn right (right LED blinks) |
|    S    | Stop |

## 🚀 How to Use
1. Upload the code.ino file to your Arduino board.
2. Connect your Bluetooth module (HC-05/HC-06).
3. Power the robot with batteries.
4. Open a Bluetooth control app on your smartphone (e.g., "Arduino Bluetooth Control").
5. Pair with the Bluetooth module and use the commands above.

## 📷 Demo Video

https://www.linkedin.com/posts/donald-oke-343369331_arduino-robotics-iot-activity-7361918335904641024-RIOG?utm_source=share&utm_medium=member_android&rcm=ACoAAFOGWKMBPVfuLxRoG5OZsoEwHf3kVfihuD4

✍ *Author*: MELRIQU  
📅 *Date*: August 15 2025
