#include "Config.h"
#include <EEPROM.h>

#define SELECTED_APP_ADDRESS 0

uint8_t Config::getSelectedApp() {
    // eeprom_buffer_fill();
    // return eeprom_buffered_read_byte(SELECTED_APP_ADDRESS);
}

#define DATA_LENGTH E2END

void Config::setSelectedApp(uint8_t id) {
  // // Fill the EEPROM buffer in memory with data
  // eeprom_buffered_write_byte(0, 255);

  // // Copy the data from the buffer to the flash
  // eeprom_buffer_flush();

  // // Clear the buffer for demonstration purpose
  // eeprom_buffered_write_byte(0, 0);

  // // Print the 254th byte of the current buffer (should be 0)
  // Serial.println(eeprom_buffered_read_byte(0));

  // // Copy the data from the flash to the buffer
  // eeprom_buffer_fill();

  // // Print the 254th byte of the current buffer (should be 254)
  // Serial.println(eeprom_buffered_read_byte(0));
}