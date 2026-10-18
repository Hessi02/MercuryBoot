#include <MercuryBoot/memory/sram.hpp>

uint32_t Sram::getTotalSize(void) const {
    return _size;
}

uint8_t Sram::readByte(const uint32_t& addr) const {
    const uint32_t shiftedAddress = _mask & (addr + _offset);
    uint8_t* ptr = reinterpret_cast<uint8_t*>(shiftedAddress);
    return *ptr;
}