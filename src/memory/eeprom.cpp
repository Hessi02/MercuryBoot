#include <MercuryBoot/memory/eeprom.hpp>

#include <avr/eeprom.h>

uint32_t Eeprom::getTotalSize(void) const {
    return _size;
}

uint8_t Eeprom::readByte(const uint32_t& addr) const {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(_mask & addr);
    return eeprom_read_byte(ptr);
}