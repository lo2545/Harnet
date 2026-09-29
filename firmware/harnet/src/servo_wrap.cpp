#include "servo_wrap.h"

// Диапазон импульсов как у стандартной AVR-библиотеки Servo (544..2400 мкс).
// В ESP32Servo по умолчанию 500..2500, поэтому задаём явно, чтобы углы совпадали с оригиналом.
static const int SERVO_MIN_US = 544;
static const int SERVO_MAX_US = 2400;

void ServoWrap::attach(uint8_t pin)
{
    _servo.setPeriodHertz(50);
    _servo.attach(pin, SERVO_MIN_US, SERVO_MAX_US);
}

void ServoWrap::attach(uint8_t pin, uint8_t angleAtZero, uint8_t angleAtFull)
{
    attach(pin);
    _min = angleAtZero;
    _max = angleAtFull;
}

uint8_t ServoWrap::getMin() { return _min; }
uint8_t ServoWrap::getMax() { return _max; }
void ServoWrap::setMin(uint8_t angleAtZero) { _min = angleAtZero; }
void ServoWrap::setMax(uint8_t angleAtFull) { _max = angleAtFull; }

int ServoWrap::read()
{
    return map(_servo.read(), _min, _max, 0, 100);
}

void ServoWrap::write(int percent)
{
    // В оригинале было `percent > 100 && percent < 0` - условие никогда не выполнялось.
    if (percent < 0 || percent > 100)
        return;
    _servo.write(map(percent, 0, 100, _min, _max));
}
