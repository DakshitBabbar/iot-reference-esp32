#ifndef REMOTE_DEBUGGING_H
#define REMOTE_DEBUGGING_H

/* FreeRTOS includes. */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* ESP-IDF includes. */
#include "esp_log.h"

/* Driver Includes */
#include "driver/gpio.h"

void applicationTask( void * pvParam );

#endif