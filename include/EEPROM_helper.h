#ifndef EEPROM_HELPER_H_
#define EEPROM_HELPER_H_

#include <EEPROM.h>
#include <wstring.h>

#define EEPROM_DEFAULT_TOTAL_SIZE 512

/**
 * this class is not the final version of a EEPROM helper. later we want to introduce a structured way of generically writing to the EEPROM
 */

class EEPROM_helper
{
private:

    String readStringUntil (const unsigned int startAddress, const char terminateChar);

public:
    EEPROM_helper();
    ~EEPROM_helper();

    //temporary
    String getSavedSSID();
    String getSavedPassword();
    void writeSSID(const String ssid);
    void writePass(const String pass);
};

#endif