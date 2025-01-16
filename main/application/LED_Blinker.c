#include "LED_Blinker.h"
#include "remote_configuration.h"

#define LED_GPIO_PIN   8  // Change this to the GPIO pin connected to your LED


#define myConfig ( &myConfigStruct )

static void applicationTask( void * pvParam ){
    //application task
    ( void ) pvParam;

    // Configure the GPIO pin as output
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO_PIN),  // Set the pin mask for the LED pin
        .mode = GPIO_MODE_OUTPUT,               // Set the GPIO as output mode
        .pull_up_en = GPIO_PULLUP_DISABLE,      // Disable pull-up resistor
        .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Disable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE          // Disable interrupts
    };

    gpio_config(&io_conf);
    gpio_set_level(LED_GPIO_PIN, 0);  // Ensures LED is off initially

    while (1) {
        // Turn the LED on
        gpio_set_level(LED_GPIO_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS( myConfig->delayTimeMs ));  // Delay for 1 second

        // Turn the LED off
        gpio_set_level(LED_GPIO_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS( myConfig->delayTimeMs ));  // Delay for 1 second
    }

}