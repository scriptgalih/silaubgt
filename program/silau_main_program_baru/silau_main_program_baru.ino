#include "GLOBAL_VARIABLE.h"
#include <LCD5110_Graph.h>
#include <Wire.h>
#include "SparkFunBME280.h"
#include <BH1750.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
#include "Dimmer.h"

LCD5110 myGLCD(4, 7, 8, 12, 11);
BME280 mySensorB;
BH1750 lightMeter;
Dimmer dimmer(10, DIMMER_RAMP);


extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
extern unsigned char MediumNumbers[];
int idx[2];
int countDown = 120;  // Countind down 2 minutes
unsigned long lastTick;
//unsigned long tick_1;

int exe_dim;
struct config_t
{
  float set_power[5];
  int set_timer[5];
  int set_dimmer[5];
} configuration;


int mainMenuPos = 1;
float exe_power = 1;
unsigned long tick_1;
boolean last_tick = true;
boolean last_state;
void setup() {
  // put your setup code here, to run once:
  dimmer.begin();
  dimmer.set(0);
  Serial.begin(9600);
  EEPROM_readAnything(0, configuration);
  Serial.println(F("Example showing alternate I2C addresses"));
  Wire.begin();
  pinMode(PB_INTENSITY, 0);
  pinMode(PB_TIMER, 0);
  pinMode(PB_OK, 0);
  pinMode(LM_DOOR, 0);

  pinMode(DIM_1, 1);
  pinMode(DIM_2, 1);
  pinMode(DIM_3, 1);
  pinMode(DIM_4, 1);

  digitalWrite(PB_INTENSITY, 1);
  digitalWrite(PB_TIMER, 1);
  digitalWrite(PB_OK, 1);
  digitalWrite(LM_DOOR, 1);

  digitalWrite(DIM_1, 0);
  digitalWrite(DIM_2, 0);
  digitalWrite(DIM_3, 0);
  digitalWrite(DIM_4, 0);

  lightMeter.begin();
  mySensorB.setI2CAddress(0x76); //Connect to a second sensor
  if (mySensorB.beginI2C() == false) Serial.println("Sensor B connect failed");
  myGLCD.InitLCD();
  delay(500);
  //  sensorDisplay(1.2, 122.2, 124);
  //  settingScreen(1.2, 4);
  settingScreen(1, configuration.set_timer[idx[1]]);
  //  updateMenu();
//  warningMSG();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateMenu();
  tick_1 = millis();
  last_tick = timerX(tick_1, 3000);
  //  delay(10);
}
