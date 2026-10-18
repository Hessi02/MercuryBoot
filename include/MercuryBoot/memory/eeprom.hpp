#ifndef __MERCURY_BOOT_EEPROM_HPP__
#define __MERCURY_BOOT_EEPROM_HPP__

#include <MercuryBoot/memory/memory.hpp>

class Eeprom : public Memory
{
public:
    Eeprom(void);
    virtual uint8_t readByte(const uint32_t& address) const override;
};

#endif //__MERCURY_BOOT_EEPROM_HPP__