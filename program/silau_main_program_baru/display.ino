void sensorDisplay(float temp, float power, int t_mins, int t_seconds) {
  int pos_x;
  int pos_string = 12;
  int offset_t = 10;
  char c[10];
  if (temp <= 0)
    temp = 0.001;
  if (power <= 0)
    power = 0.001;
  myGLCD.clrScr();
  homeScreen();
  myGLCD.setFont(SmallFont);
  myGLCD.print("T:", 3, pos_string + offset_t);
  myGLCD.printNumF(abs(temp), 1, 14, pos_string + offset_t);
  myGLCD.print("C", v2p(temp), pos_string + offset_t);

  myGLCD.print("P:", 3, pos_string);
  myGLCD.printNumF(abs(power), 1, 14, pos_string);
  myGLCD.print("Joule", v2p(power), pos_string);

  myGLCD.print("Timer:", 3, pos_string + (offset_t * 2));
  sprintf(c, "%2d:%2d", t_mins, t_seconds);
  myGLCD.print(c, 40, pos_string + (offset_t * 2));
  myGLCD.update();
}

void homeScreen() {
  myGLCD.setFont(SmallFont);
  myGLCD.print("UV Sterilizer", CENTER, 0);
  myGLCD.drawLine(0, 8, 84, 8);
}

int v2p(float val) {
  int point;
  if (val < 10)
    point = 36;
  else if (val < 100)
    point = 36 + 6;
  else if (val < 1000)
    point = 36 + (6 * 2);

  return point;
}

void settingScreen(float power, float t_min) {
  int pos_x = 50;
  int pos_string = 12;
  int offset_t = 10;
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("SET PARAM", CENTER, 0);
  myGLCD.drawLine(0, 8, 84, 8);
  myGLCD.print("Set Pow:", 3, pos_string);
  myGLCD.print("Set Tim:", 3, pos_string + offset_t);
  myGLCD.printNumF(power, 1, pos_x, pos_string);
  myGLCD.printNumI(t_min, pos_x, pos_string + offset_t);
  myGLCD.update();
}

void advScren() {
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("ADVANCE", CENTER, 15);
  myGLCD.print("MODE", CENTER, 25);
  myGLCD.update();
  delay(500);
}

void screenAdvPower(float customVal) {
  int pos_x = 38;
  int pos_string = 12;
  int offset_t = 10;
  int pos_cursor;
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("SET POWER", CENTER, 0);
  myGLCD.drawLine(0, 8, 84, 8);
  myGLCD.print("value:", CENTER, pos_string);
  myGLCD.setFont(MediumNumbers);
  myGLCD.printNumF(customVal, 1, CENTER, pos_string + offset_t);
  myGLCD.update();
}

void warningMSG() {
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("WARING !!!", CENTER, 10);
  myGLCD.print("JGN PAKAI", CENTER, 20);
  myGLCD.print("TIMER TERLAMA", CENTER, 30);
  myGLCD.update();
}

void introMSG() {
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("UV-C", CENTER, 10);
  myGLCD.print("STERILLIZER", CENTER, 20);
  myGLCD.print("SV-UGM", CENTER, 30);
  myGLCD.update();
}
