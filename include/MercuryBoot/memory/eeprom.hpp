#ifndef __MERCURY_BOOT_EEPROM_HPP__
#define __MERCURY_BOOT_EEPROM_HPP__

#include <MercuryBoot/memory/memory.hpp>

class Eeprom : public Memory
{
public:
    virtual uint32_t getTotalSize(void) const override;
    virtual uint8_t readByte(const uint32_t& addr) const override;

private:
    static constexpr uint32_t _size = 0x1000;
    static constexpr uint32_t _mask = _size - 1;
};

#endif //__MERCURY_BOOT_EEPROM_HPP__