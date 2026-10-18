#include <MercuryBoot/bootloader.hpp>
    
#include <MercuryCAN/controller/receiver.hpp>
#include <MercuryCAN/controller/transmitter.hpp>
#include <MercuryCAN/model/message.hpp>
#include <MercuryCAN/model/cyclicMessage.hpp>

Bootloader::Bootloader(void) : 
    _rx(new Can::Controller::Receiver), 
    _tx(new Can::Controller::Transmitter) 
{}

bool Bootloader::awaitEntryFrame(const uint32_t timeoutMs) const {
    volatile uint8_t value = 0;

    Can::Model::Message rxEntryMsg(
        _entryFrameRxId,
        &value 
    );
    
    return _rx->awaitMessage(rxEntryMsg, timeoutMs) && _magicWord == value;
}

void Bootloader::execute(void) {
    startHeartbeat();
    startMemoryReadAsync();

    volatile uint8_t exitByte = 0;

    Can::Model::Message exitMessage(
        _exitFrameRxId,
        &exitByte        
    );

    while (_magicWord != exitByte)
        _rx->awaitMessage(exitMessage);
}

void Bootloader::resetHardware(void) const {

}

int Bootloader::jumpToApp(void) const {
    int (*entry)(void) = reinterpret_cast<int(*)(void)>(_appStartAddress);
    return entry();
}
 
void Bootloader::startHeartbeat(void) {
    _heartbeatMessage = new Can::Model::CyclicMessage(
        _heartbeatTxId,
        _heartbeatCycleTime,
        &_rollingCounter
    ); 

    SignalSlot::MetaObject::connect(
        _heartbeatMessage,
        &Can::Model::Message::preSend,
        this,
        &Bootloader::incrementRollingCounter
    );

    _tx->addCyclicMessage(*_heartbeatMessage);
}

void Bootloader::incrementRollingCounter(uint32_t) {
    _rollingCounter = static_cast<uint8_t>(_rollingCounter + 1);
}

void Bootloader::startMemoryReadAsync(void) {
    _readMemoryMessage = new Can::Model::CyclicMessage(
        _readMemoryRxId,
        1,
        &_readMemoryType,
        &_readMemoryAddress
    );

    SignalSlot::MetaObject::connect(
        _readMemoryMessage,
        &Can::Model::Message::received,
        this,
        &Bootloader::onReadCallback
    );

    _rx->addCyclicMessage(*_readMemoryMessage);
}

void Bootloader::onReadCallback(uint32_t tickCountMs) {
    const uint8_t type = _readMemoryType;
    const uint32_t address = _readMemoryAddress; 

    Memory* memoryToRead = nullptr;

    switch (type) {
        case 0: memoryToRead = &_flash;  break;
        case 1: memoryToRead = &_eeprom; break;
        case 2: memoryToRead = &_sram;   break;
    }

    if (!memoryToRead)
        return;

    const uint8_t byte = memoryToRead->readByte(address);
    transmitReadData(type, address, byte);
}

void Bootloader::transmitReadData(
    uint8_t type,
    uint32_t address,
    uint8_t data
) {
    Can::Model::Message readDataFrame(
        _readMemoryTxId,
        &type,
        &address,
        &data    
    );

    _tx->sendMessage(readDataFrame);
}