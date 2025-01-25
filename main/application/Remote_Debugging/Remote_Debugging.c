#include "Remote_Debugging.h"
#include "remote_configuration.h"

#include "esp_log.h"
#include <esp_err.h>

#include "app_driver.h"

static const char * TAG = "Stack Overflow Task";

#define myConfig ( &myConfigStruct )


void foo(int x){
    if(x == 100){
        return;
    }
    foo(x);    
}

void applicationTask( void * pvParam ){
    //application task
    ( void ) pvParam;

    // Delay to allow the jobHandler Task to run so that stack overflow could be fixed
    vTaskDelay(pdMS_TO_TICKS(20000));  


    ESP_LOGI( TAG, "Inside application Task - Stack Overflow" );
    
    char buffer[600];  // Intentionally large array to exceed the stack size

    // Fill the buffer to ensure memory is used
    for (int i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = 'A';
    }

    ESP_LOGI( TAG, "This line may never print because of stack overflow" );

    // Simulate task loop
    while (1)
    {

        ESP_LOGI( TAG, "Delaying now" );
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay to keep the task alive
    }

}

// void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
// {
//     // This function will be called when a stack overflow is detected
//     ESP_LOGE( TAG, "&&&&&&&Handle hora guyz&&&&&&" );
//     while (1);  // Halt the system or handle recovery
// }