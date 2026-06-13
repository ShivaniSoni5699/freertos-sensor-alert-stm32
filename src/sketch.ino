#include <STM32FreeRTOS.h>

QueueHandle_t xQueue;
SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t xWatchdogSemaphore;
//Task 1
void vTaskSensor(void *pvParameters)
{
  uint32_t Sensorvalue;

    for(;;)
    {
      Sensorvalue = analogRead(A0);
      xQueueSend(xQueue, &Sensorvalue, portMAX_DELAY);
      xSemaphoreGive(xWatchdogSemaphore);
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
      Serial.print(millis());
      Serial.print(",");
      Serial.print(received);
      Serial.print(",");
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
//task 4
void vTaskWatchdog(void *pvParameters)
{
  for(;;)
  {
    if(xSemaphoreTake(xWatchdogSemaphore,pdMS_TO_TICKS(3000)) == pdFALSE)
    {
      Serial.println("WATCHDOG,0,FAULT");
    }

  }
}

void setup() {
  Serial.begin(115200);
  xQueue = xQueueCreate(5,sizeof(uint32_t));
  xSemaphore = xSemaphoreCreateBinary();
  xWatchdogSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(vTaskSensor, "Sensor", 128, NULL ,1, NULL);
  xTaskCreate(vTaskProcess, "Process",128, NULL, 2, NULL);
  xTaskCreate(vTaskDisplay, "Display",128, NULL, 1, NULL);
  xTaskCreate(vTaskWatchdog, "Watchdog", 128, NULL,3, NULL);
  vTaskStartScheduler();
  
}
void loop() {
//empty -- freertos takes charge 
}


// task1 -- queue(data) -- task2
// task2 -- semaphore -- task3
// task1 -- watchdog -- task4 