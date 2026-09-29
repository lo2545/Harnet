#ifndef SPIDER_H
#define SPIDER_H

#include "servo_wrap.h"
#include <Arduino.h>

class Spider {
public:
    void attachServos(ServoWrap* servs);
    void safeTimeStepForward();
    void stepForward();
    // Значение по умолчанию задаётся ТОЛЬКО в объявлении (в оригинале оно дублировалось в .cpp - ошибка компиляции)
    void safeTimeWrite(int servoId, int percent, int afterDelay = 1000);
    void upLeg();
    void spiderDelay(int timing);
    void defaultPosition();
    void startPosition();
    void standUp();

    ServoWrap* servos;
};

#endif // SPIDER_H
