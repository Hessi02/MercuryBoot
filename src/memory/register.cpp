#include <MercuryBoot/memory/register.hpp>

uint32_t Register::getTotalSize(void) const {
    return 0x200;
}

uint8_t Register::readByte(const uint32_t& addr) const {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(0xffff & addr);
    return *ptr;
}