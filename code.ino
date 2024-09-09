#include <Servo.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo servo;
const int trigPin = D6;
const int echoPin = D5;

char ssid[] = "Veendy-Suseno";                      // name wifi
char pass[] = "Admin12345";                         // password wifi
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
        Blynk.notify("Ada sampah masuk"); // Send notification when distance condition is met
        delay(3000); // Wait to avoid continuous notification
    } else {
        servo.write(90); // Adjust to a default position within valid range
    }

    // Waiting 60 ms between loops
    delay(60);
    Blynk.run(); // Run Blynk operations
}
