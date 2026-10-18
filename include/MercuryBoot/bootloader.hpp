#ifndef __MERCURY_BOOT_BOOTLOADER_HPP__
#define __MERCURY_BOOT_BOOTLOADER_HPP__

#include <cstdint>

#include <MercuryBoot/memory/eeprom.hpp>
#include <MercuryBoot/memory/flash.hpp>
#include <MercuryBoot/memory/sram.hpp>

#include <MercuryCAN/support/signalSlot/metaObject.hpp>

namespace Can 
{    
    namespace Controller
    {
        class Receiver;
        class Transmitter;
    }

    namespace Model
    {
        class Message;
        class CyclicMessage;
    }
}

class Bootloader : public SignalSlot::MetaObject
{
public:
    Bootloader(void);
    bool awaitEntryFrame(const uint32_t timeoutMs) const;
    void execute(void);
    void resetHardware(void) const;
    int jumpToApp(void) const;
        
private:
    void startHeartbeat(void);
    void startMemoryReadAsync(void);
    void incrementRollingCounter(uint32_t tickCountMs);
    void onReadCallback(uint32_t tickCountMs);
    void transmitReadData(uint8_t type, uint32_t address, uint16_t word);
    
    volatile bool _exitFlag = false;

    Can::Controller::Receiver*    _rx = nullptr;
    Can::Controller::Transmitter* _tx = nullptr;

    Can::Model::CyclicMessage* _heartbeatMessage  = nullptr;
    Can::Model::CyclicMessage* _readMemoryMessage = nullptr;

    volatile uint8_t  _rollingCounter;
    volatile uint8_t  _readMemoryType;
    volatile uint32_t _readMemoryAddress;

    Eeprom _eeprom;
    Flash  _flash;
    Sram   _sram;

    static constexpr uint16_t _entryFrameRxId = 0x01;
    static constexpr uint16_t _heartbeatTxId  = 0x02;
    static constexpr uint16_t _exitFrameRxId  = 0x03;
    static constexpr uint16_t _readMemoryRxId = 0x10;
    static constexpr uint16_t _readMemoryTxId = 0x11;

    static constexpr uint8_t  _magicWord          = 0x80;
    static constexpr uint16_t _heartbeatCycleTime = 1000;

    static constexpr std::uintptr_t _appStartAddress = 0x00;
};

#endif //__MERCURY_BOOT_BOOTLOADER_HPP__