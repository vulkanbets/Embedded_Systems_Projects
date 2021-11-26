#include <Arduino.h>

int ledPin = 32;

void setup()
{
    // Set LED as output
    pinMode(ledPin, OUTPUT);
    
    // Serial monitor setup
    Serial.begin(115200);
}

void loop()
{
    Serial.println("LED ON!");
    digitalWrite(ledPin, HIGH);
    
    delay(1000);
    
    Serial.println("LED OFF!");
    digitalWrite(ledPin, LOW);
    
    delay(1000);
}
