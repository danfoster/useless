#include "LowPower.h"

// Use pin 2 as wake up pin
const int wakeUpPin = 2;
const int motorForwardPin = 3;
const int motorBackPin = 5;

// the setup function runs once when you press reset or power the board
void setup()
{
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(motorForwardPin, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(wakeUpPin, INPUT);

    Serial.begin(115200); // open the serial port at 9600 bps:
    Serial.print("Hello\n");
}

void wakeUp()
{
    // Just a handler for the pin interrupt.
}

// the loop function runs over and over again forever
void loop()
{
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    analogWrite(motorForwardPin, 0);
    attachInterrupt(0, wakeUp, LOW);

    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    Serial.print("Sleep Time\n");
    delay(100);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    Serial.print("Good Morning\n");

    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0);

    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    analogWrite(motorForwardPin, 255);
    while (digitalRead(wakeUpPin) == LOW)
    {
    }
    analogWrite(motorForwardPin, 0);
    analogWrite(motorBackPin, 255);
    delay(400);
    analogWrite(motorBackPin, 0);
}
