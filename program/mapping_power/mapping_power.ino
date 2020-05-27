/*

  Example of BH1750 library usage.

  This example initialises the BH1750 object using the default high resolution
  continuous mode and then makes a light level reading every second.

  Connection:

    VCC -> 3V3 or 5V
    GND -> GND
    SCL -> SCL (A5 on Arduino Uno, Leonardo, etc or 21 on Mega and Due, on esp8266 free selectable)
    SDA -> SDA (A4 on Arduino Uno, Leonardo, etc or 20 on Mega and Due, on esp8266 free selectable)
    ADD -> (not connected) or GND

  ADD pin is used to set sensor I2C address. If it has voltage greater or equal to
  0.7VCC voltage (e.g. you've connected it to VCC) the sensor address will be
  0x5C. In other case (if ADD voltage less than 0.7 * VCC) the sensor address will
  be 0x23 (by default).

*/


#include <Wire.h>
#include <BH1750.h>
#include "Dimmer.h"
BH1750 lightMeter;
Dimmer dimmer(10, DIMMER_RAMP, 1);

void setup() {
  pinMode(10, 1);
  digitalWrite(10, 1);
  Serial.begin(9600);
  dimmer.begin();
  dimmer.set(0);
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

  lightMeter.begin();
  float lux = lightMeter.readLightLevel();
  Serial.println(F("BH1750 Test begin"));
  delay(500);
  Serial.println(F("p\tw"));
  for (int x = 15; x <= 90; x += 5) {
    dimmer.set(x);
    delay(2000);
    float lux = lightMeter.readLightLevel();
    Serial.println((String)x + "\t" + (String)(lux * 0.0015));
  }
  while (1);
}


void loop() {

  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(200);

}
