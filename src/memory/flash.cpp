#include <MercuryBoot/memory/flash.hpp>

#include <avr/pgmspace.h>

uint32_t Flash::getTotalSize(void) const {
    return _size;
}

uint8_t Flash::readByte(const uint32_t& addr) const {
    return pgm_read_byte_far(_mask & addr);
}