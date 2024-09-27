#pragma once


namespace GeneralConfig{
    //Serial baud rate
    static constexpr int SerialBaud = 115200;
    //Serial rx buffer size
    static constexpr int SerialRxSize = 256;

    //I2C frequrency - 400Khz
    static constexpr int I2C_FREQUENCY = 400000;

    static constexpr float sense_resistance = 2.0e-3; //ohms
    static constexpr float maxExpectedCurrent = 30.0; //Amps
};







