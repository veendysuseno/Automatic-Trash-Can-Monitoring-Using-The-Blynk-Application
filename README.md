# Automatic Trash Can Monitoring Using The Blynk Application

## Overview

This project demonstrates an automatic trash can monitoring system using an ESP8266 microcontroller, an ultrasonic sensor, and a servo motor. The system monitors the trash can's fill level and uses the Blynk application to send notifications when the trash can is full. The servo motor adjusts based on the measured distance to manage the trash can's lid.

## Components Used

- **ESP8266**: Microcontroller for WiFi connectivity and processing.
- **Ultrasonic Sensor (HC-SR04)**: Measures the distance to the trash can's contents.
- **Servo Motor**: Controls the trash can's lid.
- **Blynk Platform**: Provides notifications and remote monitoring.

## Libraries

- **Servo.h**: Controls the servo motor.
- **ESP8266WiFi.h**: Manages WiFi connections.
- **BlynkSimpleEsp8266.h**: Handles Blynk communication.

## Code

```cpp
#include <Servo.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo servo;
const int trigPin = D6;
const int echoPin = D5;

char ssid[] = "Veendy-Suseno";                      // WiFi network name
char pass[] = "Admin12345";                         // WiFi password
char auth[] = "d6d09d7bd9f6409bae0bc64774020b68";   // Blynk authentication token

void setup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    servo.attach(D3);

    // Debug console
    Serial.begin(9600);

    // Blynk initialization
    Blynk.begin(auth, ssid, pass);
}

void loop(){
    int duration, distance;

    // Trigger ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // Small delay to ensure accurate measurement
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure pulse width
    duration = pulseIn(echoPin, HIGH);

    // Calculate distance in cm
    distance = (duration / 2) / 29.1;

    // Debug output
    Serial.print("Distance: ");
    Serial.println(distance);

    // Control servo based on distance
    if (distance <= 30 && distance >= 0) {
        servo.write(10);
        Blynk.notify("Ada sampah masuk"); // Send notification when trash can is full
        delay(3000); // Wait to avoid continuous notification
    } else {
        servo.write(90); // Adjust to a default position within valid range
    }

    // Waiting 60 ms between loops
    delay(60);
    Blynk.run(); // Run Blynk operations
}
```

## Setup

1. Install Libraries: Ensure the Servo, ESP8266WiFi, and Blynk libraries are installed in your Arduino IDE.

2. Blynk App Setup:

   - Create a new project in the Blynk app.
   - Obtain your Auth Token and replace it in the code.
   - Configure notifications in the app to receive alerts.

3. Hardware Connections:

   - Connect the ultrasonic sensor to the specified pins (D6 for Trig, D5 for Echo).
   - Connect the servo motor to pin D3.

4. Upload Code: Upload the code to your ESP8266 using the Arduino IDE.

5. Power and Test: Power your ESP8266 and monitor the serial output. Ensure the Blynk app receives notifications when the trash can is full.

## Notes

- Adjust servo.write() values as needed based on your servo's range and trash can lid position.
- Ensure your WiFi credentials and Blynk auth token are correctly set in the code.
- The Blynk.notify() function will send a notification to your mobile device when the trash can is within 30 cm of the sensor.

## Troubleshooting

- No Notifications: Check your Blynk project settings and ensure notifications are enabled.
- Incorrect Distance: Verify the ultrasonic sensor's wiring and positioning.
