#include <MercuryBoot/memory/sram.hpp>

Sram::Sram(void) : Memory(0x1000, 0x200) {}

uint8_t Sram::readByte(const uint32_t& address) const {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(calculateShiftedAddress(address));
    return *ptr;
}