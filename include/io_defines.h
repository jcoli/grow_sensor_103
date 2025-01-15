/**
Version: 0a
Tecnocoli - 08/2024
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br    
STM32F103C8 - Grow Sensors
**/

#ifndef __IO_DEFINES_H__
#define __IO_DEFINES_H__

//I2C
#define SDA1        PB7
#define SCL1        PB6

//MCP2515
#define CAN0_CS     PA9 
#define CAN0_INT    PB1
#define CAN0_SCK    PB13
#define CAN0_MISO   PB14
#define CAN0_MOSI   PB15

#define LED_PIN     PC13

#define LUMI_ANA    PA0//ana 
#define SOIL_HUM_1  PA1//ana
#define SOIL_HUM_2  PA2//ana
#define SOIL_HUM_3  PA3//ana
#define SOIL_HUM_4  PA4//ana

#define LV_W_IRR    PC14//dig
#define LV_W_HUM    PC15//dig


#endif