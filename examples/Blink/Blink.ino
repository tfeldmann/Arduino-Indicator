#include <Indicator.h>

Indicator led;

void setup()
{
    pinMode(13, OUTPUT);
    led.blink();
}

void loop()
{
    digitalWrite(13, led.update());
}
