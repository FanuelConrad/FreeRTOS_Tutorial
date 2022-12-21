#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED 6
#define YELLOW 7
#define BLUE 8

typedef int TaskProfiler;

TaskProfiler SenderTaskProfiler;
TaskProfiler ReceiverTaskProfiler;

QueueHandle_t yearQueue;

void setup() {
  Serial.begin(9600);
  yearQueue = xQueueCreate(5, sizeof(int32_t));

  xTaskCreate(vSenderTask, "Sender Task 1", 100, 1998, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 2", 100, 2019, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, NULL, 2, NULL);
}


void vSenderTask(void *pvParameters) {
  BaseType_t qStatus;
  int32_t valueToSend;
  valueToSend = (int32_t)pvParameters;
  pinMode(RED, OUTPUT);
  while (1) {
    qStatus = xQueueSend(yearQueue, &valueToSend, 0);
    if (qStatus != pdPASS) {
      Serial.print("Could not send to the queue");
    }
    digitalWrite(RED, HIGH);
    for (int i = 0; i < 30000; i++) {}
  }
}

void vReceiverTask(void *pvParameters) {
  BaseType_t qStatus;
  int32_t valueReceived;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  while (1) {
    qStatus = xQueueReceive(yearQueue, &valueReceived, xTicksToWait);
    if (qStatus == pdPASS) {
      Serial.print("Data received successfully : ");
      Serial.println(valueReceived);

    } else {
      Serial.print("Could not receive from queue");
    }
    digitalWrite(RED, LOW);
    for (int i = 0; i < 30000; i++) {}
  }
}
void loop() {}