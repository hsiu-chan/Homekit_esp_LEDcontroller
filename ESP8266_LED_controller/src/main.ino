/*
 * Example05_WS2812_Neopixel.ino
 *
 *  Created on: 2020-10-01
 *      Author: Juergen Fink
 *	Thanks to all the other helpful people commenting here.
 *
 * This example allows to change brightness and color of a connected neopixel strip/matrix
 *
 * You should:
 * 1. read and use the Example01_TemperatureSensor with detailed comments
 *    to know the basic concept and usage of this library before other examples。
 * 2. erase the full flash or call homekit_storage_reset() in setup()
 *    to remove the previous HomeKit pairing storage and
 *    enable the pairing with the new accessory of this new HomeKit example.
 */


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"
#include "LEDitems.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

#define LED1 D5
#define LED2 D6 
#define LED3 D7 
#define LED4 15




void setup() {
	Serial.begin(74880);
	wifi_connect(); // in wifi_info.h
  	delay(1000);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);

	my_homekit_setup();
}


int i = 0;

void loop() {
	my_homekit_loop();
	delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c

extern "C" homekit_server_config_t accessory_config;
extern "C" homekit_characteristic_t cha_on1;
extern "C" homekit_characteristic_t cha_bright1;

extern "C" homekit_characteristic_t cha_on2;
extern "C" homekit_characteristic_t cha_bright2;

extern "C" homekit_characteristic_t cha_on3;
extern "C" homekit_characteristic_t cha_bright3;

extern "C" homekit_characteristic_t cha_on4;
extern "C" homekit_characteristic_t cha_bright4;

static uint32_t next_heap_millis = 0;





void my_homekit_setup() {

	cha_on1.setter = set_on1;
	cha_bright1.setter = set_bright1;

	cha_on2.setter = set_on2;
	cha_bright2.setter = set_bright2;

	cha_on3.setter = set_on3;
	cha_bright3.setter = set_bright3;

	cha_on4.setter = set_on4;
	cha_bright4.setter = set_bright4;
	

	arduino_homekit_setup(&accessory_config);

}

void my_homekit_loop() {
	arduino_homekit_loop();
	const uint32_t t = millis();
	if (t > next_heap_millis) {
		// show heap info every 5 seconds
		next_heap_millis = t + 5 * 1000;
		LOG_D("Free heap: %d, HomeKit clients: %d",
				ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

	}
}
