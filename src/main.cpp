/**
Version: 0a
Tecnocoli - 08/2024
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br    
STM32F103C8 - Grow Sensors
**/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <IWatchdog.h>

#include "input_analog_control.h"
#include "defines.h"
#include "io_defines.h"
#include "variables.h" 
#include "can_control.h" 

void setup() {
    Serial.begin(115200); 
    delay(30000);
    analogReadResolution(12);
    Serial.println("Begin"); 
    can_begin();
    Serial.println("Begin 2"); 
    analog_input_begin();
    Serial.println("Begin 3"); 
    IWatchdog.begin(10000000);
    loopDelay_watchdog  = millis();
 
}

void loop() {
    if (millis() - loopDelay > TIMER_ANALOG){
        // Serial.println("Loop"); 
        loopDelay = millis();
        read_analog();
        printValues();
        Serial.println("Loop"); 
    }

    if (millis() - loopDelay_watchdog  > TIMER_LED){ 
     loopDelay_watchdog  = millis();
     digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
     IWatchdog.reload();
     if (digitalRead(CAN0_INT) == LOW){
        can_read();
     }
    } 
}

