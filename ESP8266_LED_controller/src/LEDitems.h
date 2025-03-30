#ifndef LEDITEMS_H
#define LEDITEMS_H

#include <Arduino.h>
#include <arduino_homekit_server.h>

// LED 結構定義
struct LEDitem {
    bool ison = false;
    float bright = 100;
    uint8_t pin;

    LEDitem(uint8_t pin) : pin(pin) {}
};

// LED 陣列定義

// LED 相關函式宣告
void updateColor1();
void updateColor2();
void updateColor3();
void updateColor4();


void set_on1(const homekit_value_t v);
void set_on2(const homekit_value_t v);
void set_on3(const homekit_value_t v);
void set_on4(const homekit_value_t v);

void set_bright1(const homekit_value_t v);
void set_bright2(const homekit_value_t v);
void set_bright3(const homekit_value_t v);
void set_bright4(const homekit_value_t v);



#endif // LEDITEMS_H
