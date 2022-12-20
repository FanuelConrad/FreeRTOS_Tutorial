#include <Arduino_FreeRTOS.h>

#define RED 6
#define BLUE 7
#define YELLOW 8

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler BlueLEDProfiler;
TaskProfiler YellowLEDProfiler;

TaskHandle_t blue_Handle, red_Handle, yellow_Handle;

int yellowTaskPrio;

void setup() {
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask, "RED LED Task", 100, NULL, 1, NULL);
  xTaskCreate(blueLedControllerTask, "BLUE LED Task", 100, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "YELLOW LED Task", 100, NULL, 1, NULL);
}

void redLedControllerTask(void *pvParameters) {
  while (1) {
//RedLEDProfiler++;
//Serial.print("RED Run Time : ");
//Serial.println(RedLEDProfiler);
//delay(300);
}
}

void blueLedControllerTask(void *pvParameters) {
  while (1) {
//BlueLEDProfiler++;
//Serial.print("BLUE Run Time : ");
//Serial.println(BlueLEDProfiler);
//delay(300);
  }
}

void yellowLedControllerTask(void *pvParameters) {
  while (1) {
//YellowLEDProfiler++;
yellowTaskPrio=uxTaskPriorityGet(yellow_Handle);
Serial.print("YellowTaskPriority : ");
Serial.println(yellowTaskPrio);
//delay(300);
  }
}

void loop() {}