# freertos-sensor-alert-stm32

Real-time sensor monitoring system on STM32 (NUCLEO-C031C6) using FreeRTOS.

Three concurrent tasks communicate via a queue and binary semaphore to read

an analog sensor, check a threshold, and trigger an LED alert.



**Concepts used**

Tasks, Queue, Semaphore, Priority Scheduling



**Tools**

STM32 · FreeRTOS · Embedded C · Wokwi



**Screenshots**

!\[Alert state](images/1.png)

!\[Normal state](images/2.png)

