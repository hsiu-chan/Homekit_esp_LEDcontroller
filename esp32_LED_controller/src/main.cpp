#include <Arduino.h>
#include <WiFi.h>
#include <HomeSpan.h>         // HomeSpan sketches always begin by including the HomeSpan library


#include <ArduinoOTA.h>
#include <ESPmDNS.h>


#define PIN_LED 33// LEDC 的 PWM 通道
#define PIN_LED2 25// LEDC 的 PWM 通道
const int pwmChannel = 0;          // LEDC 的 PWM 通道
const int pwmChannel2 = 1;          // LEDC 的 PWM 通道

const int pwmFreq = 5000;          // 頻率 5 kHz
const int pwmResolution = 10;       // 解析度 8 位元（範圍 0~255）




const char pairing_code[] = "20030707";
const char* ssid = "WI-FI_2.4G";
const char* password = "hsiu112358";





// LED
struct LEDBlub : Service::LightBulb {      // Addressable single-wire RGB LED Strand (e.g. NeoPixel)
  Characteristic::On power{0,true};
  Characteristic::Brightness L{100,true};
  int ThisChannel;

  LEDBlub(int Channel):Service::LightBulb()
  {
    L.setRange(0,100,1);// sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    update(); 
    ThisChannel=Channel;

    
  }

  boolean update() override 
  {
    if (power.getNewVal()==0){
      ledcWrite(ThisChannel,0);
      return (true);
    }
    int l=L.getNewVal<float>();
    Serial.printf("LED: %d\n",l);
    ledcWrite(ThisChannel, round(l*1023/100));
    return(true); 
  }


};



void setup() {
  Serial.begin(115200);
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcSetup(pwmChannel2, pwmFreq, pwmResolution);
  ledcAttachPin(PIN_LED, pwmChannel);   // 將通道綁定到 GPIO 25
  ledcAttachPin(PIN_LED2, pwmChannel2);   // 將通道綁定到 GPIO 25





  
  // homespan 初始化

  
  homeSpan.setWifiCredentials(ssid, password);
  homeSpan.setPairingCode(pairing_code);
  homeSpan.begin(Category::Lighting,"LED Controller");



  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();  
  
  SPAN_ACCESSORY("LED1");
    new LEDBlub(pwmChannel);
  
  SPAN_ACCESSORY("LED2");
    new LEDBlub(pwmChannel2);
  
  Serial.printf("setup end");
 

}

void loop() {
  homeSpan.poll();

  delay(10);
  
}
