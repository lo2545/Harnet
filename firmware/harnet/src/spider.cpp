#include "spider.h"

void Spider::attachServos(ServoWrap* servs) { servos = servs; }

// Шаг вперёд: две пары ног по очереди.
void Spider::safeTimeStepForward()
{
    // Первая пара ног (0-2 и 9-11)
    safeTimeWrite(10, 100, 300);
    safeTimeWrite(9, 100, 300);
    safeTimeWrite(10, 70);
    safeTimeWrite(1, 100, 300);
    safeTimeWrite(0, 20, 300);
    safeTimeWrite(1, 70);

    for (int p = 0; p < 60; p += 5) {
        safeTimeWrite(0, 20 + p, 0);
        safeTimeWrite(9, 100 - p, 0);
    }
    spiderDelay(1000);

    // Вторая пара ног (3-5 и 6-8)
    safeTimeWrite(7, 100, 300);
    safeTimeWrite(6, 100, 300);
    safeTimeWrite(7, 70);
    safeTimeWrite(4, 100, 300);
    safeTimeWrite(3, 20, 300);
    safeTimeWrite(4, 70);

    for (int p = 0; p < 60; p += 5) {
        safeTimeWrite(3, 20 + p, 0);
        safeTimeWrite(6, 100 - p, 0);
    }
    spiderDelay(1000);
}

// Старый вариант шага (без safeTimeWrite), оставлен как есть.
void Spider::stepForward()
{
    servos[10].write(100);
    spiderDelay(2000);
    servos[9].write(100);
    spiderDelay(300);
    servos[10].write(70);
    spiderDelay(500);
    servos[1].write(100);
    spiderDelay(2000);
    servos[0].write(20);
    spiderDelay(300);
    servos[1].write(70);
    spiderDelay(2000);

    for (int i = 0; i < 50; i++) {
        servos[0].write(20 + i);
        servos[9].write(100 - i);
        spiderDelay(10);
    }
    spiderDelay(2000);

    servos[7].write(100);
    spiderDelay(2000);
    servos[6].write(100);
    spiderDelay(300);
    servos[7].write(70);
    spiderDelay(500);
    servos[4].write(100);
    spiderDelay(2000);
    servos[3].write(20);
    spiderDelay(300);
    servos[4].write(70);
    spiderDelay(2000);

    for (int i = 0; i < 50; i++) {
        servos[3].write(20 + i);
        servos[6].write(100 - i);
        spiderDelay(10);
    }
    spiderDelay(2000);
}

// Оригинал ждал в цикле, пока servo.read() совпадёт с целевым значением.
// Но Servo::read() возвращает последнее ЗАПИСАННОЕ значение, а не реальное положение,
// так что цикл либо выходил сразу, либо мог зависнуть навсегда из-за округления map().
// Реальной обратной связи у обычной серво нет - поэтому просто пишем и ждём заданное время.
void Spider::safeTimeWrite(int servoId, int percent, int afterDelay)
{
    servos[servoId].write(percent);
    spiderDelay(afterDelay);
}

void Spider::upLeg()
{
    servos[0].write(0);
    spiderDelay(1000);
    servos[3].write(15);
    servos[4].write(80);
    servos[5].write(70);
}

// Вместо busy-wait на millis() - delay(): отдаёт время планировщику FreeRTOS (WiFi/BLE-стеку и т.д.)
void Spider::spiderDelay(int timing)
{
    if (timing > 0)
        delay(timing);
}

void Spider::defaultPosition()
{
    for (int i = 0; i < 4; i += 3) {
        servos[i].write(50);
        servos[i + 1].write(70);
        servos[i + 2].write(0);
    }
    spiderDelay(500);
    for (int i = 6; i < 12; i += 3) {
        servos[i].write(50);
        servos[i + 1].write(70);
        servos[i + 2].write(0);
    }
}

void Spider::startPosition()
{
    for (int i = 0; i < 12; i += 3) {
        servos[i].write(0);
        servos[i + 1].write(50);
        servos[i + 2].write(50);
    }
}

void Spider::standUp()
{
    for (int i = 1; i < 5; i += 3) {
        servos[i + 6].write(100);
        servos[i + 1].write(0);
        servos[i].write(100);
        servos[i + 1 + 6].write(0);
    }
    spiderDelay(2000);

    for (int i = 1; i < 5; i += 3) {
        servos[i].write(70);
        servos[i + 6].write(70);
    }
    spiderDelay(1000);

    defaultPosition();
}
