#ifndef __MERCURY_BOOT_MEMORY_HPP__
#define __MERCURY_BOOT_MEMORY_HPP__

#include <stdint.h>

class Memory
{
public:
    Memory(const uint32_t& size, const uint32_t& offset = 0);
    uint32_t getSize(void) const;
    
    virtual uint8_t readByte(const uint32_t& address) const = 0;
    
protected:
    uint32_t buildMask(void) const;
    uint32_t calculateShiftedAddress(const uint32_t& address) const;

    const uint32_t _size;
    const uint32_t _offset;
};

#endif //__MERCURY_BOOT_MEMORY_HPP__