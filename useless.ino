// Base ESP8266
#include <ESP8266WiFi.h>
#include "user_interface.h"

WiFiClient WIFI_CLIENT;

#define LIGHT_SENSOR A0
#define LED 15
#define BUTTON 4

const byte interruptPin = D2;
const byte reverseStopPin = D3;
const byte forwardPin = D5;
const byte backwardPin = D6;

// This function runs once on startup
void setup()
{
    // Initialize the serial port
    Serial.begin(115200);

    pinMode(backwardPin, OUTPUT);
    pinMode(forwardPin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(reverseStopPin, INPUT_PULLUP);
    // randomSeed(analogRead(0));

    //  Force the ESP into client-only mode
    WiFi.mode(WIFI_STA);

    //  Enable light sleep
    wifi_set_sleep_type(LIGHT_SLEEP_T);

    while (!Serial)
    {
    }
    Serial.print("***********************\n");
    Serial.print("Ready\n");
}

void loop()
{
    // digitalWrite(ledPin, LOW);
    Serial.print("Sleepy Time\n");
    while (digitalRead(interruptPin))
    {
        delay(10);
    }
    Serial.print("Good Morning\n");
    if (!digitalRead(interruptPin))
    {
        delay(random(1000));
        forwardMovement();
        delay(random(1000));
        backwardMovement();
    }
}

void move(int dir)
{
    switch (dir)
    {
    case 1:
        analogWrite(backwardPin, 0);
        analogWrite(forwardPin, 255);
        break;
    case -1:
        analogWrite(backwardPin, 255);
        analogWrite(forwardPin, 0);
        break;
    default:
        analogWrite(backwardPin, 0);
        analogWrite(forwardPin, 0);
        break;
    }
}

void forwardMovement()
{
    switch (random(3))
    {
    case 0:
        forwardMovement1();
        break;
    case 1:
        forwardMovement2();
        break;
    case 2:
        forwardMovement3();
        break;
    }
    // forwardMovement2();
}

void forwardMovement1()
{
    // Simple movement that mimics the
    // original simple circuit
    Serial.println("Triggering Movement 1");
    move(1);
    while (!digitalRead(interruptPin))
    {
        delay(10);
    }
    move(0);
}

void forwardMovement2()
{
    // Creep out a little bit, pause and then continue
    Serial.println("Triggering Movement 2");
    delay(300);
    move(0);
    delay(random(2000));
    move(1);
    while (!digitalRead(interruptPin))
    {
        delay(10);
    }
    move(0);
}

void forwardMovement3()
{

    Serial.println("Triggering Movement 3");
    for (int i = 0; i < 3; i++)
    {
        move(1);
        delay(300);
        move(-1);
        delay(300);
    }
    move(1);
    while (!digitalRead(interruptPin))
    {
        delay(10);
    }
    move(0);
}

void backwardMovement()
{
    move(-1);

    while (digitalRead(reverseStopPin) == HIGH)
    {
        delay(100);
    }
    move(0);
}
