#include <MercuryBoot/bootloader.hpp>
    
#include <MercuryCAN/controller/receiver.hpp>
#include <MercuryCAN/controller/transmitter.hpp>
#include <MercuryCAN/model/message.hpp>
#include <MercuryCAN/model/cyclicMessage.hpp>

#include <avr/interrupt.h>
#include <avr/io.h>

extern const char dbcStr[];

Bootloader::Bootloader(void) : 
    _dbc(new Can::Model::Database(dbcStr)),
    _rx(new Can::Controller::Receiver), 
    _tx(new Can::Controller::Transmitter)
{   
}

bool Bootloader::awaitEntryFrame(const uint32_t timeoutMs) const {
    volatile uint8_t i = 0;
    
    Can::Model::Message* entryMessageRx = _dbc->buildMessage("BootEntry", &i);
    
    return _rx->awaitMessage(*entryMessageRx, timeoutMs) && _magicWord == i;
}

void Bootloader::execute(void) {
    startHeartbeat();
    startMemoryReadAsync();

    volatile uint8_t i = 0;

    Can::Model::Message* exitMessageRx = _dbc->buildMessage("BootExit", &i);

    while (_magicWord != i)
        _rx->awaitMessage(*exitMessageRx);
}

void Bootloader::resetHardware(void) const {
    cli();
    TIMSK0 = 0;
    TCCR0A = 0;
    TIFR0 = (1 << OCF0A);
    CANGIE = 0;
    CANIE1 = 0;
    CANIE2 = 0;
    CANGCON = (1 << SWRES);
    CANGCON = 0;
}

int Bootloader::jumpToApp(void) const {
    int (*entry)(void) = reinterpret_cast<int(*)(void)>(_appStartAddress);
    return entry();
}
 
void Bootloader::startHeartbeat(void) {
    _heartbeatMessage = _dbc->buildCyclicMessage(
        "Heartbeat",
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
    _readMemoryMessage = _dbc->buildCyclicMessage(
        "MemoryReadRx",
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

    const uint8_t word = memoryToRead->readWord(address);
    transmitReadData(type, address, word);
}

void Bootloader::transmitReadData(
    uint8_t type,
    uint32_t address,
    uint16_t word
) {
    Can::Model::Message* readDataFrame = _dbc->buildMessage(
        "MemoryReadTx",
        &type,
        &address,
        &word    
    );

    _tx->sendMessage(*readDataFrame);
}