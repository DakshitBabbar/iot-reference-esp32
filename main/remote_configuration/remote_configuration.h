#ifndef REMOTE_CONFIGURATION_H
#define REMOTE_CONFIGURATION_H

/* Standard includes. */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ConfigStruct{
    uint32_t delayTimeMs;
    uint32_t enableLogging;
} ConfigStruct_t;

extern ConfigStruct_t myConfigStruct;
#define myConfig ( &myConfigStruct )

#ifndef DELAY_TIME_MS
    #define DELAY_TIME_MS ( myConfig->delayTimeMs )
#endif

#ifndef ENABLE_LOGGING
    #define ENABLE_LOGGING ( myConfig->enableLogging )
#endif

void initialiseConfigStruct(void);

void updateRconfPartition(void);

#endif
