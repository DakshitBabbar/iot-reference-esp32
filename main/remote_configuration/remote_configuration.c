/* Standard includes. */
#include <string.h>

/* ESP-IDF includes. */
#include <esp_err.h>
#include <esp_log.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <sdkconfig.h>
#include "remote_configuration.h"

static const char * TAG = "remote_configuration.c";

ConfigStruct_t myConfigStruct = {0};

void initialiseConfigStruct(void)
{
    ESP_LOGI( TAG, "#########initialising config struct########\n" );
    esp_err_t ret;

    // Initialize NVS for the "rconf" partition
    ret = nvs_flash_init_partition("rconf");
    if (ret != ESP_OK) {
        ESP_LOGI(TAG, "Error initializing NVS partition 'rconf': %s", esp_err_to_name(ret));
        return;
    }

    nvs_handle_t nvs_handle;
    ret = nvs_open_from_partition("rconf", "rConfParameters", NVS_READONLY, &nvs_handle);

    if (ret != ESP_OK) {
        ESP_LOGI( TAG, "Error (%s) opening NVS rconf handle!\n", esp_err_to_name(ret) );
        return;
    }

    // Read an integer value
    uint32_t delayTimeMs;
    if (nvs_get_u32( nvs_handle, "delayTimeMs", &delayTimeMs) == ESP_OK ) {
        ESP_LOGI( TAG, "delayTimeMs: %ld, loaded\n", delayTimeMs );
    }

    myConfig->delayTimeMs = delayTimeMs;

    // Read an integer value
    uint32_t enableLogging;
    if (nvs_get_u32( nvs_handle, "enableLogging", &enableLogging) == ESP_OK ) {
        ESP_LOGI( TAG, "enableLogging: %ld, loaded\n", enableLogging );
    }

    myConfig->enableLogging = enableLogging;

    nvs_close(nvs_handle);
}
/* remote-config adds */


void updateRconfPartition(void)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret;
    
    // Open NVS with READWRITE access
    ret = nvs_open_from_partition("rconf", "rConfParameters", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK) {
        ESP_LOGI(TAG, "Error (%s) opening NVS rconf handle!\n", esp_err_to_name(ret));
        return;
    }

    // Set an integer value for "delayTimeMs"
    uint32_t delayTimeMs = myConfig->delayTimeMs;
    ret = nvs_set_u32(nvs_handle, "delayTimeMs", delayTimeMs);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "delayTimeMs: %ld, set successfully", delayTimeMs);
    } else {
        ESP_LOGI(TAG, "Error setting delayTimeMs: %s", esp_err_to_name(ret));
    }

    // Set an integer value for "enableLogging"
    uint32_t enableLogging = myConfig->enableLogging; // Example value (1 for true, 0 for false)
    ret = nvs_set_u32(nvs_handle, "enableLogging", enableLogging);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "enableLogging: %ld, set successfully", enableLogging);
    } else {
        ESP_LOGI(TAG, "Error setting enableLogging: %s", esp_err_to_name(ret));
    }

    // Commit changes to NVS
    ret = nvs_commit(nvs_handle);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Changes committed successfully to NVS.");
    } else {
        ESP_LOGI(TAG, "Error committing changes to NVS: %s", esp_err_to_name(ret));
    }

    // Close the NVS handle
    nvs_close(nvs_handle);
}
