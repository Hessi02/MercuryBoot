#include <MercuryBoot/memory/flash.hpp>

#include <avr/pgmspace.h>

uint32_t Flash::getTotalSize(void) const {
    return 0x20000UL;
}

uint8_t Flash::readByte(const uint32_t& addr) const {
    const uint32_t mask = getTotalSize() - 1; 
    return pgm_read_byte_far(mask & addr);
}