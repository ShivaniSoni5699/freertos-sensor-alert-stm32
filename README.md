# freertos-sensor-alert-stm32

Real-time sensor monitoring system on STM32 (NUCLEO-C031C6) using FreeRTOS.

Three concurrent tasks communicate via a queue and binary semaphore to read

an analog sensor, check a threshold, and trigger an LED alert.



**Concepts used**

Tasks, Queue, Semaphore, Priority Scheduling, Watchdog



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

