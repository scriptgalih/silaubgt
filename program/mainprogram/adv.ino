int advance_mode(int in)
{
  /*
     0 = intensity
     1 = timer
  */
  bool out = false;
  String s_set;
  boolean adv_set_idx = 0;
  int adv_idx = 1;
  int value;
  int last_set_value;
  if (in)
  {
    s_set = "timer";
  }
  else
  {
    s_set = "Intensity";
  }
  value = adv_val(in, 0);
  last_set_value = value;
  Serial.println("Advance Menu");
  while (1)
  {
    int pos_x = 38;
    int pos_string = 12;
    int offset_t = 10;
    int pos_cursor;
    if (adv_set_idx)
    {
      pos_cursor = pos_string + offset_t;
    }
    else
    {
      pos_cursor = pos_string;
    }

    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print("SET " + s_set, CENTER, 0);
    myGLCD.drawLine(0, 8, 84, 8);
    myGLCD.print("index:", 3, pos_string);
    myGLCD.print("value:", 3, pos_string + offset_t);
    myGLCD.printNumI(adv_idx, pos_x, pos_string);
    myGLCD.printNumI(value, pos_x, pos_string + offset_t);
    myGLCD.print("<<", 70, pos_cursor);
    myGLCD.update();
    unsigned long tick_2 = millis();
    if (!digitalRead(PB_OK)) {
      while (!digitalRead(PB_OK))
      {
        if (timerX(tick_2, 2000))
        {
          advScren();
          while (!digitalRead(PB_OK))
            yield();
          tick_2 = millis();
          delay(100);
          return;
          settingScreen();
          out = true;
          
        }
      }
      if (out)
        break;
      if (adv_set_idx)
      {
        adv_set_idx = false;
      }
      else
      {
        adv_set_idx = true;
      }
      Serial.println("OK2");

    }else if (!digitalRead(PB_TIMER)) { //DOWN
      while (!digitalRead(PB_TIMER))
        yield();
      //code start from here
      if (adv_set_idx) // value
      {
        switch (in) {
          case 0:
            value -= 10;
            break;
          case 1:
            value -= 1;
            break;
          default:
            // code block
            break;
        };
        if (adv_idx == 1) {
          if (value <= 0)
            value = 0;
        } else {
          if (value <= adv_val(in, adv_idx - 2))
            value = last_set_value;

        }
        last_set_value = value;
        advSaveValue(in, adv_idx - 1, value);
      }
      else // index
      {
        adv_idx--;
        if (adv_idx <= 1)
          adv_idx = 1;
        value = adv_val(in, adv_idx - 1);
        last_set_value = value;
      }
      Serial.println("DOWN2");
    }else if (!digitalRead(PB_INTENSITY)) { //UP
      while (!digitalRead(PB_INTENSITY))
        yield();
      //code start from here
      if (adv_set_idx) // value
      {

        switch (in) {
          case 0:
            value += 10;
            break;
          case 1:
            value += 1;
            break;
          default:
            // code block
            break;
        };
        if (adv_idx == 5) {
          yield();
        } else {
          if (value >= adv_val(in, adv_idx))
            value = last_set_value;

        }
        last_set_value = value;
        advSaveValue(in, adv_idx - 1, value);
      }
      else // index
      {
        adv_idx++;
        if (adv_idx >= 5)
          adv_idx = 5;
        value = adv_val(in, adv_idx - 1);
      }
      Serial.println("UP2");
    }
  }
}

int adv_val(int in, int idx)
{
  int rtn;
  if (in)
  {
    rtn = configuration.set_timer[idx];
  }
  else
  {
    rtn = configuration.set_lux[idx];
  }
  return rtn;
}

void advSaveValue(int in, int idx, int val)
{
  int rtn;
  if (in)
  {
    configuration.set_timer[idx] = val;
  }
  else
  {
    configuration.set_lux[idx] = val;
  }
  EEPROM_writeAnything(0, configuration);
}
boolean timerX(int x_start, int x_stop)
{
  boolean rtn = false;
  if (millis() - x_start >= x_stop) {
    rtn = true;
  }
  return rtn;
}

void advScren() {
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("ADVANCE", CENTER, 15);
  myGLCD.print("MODE", CENTER, 25);
  myGLCD.update();
  delay(500);
}
