/*

Push Button

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa envía una señal digital por medio de un push button.
Se envía por el protocolo CAN bus con ayuda del módulo MCP2515 y otro 
módulo MCP2515 la recibe para encender un led.

Autor: Moytech
github: https://github.com/moytech
Programa: Push Button
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int push= 2;

struct can_frame datasend;
MCP2515 mcp2515(CS);

void setup() 
{
  SPI.begin();                                          //iniciar SPI
  mcp2515.reset();                                      //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);            //configuración CAN bus
  mcp2515.setNormalMode();                              //modo normal
  pinMode(push, INPUT_PULLUP);                          //botón pullup                 
}

void loop() 
{
  while(digitalRead(push)== 1);                         //leer botón si push = 1
  while(digitalRead(push)== 0);                         //leer botón si push = 0
  datasend.can_id= 0x11;                                //CAN id
  datasend.can_dlc= 4;                                  //4 bytes
  datasend.data[0]= 1;                                  //Enviar 1
  datasend.data[1]= 0x00;
  datasend.data[2]= 0x00;
  datasend.data[3]= 0x00;

  mcp2515.sendMessage(&datasend);                       //enviar datos
  delay(10);                                            //esperar
}


