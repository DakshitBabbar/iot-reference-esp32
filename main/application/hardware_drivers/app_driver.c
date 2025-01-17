#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "app_driver.h"
#include "esp_idf_version.h"


#define GRI_LED_GPIO    8

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 5, 0, 0 )
    static led_strip_handle_t led_strip;
#else
    static led_strip_t * led_strip;
#endif

#if ESP_IDF_VERSION == ESP_IDF_VERSION_VAL( 4, 3, 0 )
    #ifndef CONFIG_IDF_TARGET_ESP32
        #define APP_SOC_TEMP_SENSOR_SUPPORTED
    #else
        #define APP_SOC_TEMP_SENSOR_SUPPORTED    SOC_TEMP_SENSOR_SUPPORTED
    #endif
#endif

static esp_err_t led_init()
{
    esp_err_t ret = ESP_FAIL;

    #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 5, 0, 0 )
        led_strip_config_t strip_config =
        {
            .strip_gpio_num = GRI_LED_GPIO,
            .max_leds       = 1, /* at least one LED on board */
        };
        led_strip_rmt_config_t rmt_config =
        {
            .resolution_hz = 10 * 1000 * 1000, /* 10MHz */
        };
        ret = led_strip_new_rmt_device( &strip_config, &rmt_config, &led_strip );
    #else /* if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 5, 0, 0 ) */
        led_strip = led_strip_init( 0, GRI_LED_GPIO, 1 );
    #endif /* if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 5, 0, 0 ) */

    ret |= app_driver_led_on();
    return ret;
}

esp_err_t app_driver_init()
{
    esp_err_t led_ret;

    led_ret = led_init();

    if( led_ret )
    {
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

esp_err_t app_driver_led_on()
{
    esp_err_t ret = ESP_FAIL;

    #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 5, 0, 0 )
        ret = led_strip_set_pixel( led_strip, 0, 0, 25, 0 );
        /* Refresh the strip to send data */
        ret |= led_strip_refresh( led_strip );
    #else
        led_strip->set_pixel( led_strip, 0, 0, 25, 0 );
        led_strip->refresh( led_strip, 100 );
    #endif

    return ret;
}

esp_err_t app_driver_led_off()
{
    esp_err_t ret = ESP_FAIL;

    #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 5, 0, 0 )
        ret = led_strip_clear( led_strip );
    #else
        led_strip->clear( led_strip, 50 );
    #endif

    return ret;
}
