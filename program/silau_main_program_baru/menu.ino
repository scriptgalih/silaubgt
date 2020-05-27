void updateMenu() {
  switch (mainMenuPos) {
    case 1: //Home Screen
      if (!digitalRead(PB_INTENSITY)) {
        while (!digitalRead(PB_INTENSITY))
        {
          delay(1);
        }
        idx[0]++;
        if (idx[0] >= 5)
          idx[0] = 0;

        exe_dim = configuration.set_power[idx[0]] * 64.395 - 47.997;
        Serial.print("Intensity:");
        Serial.println(exe_power);
      }
      if (!digitalRead(PB_TIMER)) {
        while (!digitalRead(PB_TIMER))
        {
          delay(1);
        }

        idx[1]++;
        if (idx[1] >= 5)
          idx[1] = 0;
        Serial.print("Timer:");
        Serial.println(configuration.set_timer[idx[1]]);

      }
      if (!digitalRead(PB_OK)) {
        while (!digitalRead(PB_OK)) {
          delay(1);
          //        Serial.print("OK menu");
        }
        lastTick = millis();
        countDown = configuration.set_timer[idx[1]] * 60;
        //        exe_dim = configuration.set_power[idx[0]] * 64.395 - 47.997;
        Serial.println("DIMER = " + (String)exe_dim);
        mainMenuPos = 2;
        dimmer.set(exe_dim);
        //        delay(2000);
        break;
      }
      settingScreen(configuration.set_power[idx[0]], configuration.set_timer[idx[1]]);
      break;
    case 2: //RUNNING MODE
      float current_output, previous_output;
      float alpha = 0.5;

      while (1) {
        unsigned long currentMillis = millis();
        if (currentMillis - lastTick >= 1000) {
          countDown--;
          lastTick += 1000;


          float luxx = lightMeter.readLightLevel() * 0.0015;
          float temp = mySensorB.readTempC();
          int pos_x;
          int pos_string = 12;
          int offset_t = 10;
          int mins = countDown / 60;
          int secs = countDown % 60;
          if (mins == 0 && secs == 0) {
            mainMenuPos = 1;
            dimmer.set(0);
            break;
          }
          float current_input = luxx;
          current_output  = alpha * current_input + (1 - alpha) * previous_output;
          previous_output = current_output;
          char c[10];

          myGLCD.clrScr();
          homeScreen();
          sensorDisplay(temp, luxx, mins, secs);
        }

      }

      break;
    case 3: // advance intensity
      break;
    case 4:
    default:
      break;
  }
}
