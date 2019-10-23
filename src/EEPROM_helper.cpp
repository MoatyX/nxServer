#include "EEPROM_helper.h"

EEPROM_helper::EEPROM_helper(/* args */)
{
}

EEPROM_helper::~EEPROM_helper()
{
    EEPROM.begin(EEPROM_DEFAULT_TOTAL_SIZE);
}

String EEPROM_helper::getSavedSSID() {
    return readStringUntil(0, '\0');;
}

String EEPROM_helper::getSavedPassword() {
    return readStringUntil(256, '\0');
}

void EEPROM_helper::writeSSID(const String ssid) {
    
}

void EEPROM_helper::writePass(const String pass) {

}

String EEPROM_helper::readStringUntil (const unsigned int startAddress, const char terminateChar) {

}