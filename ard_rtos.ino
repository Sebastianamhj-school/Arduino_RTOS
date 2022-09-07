#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#define  LEDGREEN  3
#define LEDRED  2
SemaphoreHandle_t xBinarySemaphore;
void setup()
{
  Serial.begin(9600);
  pinMode(LEDGREEN ,OUTPUT);
  pinMode(LEDRED, OUTPUT);
  xBinarySemaphore = xSemaphoreCreateBinary();
  xCountingSemaphore = xSemaphoreCreateCounting(3, 0);
  xTaskCreate(LedOnTask, "LedON",100,NULL,1,NULL);
  xTaskCreate(LedoffTask, "LedOFF", 100,NULL,1,NULL);
  xSemaphoreGive(xBinarySemaphore, xCountingSemaphore);
}

void loop(){}
void LedOnTask(void *pvParameters)
{
  while(1)
  {
   xSemaphoreTake(xBinarySemaphore, xCountingSemaphore, portMAX_DELAY);
   Serial.println("Inside LedOnTask");
   digitalWrite(LEDGREEN,HIGH);
   vTaskDelay(100);
   digitalWrite(LEDGREEN, LOW);
   xSemaphoreGive(xBinarySemaphore, xCountingSemaphore);
   vTaskDelay(1);
  }
}
void LedoffTask(void *pvParameters)
{
  while(1)
  {
    xSemaphoreTake(xBinarySemaphore, xCountingSemaphore, portMAX_DELAY);
    Serial.println("Inside LedffTask");
    digitalWrite(LEDRED,HIGH);
    vTaskDelay(100);
    digitalWrite(LEDRED, LOW);
    xSemaphoreGive(xBinarySemaphore, xCountingSemaphore);
    vTaskDelay(1);
  }
}
