#ifndef EEPROM_HELPER_H_
#define EEPROM_HELPER_H_

#include <EEPROM.h>
#include <wstring.h>

#define EEPROM_DEFAULT_TOTAL_SIZE 512
#define MAX_STR_LENGTH 256


/**
 * the purpose of this class is soley to help writing and reading strings from the EEPROM
 */
class EEPROM_str_helper
{
/**
 * this class is not the final version of a EEPROM helper. later we want to introduce a structured way of generically writing strings to the EEPROM
 */
private:

    String readStringUntil (const unsigned int startAddress, const char terminateChar);

public:
    EEPROM_str_helper();
    ~EEPROM_str_helper();

    //temporary
    String getSavedSSID();
    String getSavedPassword();


    //writes a string with a max length of 256 (MAX_STR_LENGTH) into the EEPROM
    void writeString(const String str, const uint16_t startIndex);
};

#endif