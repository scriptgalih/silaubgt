void updateMenu() {
  switch (mainMenuPos) {
    case 1: //Home Screen
      if (1) {
        tick_1 = millis();
        if (!digitalRead(PB_INTENSITY)) {
          while (!digitalRead(PB_INTENSITY)) {
            if (timerX(tick_1, 3000) && last_tick) {
              advScren();
              while (!digitalRead(PB_INTENSITY))
                delay(1);
              mainMenuPos = 3;
              break;
            }
//            last_tick = timerX(tick_1, 3000);

          }
          idx[0]++;
          if (idx[0] >= 5)
            idx[0] = 0;

          exe_power = configuration.set_power[idx[0]];
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

          if(exe_power>=2 && idx[1] == 4){
            mainMenuPos = 4;
            break;
          }
          lastTick = millis();
          countDown = configuration.set_timer[idx[1]] * 60;
          exe_dim = exe_power * 64.395 - 47.997;
          Serial.println("DIMER = " + (String)exe_dim);
          mainMenuPos = 2;
          dimmer.set(exe_dim);
          //        delay(2000);
          break;
        }
        settingScreen(exe_power, configuration.set_timer[idx[1]]);
      }
      break;
    case 2: //RUNNING MODE
      if (1) {
        float current_output, previous_output;
        float alpha = 0.5;
        boolean last_door_state = false;
        digitalWrite(LM_DOOR, HIGH);

        while (1) {
          int door_state;
          int sum = 0;
          for (int x = 0; x <= 20; x++) {

            sum += digitalRead(LM_DOOR);

          }
          if (sum >= 5)
            door_state = true;
          else
            door_state = false;
          //          Serial.println(door_state);
          if ( door_state && !last_door_state) {
            dimmer.set(0);
            Serial.println("Bakekok pintu kebuka");
          } else if ( !door_state && last_door_state) {
            dimmer.set(exe_dim);
            Serial.println("Bakekok pintu ketutup");
          }
          last_door_state = door_state;
          unsigned long currentMillis = millis();

          if (currentMillis - lastTick >= 1000) {
            if (!door_state)
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
          delay(500);
        }

        break;
      }
    case 3: // advance intensity
      if (1) {
        if (!digitalRead(PB_INTENSITY)) {
          while (!digitalRead(PB_INTENSITY)) {
            delay(1);
          }
          exe_power += 0.1;
          if (exe_power >= 2)
            exe_power = 2;
          Serial.print("Intensity:");
          Serial.println(exe_power);
        }

        if (!digitalRead(PB_TIMER)) {
          while (!digitalRead(PB_TIMER)) {
            delay(1);
          }
          exe_power -= 0.1;
          if (exe_power <= 1)
            exe_power = 1;
          Serial.print("Intensity:");
          Serial.println(exe_power);
        }
        if (!digitalRead(PB_OK)) {
          while (!digitalRead(PB_OK)) {
            delay(1);
            //        Serial.print("OK menu");
          }
          settingScreen(exe_power, configuration.set_timer[idx[1]]);
          mainMenuPos = 1;

          break;
        }
        exe_dim = exe_power * 64.395 - 47.997;
        screenAdvPower(exe_power);
        break;
      }
    case 4:
    if(1){
      warningMSG();
      delay(2000);
      mainMenuPos = 1;
    }
    default:
      break;
  }
}
