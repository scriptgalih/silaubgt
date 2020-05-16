#include <EEPROM.h>
#include "EEPROMAnything.h"

struct config_t
{
  int set_lux[5];
  int set_timer[5];
} configuration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM_readAnything(0, configuration);

  configuration.set_lux[0] = 50;
  configuration.set_lux[1] = 100;
  configuration.set_lux[2] = 150;
  configuration.set_lux[3] = 200;
  configuration.set_lux[4] = 250;

  configuration.set_timer[0] = 1;
  configuration.set_timer[1] = 2;
  configuration.set_timer[2] = 3;
  configuration.set_timer[3] = 4;
  configuration.set_timer[4] = 6;

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
