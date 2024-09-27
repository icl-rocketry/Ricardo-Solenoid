/**
 * @file services_config.h
 * @author Kiran de Silva (kd619@ic.ac.uk)
 * @brief Defintion of user defined services
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <stdint.h>


namespace Services{
    /**
     * @brief ID of user defined services NB start at 2, all ID's below 2 are reserved for default services found in 'rnp_networkmanager.h'
     * 
     */
    enum class ID:uint8_t{
        Serivce1 = 3,
        sol0 = 10,
        sol1 = 11,
        sol2 = 12,
        sol3 = 13
    };

};