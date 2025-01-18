#ifndef LOGGING_H
#define LOGGING_H

#include "remote_configuration.h"

// #define LogInfo( tag, message, ... ) (ENABLE_LOGGING == 1)? ( ESP_LOGI( tag, message, ##__VA_ARGS__ ) ) : ()
// #define LogInfo( tag, message, ... ) ESP_LOGI( tag, message, ##__VA_ARGS__ )

#define LogInfo( tag, message, ... ) if( ENABLE_LOGGING == 1 ) ESP_LOGI( tag, message, ##__VA_ARGS__ )

#endif
