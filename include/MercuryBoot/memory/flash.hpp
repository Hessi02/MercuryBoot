#ifndef __MERCURY_BOOT_FLASH_HPP__
#define __MERCURY_BOOT_FLASH_HPP__

#include <MercuryBoot/memory/memory.hpp>

class Flash : public Memory
{
public:
    virtual uint32_t getTotalSize(void) const override;
    virtual uint8_t readByte(const uint32_t& addr) const override;
};

#endif //__MERCURY_BOOT_FLASH_HPP__