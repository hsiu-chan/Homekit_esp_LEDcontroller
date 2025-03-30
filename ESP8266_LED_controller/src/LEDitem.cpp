#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "LEDitems.h"

#define LED1 D5
#define LED2 D6 
#define LED3 D7 
#define LED4 15

extern "C" homekit_server_config_t accessory_config;
extern "C" homekit_characteristic_t cha_on1;
extern "C" homekit_characteristic_t cha_bright1;

extern "C" homekit_characteristic_t cha_on2;
extern "C" homekit_characteristic_t cha_bright2;

extern "C" homekit_characteristic_t cha_on3;
extern "C" homekit_characteristic_t cha_bright3;

extern "C" homekit_characteristic_t cha_on4;
extern "C" homekit_characteristic_t cha_bright4;






LEDitem leds[]={
	LEDitem(LED1),
	LEDitem(LED2),
	LEDitem(LED3),
	LEDitem(LED4),
};


// 更新 LED 狀態
void updateColor1() {
	INFO("NOW:[%u, %u, %u, %u]", leds[1].bright, leds[2].bright, leds[3].bright, leds[4].bright)
	if (leds[0].ison) {
		int b = map(leds[0].bright, 0, 100, 0, 255);
		Serial.print("Brightness: ");
		Serial.println(b);
		analogWrite(LED1, b);
	} else {
		analogWrite(LED1, 0);
	}
}
void updateColor2() {
	INFO("NOW:[%u, %u, %u, %u]", leds[1].bright, leds[2].bright, leds[3].bright, leds[4].bright)

	if (leds[1].ison) {
		int b = map(leds[1].bright, 0, 100, 0, 255);
		Serial.print("Brightness: ");
		Serial.println(b);
		analogWrite(LED2, b);
	} else {
		Serial.println("ison == false");
		analogWrite(LED2, 0);
	}
}
void updateColor3() {
	INFO("NOW:[%u, %u, %u, %u]", leds[1].bright, leds[2].bright, leds[3].bright, leds[4].bright)

	if (leds[2].ison) {
		int b = map(leds[2].bright, 0, 100, 0, 255);
		Serial.print("Brightness: ");
		Serial.println(b);
		analogWrite(LED3, b);
	} else {
		Serial.println("ison == false");
		analogWrite(LED3, 0);
	}
}
void updateColor4() {
	INFO("NOW:[%u, %u, %u, %u]", leds[1].bright, leds[2].bright, leds[3].bright, leds[4].bright)

	if (leds[3].ison) {
		int b = map(leds[3].bright, 0, 100, 0, 255);
		Serial.print("Brightness: ");
		Serial.println(b);
		analogWrite(LED4, b);
	} else {
		Serial.println("ison == false");
		analogWrite(LED4, 0);
	}
}

// 設定開關
void set_on1(const homekit_value_t v) {
	leds[0].ison = v.bool_value;
	cha_on1.value.bool_value = v.bool_value; // 同步 HomeKit 狀態
	updateColor1();
}
void set_on2(const homekit_value_t v) {
	leds[1].ison = v.bool_value;
	cha_on2.value.bool_value = v.bool_value; // 同步 HomeKit 狀態
	updateColor2();
}
void set_on3(const homekit_value_t v) {
	leds[2].ison = v.bool_value;
	cha_on3.value.bool_value = v.bool_value; // 同步 HomeKit 狀態
	updateColor3();
}
void set_on4(const homekit_value_t v) {
	leds[3].ison = v.bool_value;
	cha_on4.value.bool_value = v.bool_value; // 同步 HomeKit 狀態
	updateColor4();
}

// 設定亮度
void set_bright1(const homekit_value_t v) {
	Serial.println("set_bright");
	leds[0].bright = v.int_value;
	cha_bright1.value.int_value = v.int_value; // 同步 HomeKit 亮度
	updateColor1();
}
void set_bright2(const homekit_value_t v) {
	Serial.println("set_bright");
	leds[1].bright = v.int_value;
	cha_bright2.value.int_value = v.int_value; // 同步 HomeKit 亮度
	updateColor2();
}
void set_bright3(const homekit_value_t v) {
	Serial.println("set_bright");
	leds[2].bright = v.int_value;
	cha_bright3.value.int_value = v.int_value; // 同步 HomeKit 亮度
	updateColor3();
}
void set_bright4(const homekit_value_t v) {
	Serial.println("set_bright");
	leds[3].bright = v.int_value;
	cha_bright4.value.int_value = v.int_value; // 同步 HomeKit 亮度
	updateColor4();
}
