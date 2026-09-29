// Harnet: прошивка робота-паука на ESP32 (порт arkadiy-core, Arduino -> ESP32)
// Библиотека: ESP32Servo (Library Manager -> "ESP32Servo" by Kevin Harrington, John K. Bennett)

#include "src/servo_wrap.h"
#include "src/spider.h"

#define SERVO_COUNT 12

ServoWrap servos[SERVO_COUNT];

// Безопасные GPIO для ESP32 DevKit (без strapping-пинов 0/2/5/12/15,
// без флеш-пинов 6-11 и без input-only 34-39).
// Индекс сервы -> GPIO. Старые пины Arduino: 9,10,12,8,11,13,7,5,3,6,4,2
const uint8_t ports[SERVO_COUNT] = { 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27 };

Spider spider;

String message;

void setup()
{
    Serial.begin(115200); // было 9600; ESP32 спокойно тянет больше (поправь монитор порта!)

    // Таймеры для LEDC (ESP32Servo)
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    // pin, угол при 0%, угол при 100%  (калибровка - без изменений)
    servos[0].attach(ports[0], 0, 100);
    servos[1].attach(ports[1], 0, 85);
    servos[2].attach(ports[2], 175, 0);
    servos[3].attach(ports[3], 180, 80);
    servos[4].attach(ports[4], 165, 80);
    servos[5].attach(ports[5], 0, 180);
    servos[6].attach(ports[6], 0, 100);
    servos[7].attach(ports[7], 0, 100);
    servos[8].attach(ports[8], 172, 0);
    servos[9].attach(ports[9], 180, 80);
    servos[10].attach(ports[10], 180, 80);
    servos[11].attach(ports[11], 20, 180);

    spider.attachServos(servos);
    spider.defaultPosition();
}

void handleCommand(const String& cmd)
{
    if (cmd == "sp") {
        Serial.println("Start position");
        spider.startPosition();
    } else if (cmd == "su") {
        Serial.println("Stand up");
        spider.standUp();
    } else if (cmd == "ruka") {
        Serial.println("Hi bro :)");
        spider.upLeg();
    } else if (cmd == "go") {
        Serial.println("GO GO GO!!!");
        spider.defaultPosition();
        spider.safeTimeStepForward();
    } else if (cmd == "def") {
        Serial.println("Default position");
        spider.defaultPosition();
    } else if (cmd.length() > 0) {
        Serial.println("Unknown command");
    }
}

void loop()
{
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\r') {
            continue; // терминалы с CRLF
        }
        if (c == '\n') {
            message.trim();
            handleCommand(message);
            message = "";
        } else if (message.length() < 32) {
            message += c;
        }
    }
}
