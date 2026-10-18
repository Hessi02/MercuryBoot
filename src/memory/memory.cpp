#include <MercuryBoot/memory/memory.hpp>

Memory::Memory(const uint32_t& size, const uint32_t& offset) :
    _size(size), _offset(offset)    
{}

uint32_t Memory::getSize(void) const {
    return _size;
}

uint32_t Memory::buildMask(void) const {
    return _size - 1;
}

uint32_t Memory::calculateShiftedAddress(const uint32_t& address) const {
    return buildMask() & (address + _offset);
}