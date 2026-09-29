#ifndef SERVO_WRAP_H
#define SERVO_WRAP_H

#include <Arduino.h>
#include <ESP32Servo.h> // вместо Servo.h (AVR)

// Обёртка над сервой: работает в процентах 0..100.
// 0%   -> угол angleAtZero
// 100% -> угол angleAtFull  (может быть меньше angleAtZero - инверсия)
class ServoWrap {
public:
    void attach(uint8_t pin);
    void attach(uint8_t pin, uint8_t angleAtZero, uint8_t angleAtFull);

    uint8_t getMin();
    uint8_t getMax();
    void setMin(uint8_t angleAtZero);
    void setMax(uint8_t angleAtFull);

    int read();
    void write(int percent);

private:
    Servo _servo;
    uint8_t _min { 0 };
    uint8_t _max { 180 };
};

#endif // SERVO_WRAP_H
