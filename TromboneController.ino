// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPin 3   // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4    //attach pin D3 Arduino to pin Trig of HC-SR04
#define buttonPin 2  // attach pin D4 to the Button
#define ledPin 13    // attach pin D4 to the Button
#include <AbsMouse.h>
#include <Keyboard.h>

// defines variables
int buttonState = 0;
long duration;   // variable for the duration of sound wave travel
float distance;  // variable for the distance measurement
float lastDistance;
float maxDistance = 75.0;  // max range for trombone slide
float minDistance = 5.0;   // min range for trombone slide
const int yMax = 1080;
const int yMin = 0;
const int xMax = 1920;
const int xMin = 0;
const float dMax = 37.0;
const float dMin = 4.0;
float dRange = dMax - dMin;
float yStep = yMax / dRange;
float xMid = xMax / 2;

void setup() {
  pinMode(trigPin, OUTPUT);   // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);    // Sets the echoPin as an INPUT
  pinMode(buttonPin, INPUT);  // Sets the button as an INPUT
  Serial.begin(9600);
  AbsMouse.init(xMax, yMax);
  Keyboard.begin();         // // Serial Communication is starting with 9600 of baudrate speed
}

void loop() {
  listenForButtonClick();
  listenToDistanceSensor();
  if (distance <= dMax && distance >= dMin) {
    float yActual = (yStep * distance) - 100;
    AbsMouse.move(xMid, yActual);
  }
}

void listenToDistanceSensor() {
  lastDistance = distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = float(duration * 0.034 / 2.0);
  float diff = distance - lastDistance;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Diff: ");
  Serial.println(diff);
}


void listenForButtonClick() {
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    Keyboard.press(32);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    Keyboard.release(32);
  }
}