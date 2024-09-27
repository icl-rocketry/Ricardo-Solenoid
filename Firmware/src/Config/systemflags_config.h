#pragma once

#include <stdint.h>
#include <type_traits>

enum class SYSTEM_FLAG:uint32_t{
    //state flags
    STATE_IDLE = (1 << 0), 
    //flags
    DEBUG = (1 << 7),
    //critical messages 
    ERROR_SERIAL = (1 << 10),
    ERROR_CAN = (1 << 11),
    //sensor messages
    ERROR_BUSV_OVF = (1 << 12)
};

using system_flag_t = uint32_t;

