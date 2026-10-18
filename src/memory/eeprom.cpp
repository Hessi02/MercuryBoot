#include <MercuryBoot/memory/eeprom.hpp>

#include <avr/eeprom.h>

Eeprom::Eeprom(void) : Memory(0x1000) {}

uint8_t Eeprom::readByte(const uint32_t& address) const {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(calculateShiftedAddress(address));
    return eeprom_read_byte(ptr);
}