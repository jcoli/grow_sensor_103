/**
Version: 0a
Tecnocoli - 08/2024
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br    
STM32F103C8 - Grow Sensors
**/

#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

#include "defines.h"
#include "io_defines.h"

void can_begin(); 
void can_read();
void can_write(uint64_t canTXId, int frame_type, int data_lenght, byte send_data[8]);
void sendValuesFloat(int destId,  int service,int pid, float sensorValue);
void sendValuesBoolean(int destId,  int service,int pid, boolean sensorValue);
void sendValues(int destId, int pid, int service, float sensorValue);


 
SPIClass SPI_2(CAN0_MOSI, CAN0_MISO, CAN0_SCK);
MCP_CAN CAN0(&SPI_2, CAN0_CS);


long unsigned int rxId;
unsigned char len = 0; 
unsigned char rxBuf[8];
char msgString[128];   
byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  


void can_begin(){
     
    byte sndStat = CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ);
    if(sndStat == CAN_OK){
      Serial.println("MCP2515 Initialized Successfully!"); 
      Serial.println(sndStat);
      digitalWrite(LED_PIN, HIGH);
    }else{ 
      // Serial.println("Error Initializing MCP2515...");
      // Serial.println(sndStat);
      digitalWrite(LED_PIN, LOW);
    }  
    CAN0.setMode(MCP_NORMAL); 

    // pinMode(CAN0_INT, INPUT_PULLUP); 

    pinMode(CAN0_INT, INPUT_PULLUP); 
    pinMode(LED_PIN, OUTPUT); 

    attachInterrupt(digitalPinToInterrupt(CAN0_INT), can_read, LOW);

}

void can_read(){
    uint16_t can_id = CANID;
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    if (rxId == CANID){
        if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
          sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
        else
          sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
      
        // Serial.print(msgString);
      
        if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
          sprintf(msgString, " REMOTE REQUEST FRAME");
          // Serial.print(msgString);
        } else {
          // for(byte i = 0; i<len; i++){
          //   sprintf(msgString, " 0x%.2X", rxBuf[i]);
          //   Serial.print(msgString);
          // }
        }
        // Serial.println("");    
        // Serial.println("-------6-------");
    }

}

void can_write(uint64_t canTXId, int frame_type, int data_lenght, byte send_data[8]){


    // unsigned char stmp[8] = {0xC0, 0x29, 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00};
    // byte sndStat = CAN0.sendMsgBuf(0x155, 0, 8, stmp);
    byte sndStat = CAN0.sendMsgBuf(canTXId, frame_type, data_lenght, send_data);
    if(sndStat == CAN_OK){
      // Serial.println("Message Sent Successfully!");
    } else {
        Serial.println("Error Sending Message...");
        Serial.println(sndStat);
        
        if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_8MHZ) == CAN_OK){
          // Serial.println("MCP2515 Initialized Successfully!");

      }else{ 
        Serial.println("Error Initializing MCP2515...");
      } 
      CAN0.setMode(MCP_NORMAL);  
    }

}

void sendValuesFloat(int destId,  int service,int pid, float sensorValue) {
    // Serial.println("sendValuesFloat");
    uint16_t temp_can;
    temp_can = sensorValue;
    uint8_t lowByteCan;
    uint8_t highByteCan;
    lowByteCan = lowByte(temp_can);
    highByteCan = highByte(temp_can);
    unsigned char stmp[8] = {service, pid, lowByteCan, highByteCan, 0x00, 0x00, 0x00, 0x00};
    can_write(destId, 0, 8, stmp);
}

void sendValuesBoolean(int destId,  int service,int pid, boolean sensorValue) {
    // Serial.println("sendValuesBoolean");
    if (sensorValue){
      unsigned char stmp[8] = {service, pid, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
      // Serial.println("send 1");
      can_write(destId, 0, 8, stmp);  
    }else{
      unsigned char stmp[8] = {service, pid, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
      // Serial.println("send 0");
      can_write(destId, 0, 8, stmp);
    }
}

void sendValues(int destId,  int service,int pid, float sensorValue) {
    uint16_t temp_can;
    // if (sensorValue*100<65535){
      // temp_can = sensorValue*100;
    // }else{
      temp_can = sensorValue;
    // }
    uint8_t lowByteCan;
    uint8_t highByteCan;
    lowByteCan = lowByte(temp_can);
    highByteCan = highByte(temp_can);

    unsigned char stmp[8] = {service, pid, lowByteCan, highByteCan, 0x00, 0x00, 0x00, 0x00};
    can_write(destId, 0, 8, stmp);
    // Serial.print("msg: ");
    // Serial.print(service, HEX);
    // Serial.print(", ");
    // Serial.print(pid, HEX);
    // Serial.print(", ");
    // Serial.print(lowByteCan, HEX);
    // Serial.print(", ");
    // Serial.println(highByteCan, HEX);

}


