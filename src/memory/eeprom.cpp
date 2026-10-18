#include <MercuryBoot/memory/eeprom.hpp>

#include <avr/eeprom.h>

Eeprom::Eeprom(void) : Memory(0x1000) {}

uint8_t Eeprom::readByte(const uint32_t& address) const {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(calcShiftedAddress(address));
    return eeprom_read_byte(ptr);
}

uint16_t Eeprom::readWord(const uint32_t& address) const {
    uint16_t* ptr = reinterpret_cast<uint16_t*>(calcShiftedAddress(address));
    return eeprom_read_word(ptr);
}