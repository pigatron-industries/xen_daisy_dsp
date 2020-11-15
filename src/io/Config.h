#ifndef Config_h
#define Config_h

#include <inttypes.h>

class Config {
public:
    static uint8_t getSelectedApp();
    static void setSelectedApp(uint8_t id);
    
private:
};

#endif
