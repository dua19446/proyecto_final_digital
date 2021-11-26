/*
 * Alejandro Duarte y Jonathan Pu
 * 19446 - 19249
 * -ESTACIONAMIENTO-
 * Descripcion:
 * Se realiza el sistema de control de dos grupos de 4 parqueos cada uno
 * utilizando actuadores para detectar si 'hay' algun carro o no
 * y desplegandolo en un 7seg, con comunicacion UART se envia la informacion
 * a un ESP32 para desplegarlo en un monitor en tiempo real
 */

//*********************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"


int IRSensor1 = PB_0; // connect ir sensor to arduino pin 2
int IRSensor2 = PB_1;
int IRSensor3 = PA_5;
int IRSensor4 = PA_6;

int LED1 = PF_2; // conect Led to arduino pin 13
int LED2 = PF_3;
int LED3 = PF_1;
int LED4 = PA_7;
int LED5 = PB_3;
int LED6 = PD_0;
int LED7 = PD_1;
int LED8 = PD_2;

int P1;
int P2;
int P3;
int P4; 

volatile int state = LOW;

void setup() 
{
  pinMode (IRSensor1, INPUT_PULLUP); // sensor pin INPUT
  pinMode (IRSensor2, INPUT_PULLUP);
  pinMode (IRSensor3, INPUT_PULLUP);
  pinMode (IRSensor4, INPUT_PULLUP);
  pinMode (LED1, OUTPUT); // Led pin OUTPUT
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);
  pinMode (LED4, OUTPUT);
  pinMode (LED5, OUTPUT);
  pinMode (LED6, OUTPUT);
  pinMode (LED7, OUTPUT);
  pinMode (LED8, OUTPUT);

  Serial.begin(115200);
  Serial2.begin(115200);
  Serial2.setTimeout(50);
  delay(100);
}

void loop()
{
  int statusSensor1 = digitalRead (IRSensor1);
  int statusSensor2 = digitalRead (IRSensor2);
  int statusSensor3 = digitalRead (IRSensor3);
  int statusSensor4 = digitalRead (IRSensor4);
  
  
  if (statusSensor1 == LOW)
  {
    digitalWrite(LED1, LOW); // LED LOW
    digitalWrite(LED2, HIGH);
    P1 = 1;
  }
  
  else
  {
    digitalWrite(LED1, HIGH); // LED High
    digitalWrite(LED2, LOW);
    P1 = 0;
  }

  if (statusSensor2 == LOW)
  {
    digitalWrite(LED3, LOW); // LED LOW
    digitalWrite(LED4, HIGH);
    P2 = 1;
  }
  
  else
  {
    digitalWrite(LED3, HIGH); // LED High
    digitalWrite(LED4, LOW);
    P2 = 0;
  }
  if (statusSensor3 == LOW)
  {
    digitalWrite(LED5, LOW); // LED LOW
    digitalWrite(LED6, HIGH);
    P3 = 1;
  }
  
  else
  {
    digitalWrite(LED5, HIGH); // LED High
    digitalWrite(LED6, LOW);
    P3 = 0;
  }
  if (statusSensor4 == LOW)
  {
    digitalWrite(LED7, LOW); // LED LOW
    digitalWrite(LED8, HIGH);
    P4 = 1;
  }
  
  else
  {
    digitalWrite(LED7, HIGH); // LED High
    digitalWrite(LED8, LOW);
    P4 = 0;
  }

// Para mandar que un  espacio esta ocupado
  if (P1 == 1 && P2 == 0 && P3 == 0 && P4 == 0){
    Serial2.write('1');
    Serial.write('1');
  }
  if (P1 == 0 && P2 == 1 && P3 == 0 && P4 == 0){
    Serial2.write('1');
    Serial.write('2');
  }
  if (P1 == 0 && P2 == 0 && P3 == 1 && P4 == 0){
    Serial2.write('1');
    Serial.write('3');
  }
  if (P1 == 0 && P2 == 0 && P3 == 0 && P4 == 1){
    Serial2.write('1');
    Serial.write('4');
   
  }
// Para mandar que dos espacios estan ocupados
  if (P1 == 1 && P2 == 1 && P3 == 0 && P4 == 0){
    Serial2.write('2');
  }
  if (P1 == 1 && P2 == 0 && P3 == 1 && P4 == 0){
    Serial2.write('2');
  }
  if (P1 == 1 && P2 == 0 && P3 == 0 && P4 == 1){
    Serial2.write('2');
  }
  if (P1 == 0 && P2 == 1 && P3 == 1 && P4 == 0){
    Serial2.write('2');
  }
  if (P1 == 0 && P2 == 1 && P3 == 0 && P4 == 1){
    Serial2.write('2');
  }
  if (P1 == 0 && P2 == 0 && P3 == 1 && P4 == 1){
    Serial2.write('2');
  }
// Para mandar que tres espacios estan ocupados
  if (P1 == 1 && P2 == 1 && P3 == 1 && P4 == 0){
    Serial2.write('3');
  }
  if (P1 == 1 && P2 == 1 && P3 == 0 && P4 == 1){
    Serial2.write('3');
  }
  if (P1 == 0 && P2 == 1 && P3 == 1 && P4 == 1){
    Serial2.write('3');
  }
  if (P1 == 1 && P2 == 0 && P3 == 1 && P4 == 1){
    Serial2.write('3');
  }
//Para mandar que cuatro espacios estan ocupados 
if (P1 == 1 && P2 == 1 && P3 == 1 && P4 == 1){
    Serial2.write('4');
  }
//Para mandar que ningun espacio esta ocupado
 if (P1 == 0 && P2 == 0 && P3 == 0 && P4 == 0){
    Serial2.write('0');
  }
}
