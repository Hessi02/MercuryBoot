#ifndef __MERCURY_BOOT_SRAM_HPP__
#define __MERCURY_BOOT_SRAM_HPP__

#include <MercuryBoot/memory/memory.hpp>

class Sram : public Memory
{
public:
    Sram(void);
    virtual uint8_t readByte(const uint32_t& address) const override;
    virtual uint16_t readWord(const uint32_t& address) const override;
};

#endif //__MERCURY_BOOT_SRAM_HPP__