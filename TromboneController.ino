// ---------------------------------------------------------------- //
// Arduino Leonardo TromboneChamp Controller Code
// Author: Jason Perfetto
// Using Arduino IDE 2.0.0
// Using HC-SR04 Module, Arduino Leonardo, Press-Button
// Tested on 26 September 2022
// ---------------------------------------------------------------- //
#include <AbsMouse.h>
#include <Keyboard.h>

#define echoPin 3    // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4    //attach pin D3 Arduino to pin Trig of HC-SR04
#define buttonPin 2  // attach pin D4 to the Button
#define ledPin 13    // 13 is the pin designation for the onboard LED on the Arduino chip

// instance variables
int buttonState = 0;    // initialize button as un-pressed
long duration;          // duration of sound wave travel
float distance;         // distance measurement
const int yMax = 1080;  // max screen resolution in Y axis
const int xMax = 1920;  // max screen resolution in X axis
const int yMin = 0;
const int xMin = 0;
const float dMax = 37.0;  // max allowable range for distance sensor (cm)
const float dMin = 4.0;   // min allowable range for distance sensor (cm)

float dRange = dMax - dMin;   // total potential trombone slide travel distance
float yStep = yMax / dRange;  // ratio of pixels to distance for translating slide position to mouse position
float xMid = xMax / 2;        // midpoint of the screen horizontally

void setup() {
  initButton();
  initDistanceSensor();
}

void loop() {
  listenForButtonClick();
  listenToDistanceSensor();
  moveMouse();
}

void initButton() {
  pinMode(buttonPin, INPUT);  // Sets the button as an INPUT
}

void initDistanceSensor() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Sets the echoPin as an INPUT
  AbsMouse.init(xMax, yMax);
  Keyboard.begin();
  Serial.begin(9600);  // Serial Communication is starting with 9600 of baudrate speed
}

void moveMouse() {
  if (distance <= dMax && distance >= dMin) {
    float yActual = (yStep * distance) - 100; // 100 pixel shift-down to accomodate notches / improve gameplay calibration - adjust if needed 
    AbsMouse.move(xMid, yActual);
  }
}

void listenToDistanceSensor() {
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
  distance = distance();
  logDistance();
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

  float distance() {
    return float(duration * 0.034 / 2.0);
  }

  void logDistance() {
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
  }
}