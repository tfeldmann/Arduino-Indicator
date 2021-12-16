#include <Indicator.h>

Indicator led(13);
SpeedSetting mySettings = {
    .on_ms = 100,
    .off_ms = 100,
    .pause_ms = 2000,
    .ending_ms = 2000,
};

void setup()
{
    // blink 2x on repeat with custom settings
    led.pattern(2, true, mySettings);
}

void loop()
{
    led.update();
}
