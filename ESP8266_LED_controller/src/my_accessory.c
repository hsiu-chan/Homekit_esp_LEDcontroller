/*
 * my_accessory.c
 * Define the accessory in C language using the Macro in characteristics.h
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 */

 #include <homekit/homekit.h>
 #include <homekit/characteristics.h>
 
 void accessory_identify(homekit_value_t _value) {
     printf("accessory identify\n");
 }
 
 homekit_characteristic_t cha_on1 = HOMEKIT_CHARACTERISTIC_(ON, false);
 homekit_characteristic_t cha_name1 = HOMEKIT_CHARACTERISTIC_(NAME, "LED1");
 homekit_characteristic_t cha_bright1 = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 50);
 
 homekit_characteristic_t cha_on2 = HOMEKIT_CHARACTERISTIC_(ON, false);
 homekit_characteristic_t cha_name2 = HOMEKIT_CHARACTERISTIC_(NAME, "LED2");
 homekit_characteristic_t cha_bright2 = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 50);
 
 homekit_characteristic_t cha_on3 = HOMEKIT_CHARACTERISTIC_(ON, false);
 homekit_characteristic_t cha_name3 = HOMEKIT_CHARACTERISTIC_(NAME, "LED3");
 homekit_characteristic_t cha_bright3 = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 50);
 
 homekit_characteristic_t cha_on4 = HOMEKIT_CHARACTERISTIC_(ON, false);
 homekit_characteristic_t cha_name4 = HOMEKIT_CHARACTERISTIC_(NAME, "LED4");
 homekit_characteristic_t cha_bright4 = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 50);
 
 
 homekit_accessory_t *accessories[] = {
     HOMEKIT_ACCESSORY(
         .id=1, 
         .category=homekit_accessory_category_bridge, //服務類型
         .services=(homekit_service_t*[]) {
             //ACCESSORY
             HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
                 HOMEKIT_CHARACTERISTIC(NAME, "ESP8266 LED controller"),
                 HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arduino HomeKit"),
                 HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
                 HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266/ESP32"),
                 HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
                 HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
                 NULL
             }),
             HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
                &cha_on1,
                &cha_name1,
                &cha_bright1,
                NULL
            }),
             HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
                 &cha_on2,
                 &cha_name2,
                 &cha_bright2,
                 NULL
             }),
             HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
                 &cha_on3,
                 &cha_name3,
                 &cha_bright3,
                 NULL
             }),
             HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
                 &cha_on4,
                 &cha_name4,
                 &cha_bright4,
                 NULL
             }),
             NULL
     }),
     //LED
     
 
     /*HOMEKIT_ACCESSORY(
         .id=2, 
         .category=homekit_accessory_category_lightbulb, 
         .services=(homekit_service_t*[]) {
             HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
                 HOMEKIT_CHARACTERISTIC(NAME, "LED 1"),
                 HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
                 NULL
             }),
             HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
                 &cha_on,
                 &cha_name,
                 &cha_bright,
                 NULL
             }),
             NULL
     }),*/
 
     NULL
 };
 

 homekit_server_config_t accessory_config = {
    .accessories = accessories,
    .password = "111-11-111"
};
