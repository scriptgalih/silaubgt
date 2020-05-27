#include <EEPROM.h>
#include "EEPROMAnything.h"

struct config_t
{
  float set_lux[5];
  int set_timer[5];
  int set_dimmer[5];
} configuration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM_readAnything(0, configuration);

  configuration.set_lux[0] = 1.0;
  configuration.set_lux[1] = 1.1;
  configuration.set_lux[2] = 1.5;
  configuration.set_lux[3] = 1.8;
  configuration.set_lux[4] = 2.0;

  configuration.set_timer[0] = 1;
  configuration.set_timer[1] = 2;
  configuration.set_timer[2] = 3;
  configuration.set_timer[3] = 4;
  configuration.set_timer[4] = 15;

  EEPROM_writeAnything(0, configuration);

  for (int x = 0; x < 5; x++) {
    Serial.println("set lux ke-" + (String)x + ":" + (String)configuration.set_lux[x]);
  }

  for (int x = 0; x < 5; x++) {
    Serial.println("set lux ke-" + (String)x + ":" + (String)configuration.set_timer[x]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
