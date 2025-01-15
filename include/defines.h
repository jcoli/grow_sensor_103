/**
Version: 0a
Tecnocoli - 08/2024
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br    
STM32F103C8 - Grow Sensors
**/

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define CALX_TEMP 25
#define VTEMP     1430
#define AVG_SLOPE 4300
#define VREFINT   1200

#define TIME_OUT 8000000
#define TIMER_SLEEP 600000
#define TIMER_ANALOG 60000
#define TIMER_WATCHDOG 60000
#define TIMER_FIRST 250000
#define TIMER_LED 500

#define LL_ADC_RESOLUTION LL_ADC_RESOLUTION_12B
#define ADC_RANGE 4096

static const char version[] = "1.0a";
static const char develop[] =  "jcoli-Tecnocoli";
static const char email_develop[] = "jcoli@tecnocoli.com.br";
static const char processor[] = "STM32F103C8";

#define CANID 0x31F

#define CANID_MASTER_MASTER    0x310
#define CANID_MASTER_SENSOR    0x31F
#define CANID_MASTER_LIGHTS    0X32A
#define CANID_MASTER_OUTPUT    0X33A
#define CANID_MASTER_IRRIG     0X34A
#define CANID_MASTER_WIFI_BT   0X35A
#define CANID_MASTER_WIFI      0X36A
#define CANID_MASTER_BT        0X37A



#endif