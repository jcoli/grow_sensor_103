/**
Version: 0a
Tecnocoli - 08/2024
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br    
STM32F103C8 - Grow Sensors
**/

#ifndef __VARIABLES_H__
#define __VARIABLES_H__
#include <Arduino.h>

unsigned long loopDelay = millis();
unsigned long loopDelay_analog = millis();
unsigned long loopDelay_input = millis();
unsigned long loopDelay_watchdog = millis();
unsigned long lastAvailabilityToggleAt = millis();


String line = "";
String line1 = "";
String line2 = "";
bool stringComplete = false;
bool string1Complete = false;
bool string2Complete = false;

float VRef = 0.00;
float intTemp = 0.00;

float ens_1_eco2 = 0.00;
float ens_2_eco2 = 0.00;
float aht_1_hum = 0.00;
float aht_1_temp = 0.00;
float aht_2_hum = 0.00;
float aht_2_temp = 0.00;
float bme_1_temp = 0.00;
float bme_1_hum = 0.00;
float bme_2_temp = 0.00;
float bme_2_hum = 0.00;
float soil_1_hum = 0.00;
float soil_2_hum = 0.00;
float soil_3_hum = 0.00;
float soil_4_hum = 0.00;
float light_1_int = 0.00;

bool bme_1_status = false;
bool bme_2_status = false;
bool ens1_status = false;
bool ens2_status = false;

bool water_irrig_1_level = false;
bool water_hum_1_level = false;



#endif