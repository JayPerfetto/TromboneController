# TromboneController
Microcontroller code for a custom trombone USB controller to be used with Trombone Champ on Steam

## Instructions

1) Download and install the Arduino IDE from: https://www.arduino.cc/en/software

2) Complete the included circuitry diagram to build the microcontroller, Ultrasonic distance detector, and button. Pics / Diagrams in /diagrams
  a) Button - https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
  b) Ultrasonic Sensor - https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
  c) Assemble trombone from PVC components following the guide in /diagrams
  
3) Install the required library for your Board, the Keyboard library, and the AbsMouse library (https://github.com/jonathanedgecombe/absmouse)
4) Calibrate the program for your display size in the setup() function by changing the resolution in AbsMouse.init(x, y)
5) Upload the TromboneController sketch to your compatible microcontroller board.
*Note - not all Arduino boards will work as native USB devices - I used an Arduino Leonardo*

The Trombone will now be automatically on when the USB is plugged in, but will not control your mouse if the slide is fully in or fully extended, so that you can continue to use your computer normally (that's basically how to turn it "off")

6) Play Trombone Champ and have some laughs

