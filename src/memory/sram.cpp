#include <MercuryBoot/memory/sram.hpp>

uint32_t Sram::getTotalSize(void) const {
    return 0x1000;
}

uint8_t Sram::readByte(const uint32_t& addr) const {
    constexpr uint32_t registerOffset = 0x200;
    const uint32_t shiftedAddress = addr + 0x200;
    uint8_t* ptr = reinterpret_cast<uint8_t*>(0xffff & shiftedAddress);
    return *ptr;
}