#include <MercuryBoot/memory/eeprom.hpp>

#include <avr/eeprom.h>

uint32_t Eeprom::getTotalSize(void) const {
    return 0x1000;
}

uint8_t Eeprom::readByte(const uint32_t& addr) const {
    const uint16_t mask = getTotalSize() - 1; 
    uint8_t* ptr = reinterpret_cast<uint8_t*>(mask & addr);
    return eeprom_read_byte(ptr);
}