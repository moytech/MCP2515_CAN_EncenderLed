/*

Led con push button

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa recibe una señal digital por medio de un push button.
Se envía y se recibe por el protocolo CAN bus con ayuda del módulo MCP2515 
para encender un led.

Autor: Moytech
github: https://github.com/moytech
Programa: Led con push button
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int pushRec;
int led=2;

struct can_frame datareceive;
MCP2515 mcp2515(CS);

void setup() 
{
  SPI.begin();                                    //iniciar SPI
  mcp2515.reset();                                //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);      //configuración CAN bus
  mcp2515.setNormalMode();                        //modo normal
  pinMode(led, OUTPUT);                           //salida led
  digitalWrite(led, 0);                           //led en 0
}

void loop() 
{
  if(mcp2515.readMessage(&datareceive)== MCP2515::ERROR_OK)
  {
    pushRec= datareceive.data[0];                 //byte [0]
    if(pushRec== 1)                               //si se recibe 1
    {
      digitalWrite(led, 1);                       //led en 1
      delay(5000);                                //esperar 5 seg.
      digitalWrite(led, 0);                       //led en 0
    }
    else
      digitalWrite(led, 0);                       //led en 0
  }
}
