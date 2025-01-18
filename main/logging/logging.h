#ifndef LOGGING_H
#define LOGGING_H

#include "remote_configuration.h"

#define LogInfo( tag, message, ... ) if( ENABLE_LOGGING == 1 ) ESP_LOGI( tag, message, ##__VA_ARGS__ )

#define LogDebug( tag, message, ... ) if( ENABLE_LOGGING == 1 ) ESP_LOGD( tag, message, ##__VA_ARGS__ )

#define LogError( tag, message, ... ) if( ENABLE_LOGGING == 1 ) ESP_LOGE( tag, message, ##__VA_ARGS__ )

#endif
