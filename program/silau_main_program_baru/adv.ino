boolean timerX(int x_start, int x_stop)
{
  boolean rtn = false;
  if (millis() - x_start >= x_stop) {
    rtn = true;
  }
  return rtn;
}

void doorSecurity(){
  if(digitalRead(3)){
    
  }
}
