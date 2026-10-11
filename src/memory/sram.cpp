#include <MercuryBoot/memory/sram.hpp>

uint32_t Sram::getTotalSize(void) const {
    return 0x1000;
}

uint8_t Sram::readByte(const uint32_t& addr) const {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(0xffff & (addr + 0x200));
    return *ptr;
}