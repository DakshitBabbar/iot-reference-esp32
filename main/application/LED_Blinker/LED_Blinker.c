#include "LED_Blinker.h"
#include "remote_configuration.h"

#include "esp_log.h"
#include <esp_err.h>

#include "app_driver.h"

#include "logging.h"

//#define LED_GPIO_PIN   8  // Change this to the GPIO pin connected to your LED

static const char * TAG = "Sensor sampling task";

#define myConfig ( &myConfigStruct )


void blinkerTask( void * pvParam ){
    //application task
    ( void ) pvParam;

    LogInfo( TAG, "LED Initialisation" );

    /* Hardware initialisation */
    esp_err_t ret = app_driver_init();

    LogInfo( TAG, "Before while Loop & GPIO setup" );

    while (1) {
        // Turn the LED on
        LogInfo( TAG, "Setting pin to 1");

        ret = app_driver_led_on();

        LogInfo( TAG, "LED ON ret = %s ", esp_err_to_name( ret ));

        vTaskDelay(pdMS_TO_TICKS( myConfig->delayTimeMs ));  // Delay for 1 second

        LogInfo( TAG, "After 1st delay %ld", myConfig->delayTimeMs );

        // Turn the LED off
        LogInfo( TAG, "Setting pin to 0");

        ret = app_driver_led_off();
        
        LogInfo( TAG, "LED OFF ret = %s ", esp_err_to_name( ret ));

        vTaskDelay(pdMS_TO_TICKS( myConfig->delayTimeMs ));  // Delay for 1 second
        LogInfo( TAG, "After 2nd delay %ld", myConfig->delayTimeMs );

        LogInfo( TAG, "Function End.....LOOPING" );

    }

}