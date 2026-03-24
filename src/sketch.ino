#include <STM32FreeRTOS.h>

QueueHandle_t xQueue;
SemaphoreHandle_t xSemaphore;

//Task 1
void vTaskSensor(void *pvParameters)
{
  uint32_t Sensorvalue;

    for(;;)
    {
      Sensorvalue = analogRead(A0);
      xQueueSend(xQueue, &Sensorvalue, portMAX_DELAY);
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

//task 2
void vTaskProcess(void *pvParameters)
{
  uint32_t received;

  for(;;)
  {
    if(xQueueReceive(xQueue, & received, portMAX_DELAY)){
      if (received > 511)
      {
        Serial.println("Alert:value too high");
      }
      else
      {
        Serial.println("ok:normal");
      }
      xSemaphoreGive(xSemaphore);
    }
    

  }
}
//task 3

void vTaskDisplay(void * pvParameters)
{
  pinMode(LED_BUILTIN, OUTPUT);
  for(;;)
  {
    if(xSemaphoreTake(xSemaphore, portMAX_DELAY))
    {
      digitalWrite(LED_BUILTIN, HIGH);
      vTaskDelay(pdMS_TO_TICKS(200));
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

void setup() {
  Serial.begin(115200);
  xQueue = xQueueCreate(5,sizeof(uint32_t));
  xSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(vTaskSensor, "Sensor", 128, NULL ,1, NULL);
  xTaskCreate(vTaskProcess, "Process",128, NULL, 2, NULL);
  xTaskCreate(vTaskDisplay, "Display",128, NULL, 1, NULL);
  vTaskStartScheduler();
}
void loop() {

}
