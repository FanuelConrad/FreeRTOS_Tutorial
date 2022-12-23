#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED 6
#define YELLOW 7
#define BLUE 8

SemaphoreHandle_t xCountingSemaphore;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);

  Serial.begin(9600);
  xCountingSemaphore = xSemaphoreCreateCounting(1, 0);
  xTaskCreate(redLedControllerTask, "RED Task", 100, NULL, 1, NULL);
  xTaskCreate(blueLedControllerTask, "BLUE Task", 100, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "YELLOW Task", 100, NULL, 1, NULL);

  xSemaphoreGive(xCountingSemaphore);
}

void redLedControllerTask(void *pvParameters) {
  while (1) {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(RED, digitalRead(RED) ^ 1);
    Serial.println("RED Task");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}

void blueLedControllerTask(void *pvParameters) {
  while (1) {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
    Serial.println("BLUE Task");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}
void yellowLedControllerTask(void *pvParameters) {
  while (1) {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
    Serial.println("YELLOW Task");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}
void loop() {}