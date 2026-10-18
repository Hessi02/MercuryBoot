#include <MercuryBoot/memory/sram.hpp>

uint32_t Sram::getTotalSize(void) const {
    return 0x1000;
}

uint8_t Sram::readByte(const uint32_t& addr) const {
    constexpr uint16_t offset = 0x200;
    const uint16_t mask = getTotalSize() - 1; 
    const uint16_t shiftedAddress = mask & (addr + offset);
    uint8_t* ptr = reinterpret_cast<uint8_t*>(shiftedAddress);
    return *ptr;
}