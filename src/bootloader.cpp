#include <MercuryBoot/bootloader.hpp>
    
#include <MercuryCAN/controller/receiver.hpp>
#include <MercuryCAN/controller/transmitter.hpp>

Bootloader::Bootloader(void) : 
    _rx(new Can::Controller::Receiver), 
    _tx(new Can::Controller::Transmitter) 
{}

bool Bootloader::awaitEntryFrame(const uint32_t timeoutMs) const {
    volatile uint8_t value = 0;

    Can::Model::Message rxEntryMsg(
        1,
        &value 
    );
    
    return _rx->awaitMessage(rxEntryMsg, timeoutMs) && _magicWord == value;
}

void Bootloader::execute(void) const {

}

void Bootloader::resetHardware(void) const {

}

int Bootloader::jumpToApp(void) const {
    int (*entry)(void) = reinterpret_cast<int(*)(void)>(_appStartAddress);
    return entry();
}