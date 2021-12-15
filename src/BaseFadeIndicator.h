#pragma once
#include <Arduino.h>

#include "BaseIndicator.h"

// logarithmic led brightness curve
// clang-format off
static const uint8_t LED_LOG_CURVE[256] = {
   0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
   1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,
   3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  4,
   4,  4,  4,  4,  4,  4,  5,  5,  5,  5,  5,  5,  5,  5,  5,  6,
   6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  7,  8,  8,  8,
   8,  8,  8,  9,  9,  9,  9,  9, 10, 10, 10, 10, 10, 11, 11, 11,
  11, 12, 12, 12, 12, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 16,
  16, 16, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
  23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 28, 29, 30, 30, 31, 32,
  32, 33, 34, 35, 35, 36, 37, 38, 39, 39, 40, 41, 42, 43, 44, 45,
  46, 47, 48, 49, 50, 51, 52, 53, 55, 56, 57, 58, 59, 61, 62, 63,
  65, 66, 68, 69, 71, 72, 74, 76, 77, 79, 81, 82, 84, 86, 88, 90,
  92, 94, 96, 98,100,102,105,107,109,112,114,117,119,122,124,127,
 130,133,136,139,142,145,148,151,155,158,162,165,169,172,176,180,
 184,188,192,196,201,205,210,214,219,224,229,234,239,244,250,255,
};
// clang-format on

class BaseFadeIndicator : public BaseIndicator
{
public:
    BaseFadeIndicator(bool logarithmic = false, int fade_speed = 30)
        : BaseIndicator(),
          value_(0),
          fade_speed_(abs(fade_speed)),
          logarithmic_(logarithmic)
    {
        setSpeed(300, 300, 750, 1200);
        lastUpdate_ = millis();
        write(0);
    }

    int update()
    {
        int state = BaseIndicator::update();
        uint32_t time = millis();
        if (time - lastUpdate_ > 10)
        {
            lastUpdate_ = time;
            int diff = state * 255 - value_;
            value_ += constrain(diff, -fade_speed_, fade_speed_);

            // only write changes
            if (diff)
            {
                int result = logarithmic_ ? LED_LOG_CURVE[value_] : value_;
                write(result);
                return result;
            }
        }
        if (logarithmic_)
            return LED_LOG_CURVE[value_];
        return value_;
    }

    virtual void write(int state)
    {
        // write() is only called on changes.
        // You can override it and set your indicator here.
    }

private:
    int value_;
    int fade_speed_;
    bool logarithmic_;
    unsigned long long lastUpdate_;
};
