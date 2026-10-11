#include <MercuryBoot/memory/register.hpp>

uint32_t Register::getTotalSize(void) const {
    return 0x200;
}

uint8_t Register::readByte(const uint32_t& addr) const {
    const uint16_t mask = getTotalSize() - 1; 
    uint8_t* ptr = reinterpret_cast<uint8_t*>(mask & addr);
    return *ptr;
}