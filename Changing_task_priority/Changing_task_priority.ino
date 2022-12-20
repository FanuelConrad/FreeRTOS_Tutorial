#include <Arduino_FreeRTOS.h>

#define RED 6
#define BLUE 7
#define YELLOW 8

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler BLUELEDProfiler;
TaskProfiler YELLOWLEDProfiler;

TaskHandle_t blue_Handle, red_Handle, yellow_Handle;

void setup() {
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask, "RED LED", 100, NULL, 1, &red_Handle);
  xTaskCreate(blueLedControllerTask, "BLUE LED", 100, NULL, 1, &blue_Handle);
  xTaskCreate(yellowLedControllerTask, "YELLOW LED", 100, NULL, 1, &yellow_Handle);
}

void redLedControllerTask(void *pvParameters) {
  pinMode(RED, OUTPUT);
  while (1) {
    digitalWrite(RED, digitalRead(RED) ^ 1);
    delay(50);
  }
}

void blueLedControllerTask(void *pvParameters) {
  pinMode(BLUE, OUTPUT);
  while (1) {
    digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
    delay(50);
  }
}

void yellowLedControllerTask(void *pvParameters) {
  pinMode(YELLOW, OUTPUT);
  while (1) {
    digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
    vTaskPrioritySet(red_Handle, 2);
    delay(50);
  }
}

void loop() {}