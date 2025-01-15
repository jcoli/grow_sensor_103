/**
Version: 0a
Tecnocoli - 08/2024
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br    
STM32F103C8 - Grow Sensors
**/

#ifndef __CAN_CONTROL_H__
#define __CAN_CONTROL_H__


void can_begin();
void can_read();
void can_write(uint64_t canTXId, int frame_type, int data_lenght, byte send_data[8]);
void sendValuesFloat(int destId,  int service,int pid, float sensorValue);
void sendValuesBoolean(int destId,  int service,int pid, boolean sensorValue);
void sendValues(int destId, int pid, int service, float sensorValue);





#endif