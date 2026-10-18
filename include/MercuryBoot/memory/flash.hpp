#ifndef __MERCURY_BOOT_FLASH_HPP__
#define __MERCURY_BOOT_FLASH_HPP__

#include <MercuryBoot/memory/memory.hpp>

class Flash : public Memory
{
public:
    Flash(void);
    virtual uint8_t readByte(const uint32_t& address) const override;
    virtual uint16_t readWord(const uint32_t& address) const override;
};

#endif //__MERCURY_BOOT_FLASH_HPP__