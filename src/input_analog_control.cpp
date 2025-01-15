/**
Version: 0a
Tecnocoli - 08/2024
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br    
STM32F103C8 - Grow Sensors
**/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "ScioSense_ENS160.h" 
// #include <dhtnew.h>

#include "io_defines.h"
#include "defines.h" 
#include "can_control.h" 

Adafruit_BME280 bme_1;  
Adafruit_BME280 bme_2; 
ScioSense_ENS160      ens160_1(ENS160_I2CADDR_0);
ScioSense_ENS160      ens160_2(ENS160_I2CADDR_1);
// DHTNEW mySensor(PA0);

void analog_input_begin();
void read_analog();
void printValues();

extern float ens_1_eco2;
extern float ens_2_eco2;
extern float aht_1_hum;
extern float aht_1_temp;
extern float aht_2_hum;
extern float aht_2_temp;
extern float bme_1_temp;
extern float bme_1_hum;
extern float bme_2_temp;
extern float bme_2_hum;
extern float soil_1_hum;
extern float soil_2_hum;
extern float soil_3_hum;
extern float soil_4_hum;
extern float light_1_int;

extern bool bme_1_status;
extern bool bme_2_status;
extern bool ens1_status;
extern bool ens2_status;

extern bool water_irrig_1_level;
extern bool water_hum_1_level;

void analog_input_begin(){
    
    pinMode(LV_W_IRR, INPUT_PULLDOWN);
    pinMode(LV_W_HUM, INPUT_PULLDOWN);


    bme_1_status = bme_1.begin(0x76, &Wire);  
    bme_2_status = bme_2.begin(0x77, &Wire);  

   delay(1000);

    if (!bme_1_status) {
        Serial.println("Could not find a valid BME280 1 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme_1.sensorID(),16);
    }else{
        Serial.println("BME280 1 sensor");
        Serial.print("SensorID was: 0x"); Serial.println(bme_1.sensorID(),16);
        
    }
    if (!bme_2_status) {
        Serial.println("Could not find a valid BME280 2 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme_2.sensorID(),16);
    }else{
        Serial.println("BME280 2 sensor");
        Serial.print("SensorID was: 0x"); Serial.println(bme_2.sensorID(),16);

    }

    delay(1000);

    ens160_1.begin();
    
    if (!ens160_1.available()) {
        Serial.println("Could not find a valid ENS160 1 sensor, check wiring, address, sensor ID!");
        ens1_status = false;
        
    }else{
        ens1_status = true;
        Serial.println("ENS160 1");
        Serial.print("\tRev: "); Serial.print(ens160_1.getMajorRev());
        Serial.print("."); Serial.print(ens160_1.getMinorRev());
        Serial.print("."); Serial.println(ens160_1.getBuild());
    
        Serial.print("\tStandard mode ");
        Serial.println(ens160_1.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
        ens160_1.measure(true);
        ens160_1.measureRaw(true);
    }

    ens160_2.begin();

    if (!ens160_2.available()) {
        Serial.println("Could not find a valid ENS160 2 sensor, check wiring, address, sensor ID!");
        ens2_status = false;
    }else{
        ens2_status = true;
        Serial.println("ENS160 2");
        Serial.print("\tRev: "); Serial.print(ens160_2.getMajorRev());
        Serial.print("."); Serial.print(ens160_2.getMinorRev());
        Serial.print("."); Serial.println(ens160_2.getBuild());
    
        Serial.print("\tStandard mode ");
        Serial.println(ens160_2.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
        ens160_2.measure(true);
        ens160_2.measureRaw(true);
    }

    delay(1000);

}

void read_analog(){
    // Serial.println("read analog sensors");
    // Serial.println("BME");
    if (bme_1_status){
        // Serial.println("BME 1");
        bme_1_temp = bme_1.readTemperature();
        sendValuesFloat(0x310, 0x02, 0x00, bme_1_temp*100);
        // delay(100);
        bme_1_hum = bme_1.readHumidity();
        sendValuesFloat(0x310, 0x02, 0x02, bme_1_hum*100);
        // delay(100);
    }
    
    if (bme_2_status){
        // Serial.println("BME 2");
        bme_2_temp = bme_2.readTemperature();
        sendValuesFloat(0x310, 0x02, 0x01, bme_2_temp*100);
        // delay(100);
        bme_2_hum = bme_2.readHumidity();
        sendValuesFloat(0x310, 0x02, 0x03, bme_2_hum*100);
        // delay(100);
    }


    // Serial.println("ENS 1");

    if (ens1_status){
        ens160_1.set_envdata(bme_2_temp, bme_2_hum);
        ens160_1.measure(true);
        ens160_1.measureRaw(true);
        ens_1_eco2 = ens160_1.geteCO2();
        sendValuesFloat(0x310, 0x02, 0x04, ens_1_eco2);
        // delay(100);
    }
   
    if (ens2_status){
        // Serial.println("ENS 2");
        ens160_2.set_envdata(bme_1_temp, bme_1_hum);
        ens160_2.measure(true);
        ens160_2.measureRaw(true);
        ens_2_eco2 = ens160_2.geteCO2();
        sendValuesFloat(0x310, 0x02, 0x05, ens_2_eco2);
        // delay(100);
    }
    
    float soil_hum_temp = 0.00;
    soil_hum_temp=analogRead(SOIL_HUM_1);
    Serial.print("Soul Hum: ");
    Serial.println(soil_hum_temp);
    soil_1_hum = map(soil_hum_temp, 1860, 4095, 100, 0);

    // // delay(100);
    // soil_hum_temp = 0.00;
    // soil_hum_temp=analogRead(SOIL_HUM_2);
    // soil_2_hum = map(soil_hum_temp, 1000, 4095, 100, 0);

    // // delay(100);
    // soil_hum_temp = 0.00;
    // soil_hum_temp=analogRead(SOIL_HUM_3);
    
    // soil_3_hum = map(soil_hum_temp, 1000, 4095, 100, 0);

    // // delay(100);
    // soil_hum_temp = 0.00;
    // soil_hum_temp=analogRead(SOIL_HUM_4);
    // soil_4_hum = map(soil_hum_temp, 1000, 2200, 100, 0);
    
    // delay(100);
    float light_int_temp = 0;
    light_int_temp = analogRead(LUMI_ANA);
    Serial.print("Light Int: ");
    Serial.println(light_int_temp);
    light_1_int = map(light_int_temp, 0, 4095, 100, 0);

    sendValuesFloat(0x310,  0x02, 0x12, soil_1_hum);
    // delay(100);
    sendValuesFloat(0x310,  0x02, 0x11, light_1_int);
    

    water_irrig_1_level = digitalRead(LV_W_IRR);
    water_hum_1_level = digitalRead(LV_W_HUM);
    sendValuesBoolean(0x310, 0x03, 0x06, water_irrig_1_level);  
    // delay(100);
    sendValuesBoolean(0x310, 0x03, 0x07, water_hum_1_level); 
    // delay(100);

}



void printValues() {

    Serial.print("soil humidity: ");
    Serial.println(soil_1_hum);
    Serial.print("light intensity: ");
    Serial.println(light_1_int);

    Serial.print("water level irr: ");
    Serial.println(water_irrig_1_level);
    Serial.print("water level hum: ");
    Serial.println(water_hum_1_level);

    // Serial.println("========");
    
    // uint16_t temp_can;
    // temp_can = bme_2_hum*100;
    // uint8_t lowByteCan;
    // uint8_t highByteCan;
    // lowByteCan = lowByte(temp_can);
    // highByteCan = highByte(temp_can);
    // Serial.println(lowByteCan);
    // Serial.println(highByteCan);
    // uint16_t comb_can = (highByteCan<<8) | (lowByteCan);
    // Serial.println("BME 2 HUM comb can");
    // Serial.println(comb_can);

    // unsigned char stmp[8] = {0x02, 0x01, lowByteCan, highByteCan, 0x00, 0x00, 0x00, 0x00};
    // can_write(0x0100, 0, 8, stmp);

    Serial.print("BME 1 ");
    Serial.print(bme_1_temp);
    Serial.print(", ");
    Serial.println(bme_1_hum);
    Serial.print("BME 2 ");
    Serial.print(bme_2_temp);
    Serial.print(", ");
    Serial.println(bme_2_hum);
    Serial.print("eCO2 1: ");
    Serial.println(ens_1_eco2);
    Serial.print("eCO2 2: ");
    Serial.println(ens_2_eco2);
    
    
    Serial.println("===================");
    
}
