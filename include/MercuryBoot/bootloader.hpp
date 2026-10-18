#ifndef __MERCURY_BOOT_BOOTLOADER_HPP__
#define __MERCURY_BOOT_BOOTLOADER_HPP__

#include <cstdint>

namespace Can::Controller 
{    
    class Receiver;
    class Transmitter;
}

class Bootloader 
{
public:
    Bootloader(void);

    bool awaitEntryFrame(const uint32_t timeoutMs) const;
    void execute(void) const;
    void resetHardware(void) const;
    int jumpToApp(void) const;

private:
    Can::Controller::Receiver*    _rx = nullptr;
    Can::Controller::Transmitter* _tx = nullptr;

    static constexpr uint8_t _magicWord = 0x80;
    static constexpr std::uintptr_t _appStartAddress = 0x1000;
};

#endif //__MERCURY_BOOT_BOOTLOADER_HPP__