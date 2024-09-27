#include "system.h"

#include <memory>

#include <libriccore/riccoresystem.h>

#include <HardwareSerial.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include "Config/general_config.h"
#include "Config/services_config.h"

#include "Commands/commands.h"

#include "States/idle.h"


System::System():
RicCoreSystem(Commands::command_map,Commands::defaultEnabledCommands,Serial),
canbus(systemstatus, PinMap::TxCan, PinMap::RxCan, 3),
sol0(PinMap::Nuke1, networkmanager),
sol1(PinMap::Nuke2, networkmanager),
sol2(PinMap::Nuke3, networkmanager),
sol3(PinMap::Nuke4, networkmanager),
I2C(0),
curr_sensor(0b1000000, I2C)
{};


void System::systemSetup(){
    
    Serial.setRxBufferSize(GeneralConfig::SerialRxSize);
    Serial.begin(GeneralConfig::SerialBaud);
   
    //intialize rnp message logger
    loggerhandler.retrieve_logger<RicCoreLoggingConfig::LOGGERS::SYS>().initialize(networkmanager);

    //initialize statemachine with idle state
    statemachine.initalize(std::make_unique<Idle>(systemstatus,commandhandler));
    
    //any other setup goes here
    canbus.setup();
    networkmanager.addInterface(&canbus);

    networkmanager.setNodeType(NODETYPE::HUB);
    networkmanager.setNoRouteAction(NOROUTE_ACTION::BROADCAST,{1,3});

    sol0.setup();
    sol1.setup();
    sol2.setup();
    sol3.setup();

    I2C.begin(PinMap::SDA, PinMap::SCL, GeneralConfig::I2C_FREQUENCY);
    curr_sensor.setup(GeneralConfig::sense_resistance, GeneralConfig::maxExpectedCurrent);

    uint8_t solservice0 = static_cast<uint8_t>(Services::ID::sol0);
    uint8_t solservice1 = static_cast<uint8_t>(Services::ID::sol1);
    uint8_t solservice2 = static_cast<uint8_t>(Services::ID::sol2);
    uint8_t solservice3 = static_cast<uint8_t>(Services::ID::sol3);

    networkmanager.registerService(solservice0,sol0.getThisNetworkCallback());
    networkmanager.registerService(solservice1,sol1.getThisNetworkCallback());
    networkmanager.registerService(solservice2,sol2.getThisNetworkCallback());
    networkmanager.registerService(solservice3,sol3.getThisNetworkCallback());
};

long prevTime = 0;

void System::systemUpdate(){

    curr_sensor.update();
};