#include "EEPROM_str_helper.h"

#define SSID_ADDR 0
#define PASS_ADDR 256

EEPROM_str_helper::EEPROM_str_helper(/* args */)
{
    EEPROM.begin(EEPROM_DEFAULT_TOTAL_SIZE);
}

EEPROM_str_helper::~EEPROM_str_helper()
{
    EEPROM.end();
}

String EEPROM_str_helper::getSavedSSID() {
    return readStringUntil(SSID_ADDR, '\0');;
}

String EEPROM_str_helper::getSavedPassword() {
    return readStringUntil(PASS_ADDR, '\0');
}

void EEPROM_str_helper::writeString(const String str, const uint16_t startIndex) {
    const uint32_t le = str.length();
    for(size_t i = 0; i < MAX_STR_LENGTH; i++) {
        EEPROM.write(startIndex + i, i < le ? (uint8_t)str[i] : 0);
    }
}

String EEPROM_str_helper::readStringUntil (const unsigned int startAddress, const char terminateChar) {
  String temp = "";
  for (size_t i = startAddress; i < MAX_STR_LENGTH; i++)
  {
    char c = (char)EEPROM.read(i);
    if(c == terminateChar) return temp;
    else temp += c;
  }

  return temp;
}