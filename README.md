# freertos-sensor-alert-stm32



This project demonstrates a simple FreeRTOS based embedded system on STM32.



The firmware reads simulated sensor values from analog inputs, processes them in separate FreeRTOS tasks, and sends structured data over Serial for external validation. It also includes a basic watchdog task to detect when sensor updates stop.



The project is inspired by automotive ECU validation workflows, where sensor values are monitored, checked against thresholds, and logged for testing.



**Main features:**



FreeRTOS task scheduling on STM32

Analog sensor reading using analogRead

Queue-based communication between tasks

Semaphore-based LED status indication

Basic watchdog fault detection

Structured Serial output for Python-based validation

Priority based scheduling



**Tools**

STM32 · FreeRTOS · Embedded C · Wokwi



**Hardware (Wokwi simulation)**

&#x20;STM32 Nucleo C031C6

&#x20;Potentiometer 1 (A0) - speed signal simulation

&#x20;Potentiometer 2 (A1) - temperature signal simulation



**Serial output format**

timestamp,value,type



Examples:

1015,102,ok:normal     -- speed signal, below threshold

2015,50.00,TEMP        -- temperature reading

WATCHDOG,0,FAULT       -- fault detected



**Tasks**

* vTaskSensor   --> reads speed pot every 1s
* vTaskProcess  --> validates against threshold, prints structured output
* vTaskDisplay  --> blinks LED on each reading
* vTaskTemp     --> reads temperature pot every 2s
* vTaskWatchdog --> detects sensor freeze after 3s timeout



**Screenshots**

!\[Alert state](images/1.png)

!\[Normal state](images/2.png)

!\[Fault detected](images/3.png)

!\[Temperature reading](images/4.png)

