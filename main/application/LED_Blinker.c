#include "LED_Blinker.h"
#include "remote_configuration.h"

#include "esp_log.h"
#include <esp_err.h>

#include "app_driver.h"

//#define LED_GPIO_PIN   8  // Change this to the GPIO pin connected to your LED

static const char * TAG = "LED_Blinker";

#define myConfig ( &myConfigStruct )


void applicationTask( void * pvParam ){
    //application task
    ( void ) pvParam;

    ESP_LOGI( TAG, "LED Initialisation" );

    /* Hardware initialisation */
    esp_err_t ret = app_driver_init();

    ESP_LOGI( TAG, "Before while Loop & GPIO setup" );

    while (1) {
        // Turn the LED on
        ESP_LOGI( TAG, "Setting pin to 1");

        ret = app_driver_led_on();

        ESP_LOGI( TAG, "LED ON ret = %s ", esp_err_to_name( ret ));

        vTaskDelay(pdMS_TO_TICKS( myConfig->delayTimeMs ));  // Delay for 1 second

        ESP_LOGI( TAG, "After 1st delay %ld", myConfig->delayTimeMs );

        // Turn the LED off
        ESP_LOGI( TAG, "Setting pin to 0");

        ret = app_driver_led_off();
        
        ESP_LOGI( TAG, "LED OFF ret = %s ", esp_err_to_name( ret ));

        vTaskDelay(pdMS_TO_TICKS( myConfig->delayTimeMs ));  // Delay for 1 second
        ESP_LOGI( TAG, "After 2nd delay %ld", myConfig->delayTimeMs );

        ESP_LOGI( TAG, "Function End.....LOOPING" );

    }

}