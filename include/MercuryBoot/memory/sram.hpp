#ifndef __MERCURY_BOOT_SRAM_HPP__
#define __MERCURY_BOOT_SRAM_HPP__

#include <MercuryBoot/memory/memory.hpp>

class Sram : public Memory
{
public:
    virtual uint32_t getTotalSize(void) const override;
    virtual uint8_t readByte(const uint32_t& addr) const override;

private:
    static constexpr uint32_t _offset = 0x200;
    static constexpr uint32_t _size = 0x1000;
    static constexpr uint32_t _mask = _size - 1;
};

#endif //__MERCURY_BOOT_SRAM_HPP__