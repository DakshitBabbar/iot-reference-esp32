/* Includes *******************************************************************/

/* FreeRTOS includes. */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* ESP-IDF includes. */
#include "esp_log.h"

/* Driver Includes */
#include "driver/gpio.h"

static void applicationTask( void * pvParam );