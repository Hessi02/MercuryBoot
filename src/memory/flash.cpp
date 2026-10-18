#include <MercuryBoot/memory/flash.hpp>

#include <avr/pgmspace.h>

Flash::Flash(void) : Memory(0x20000U) {}

uint8_t Flash::readByte(const uint32_t& address) const {
    return pgm_read_byte_far(calculateShiftedAddress(address));
}