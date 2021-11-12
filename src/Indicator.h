#pragma once

class Indicator
{
public:
    enum Speed
    {
        SLOW,
        FAST,
    };

    // settings
    int fast_on_ms;
    int fast_off_ms;
    int fast_pause_ms;
    int fast_ending_ms;
    int slow_on_ms;
    int slow_off_ms;
    int slow_pause_ms;
    int slow_ending_ms;

    // realtime state of the indicator

    Indicator();
    void configure(
        int fast_on_ms,
        int fast_off_ms,
        int fast_pause_ms,
        int fast_ending_ms,
        int slow_on_ms,
        int slow_off_ms,
        int slow_pause_ms,
        int slow_ending_ms);

    bool isOn();

    void toggle();
    void permanent(bool enable);
    void blink(Speed speed = Speed::FAST);
    void flash();
    void count(int num, bool repeat = true, Speed speed = Speed::FAST);
    void count(int num1, int num2, bool repeat = true, Speed speed = Speed::FAST);

    virtual bool update();

private:
    bool state_;
    Speed speed_;
    enum Mode
    {
        OFF,
        ON,
        BLINKING,
        COUNTING,
    } mode_;
    int counter1_;
    int counter2_;
    bool repeat_;

    // used for remembering counting settings
    int num1_;
    int num2_;

    unsigned long long lastToggle_;
    void set_(bool en);
};
