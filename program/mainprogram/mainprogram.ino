#include "GLOBAL_VARIABLE.h"
#include <LCD5110_Graph.h>
#include <Wire.h>
#include "SparkFunBME280.h"
#include <BH1750.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"
LCD5110 myGLCD(4, 7, 8, 12, 11);
BME280 mySensorB;
BH1750 lightMeter;
extern uint8_t SmallFont[];
extern unsigned char TinyFont[];

int idx[2];
int countDown = 120;  // Countind down 2 minutes
unsigned long lastTick;
//unsigned long tick_1;
struct config_t
{
  int set_lux[5];
  int set_timer[5];
} configuration;


void setup()
{
  Serial.begin(9600);
  EEPROM_readAnything(0, configuration);
  Serial.println("Example showing alternate I2C addresses");
  Wire.begin();
  pinMode(PB_INTENSITY, 0);
  pinMode(PB_TIMER, 0);
  pinMode(PB_OK, 0);

  pinMode(DIM_1, 1);
  pinMode(DIM_2, 1);
  pinMode(DIM_3, 1);
  pinMode(DIM_4, 1);

  digitalWrite(PB_INTENSITY, 1);
  digitalWrite(PB_TIMER, 1);
  digitalWrite(PB_OK, 1);

  digitalWrite(DIM_1, 0);
  digitalWrite(DIM_2, 0);
  digitalWrite(DIM_3, 0);
  digitalWrite(DIM_4, 0);
  lightMeter.begin();
  mySensorB.setI2CAddress(0x76); //Connect to a second sensor
  if (mySensorB.beginI2C() == false) Serial.println("Sensor B connect failed");
  myGLCD.InitLCD();
  homeScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  sensorScreen();
  //  delay(500);
  Serial.println("al-awal");
  settingScreen();
  Serial.println("timer mulai");
  sensorScreen();
  Serial.println("timer berhenti");
}

void homeScreen() {
  myGLCD.setFont(SmallFont);
  myGLCD.print("UV Sterilizer", CENTER, 0);
  myGLCD.drawLine(0, 8, 84, 8);
  myGLCD.update();
}

void sensorScreen()
{
  Serial.println("Timer");
  while (1) {
    digitalWrite(DIM_1, 1);
    delay(100);
    unsigned long currentMillis = millis();

    if (currentMillis - lastTick >= 1000) {
      countDown--;
      lastTick += 1000;
    }
    myGLCD.clrScr();
    float luxx = lightMeter.readLightLevel();
    float temp = mySensorB.readTempC();
    int pos_x;
    int pos_string = 12;
    int offset_t = 10;
    int mins = countDown / 60;
    int secs = countDown % 60;

    char c[10];

    if (mins == 0 && secs == 0)
      break;
    homeScreen();
    myGLCD.setFont(SmallFont);
    myGLCD.print("T:", 3, pos_string + offset_t);
    myGLCD.printNumF(temp, 1, 14, pos_string + offset_t);
    myGLCD.print("C", 39, pos_string + offset_t);
    myGLCD.print("L:", 3, pos_string);
    myGLCD.printNumF(luxx, 1, 14, pos_string);
    if (luxx < 10)
      pos_x = 33;
    else if (luxx < 100)
      pos_x = 33 + 6;
    else if (luxx < 1000)
      pos_x = 33 + (6 * 2);
    myGLCD.print("lux", pos_x, pos_string);
    myGLCD.print("Timer:", 3, pos_string + (offset_t * 2));
    sprintf(c, "%2d:%2d", mins, secs);
    myGLCD.print(c, 40, pos_string + (offset_t * 2));
    myGLCD.update();
  }
}

void settingScreen() {
  Serial.println("Main Menuuu");
  unsigned long tick_1;
  tick_1 = millis();
  boolean last_timer = false;
  while (1) {

    digitalWrite(DIM_1, 0);
    int pos_x = 50;
    int pos_string = 12;
    int offset_t = 10;
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print("SET PARAM", CENTER, 0);
    myGLCD.drawLine(0, 8, 84, 8);
    myGLCD.print("Set Lux:", 3, pos_string);
    myGLCD.print("Set Tim:", 3, pos_string + offset_t);
    myGLCD.printNumI(configuration.set_lux[idx[0]], pos_x, pos_string);
    myGLCD.printNumI(configuration.set_timer[idx[1]], pos_x, pos_string + offset_t);
    myGLCD.update();
    //
    //    if (!digitalRead(PB_INTENSITY)) {
    //      while (!digitalRead(PB_INTENSITY))
    //        yield();
    //      idx[0]++;
    //      if (idx[0] >= 5)
    //        idx[0] = 0;
    //      Serial.print("Intensity:");
    //      Serial.println(configuration.set_lux[idx[0]]);
    //    }
    tick_1 = millis(); delay(10);
    if (!digitalRead(PB_INTENSITY)) {
      while (!digitalRead(PB_INTENSITY))
      {
        if (timerX(tick_1, 1000) && last_timer)
        {
          advScren();
          while (!digitalRead(PB_INTENSITY))
            delay(1);
          advance_mode(0);
        }
        last_timer = timerX(tick_1, 1000);
      }

      idx[0]++;
      if (idx[0] >= 5)
        idx[0] = 0;
      Serial.print("Intensity:");
      Serial.println(configuration.set_lux[idx[0]]);
    } else if (!digitalRead(PB_TIMER)) {
      while (!digitalRead(PB_TIMER))
      {
        if (timerX(tick_1, 1000) && last_timer)
        {
          advScren();
          while (!digitalRead(PB_TIMER))
            delay(1);
          advance_mode(1);
        }
        last_timer = timerX(tick_1, 1000);
      }

      idx[1]++;
      if (idx[1] >= 5)
        idx[1] = 0;
      Serial.print("Timer:");
      Serial.println(configuration.set_timer[idx[1]]);
    } else if (!digitalRead(PB_OK)) {
      while (!digitalRead(PB_OK)) {
        delay(1);
        Serial.print("OK menu");
      }

      lastTick = millis();
      countDown = configuration.set_timer[idx[1]] * 60;
      break;
    }
  }
}
