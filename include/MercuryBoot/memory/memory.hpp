#ifndef __MERCURY_BOOT_MEMORY_HPP__
#define __MERCURY_BOOT_MEMORY_HPP__

#include <stdint.h>

class Memory
{
public:
    virtual uint32_t getTotalSize(void) const = 0;
    virtual uint8_t readByte(const uint32_t& addr) const = 0;
};

#endif //__MERCURY_BOOT_MEMORY_HPP__