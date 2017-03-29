color v2C(double vel, color curColor) {
  if (vel <= SLOW) {
    curColor.red = 255;
    curColor.grn = min(vel / CRAT, 255);
    curColor.blu = 0;
  }
  else if (vel <= MED) {
    curColor.red = max(255 - ((vel - SLOW) / CRAT), 0);
    curColor.grn = 255;
    curColor.blu = 0;
  }
  else if (vel <= FAST) {
    curColor.red = 0;
    curColor.grn = max(255 - ((vel - MED) / (CRAT * 2)), 0);
    curColor.blu = min((vel - MED) / (CRAT * 2), 0);
  }
  else
  {
    curColor.red = 0;
    curColor.grn = 0;
    curColor.blu = 255;
  }

  return {curColor.red, curColor.grn, curColor.blu};
}

/*Hall Sensor*/
void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
{
  half_revolutions++;
//  Serial.println("detect");
//  Serial.println(half_revolutions);
  ct_prev = ct;
  ct = millis();
  Serial.print("Time Difference: ");
  Serial.println(ct_prev - ct);
}

void updateVelocity()
{
//  rpm = 30 * 1000 / (millis() - timeold) * half_revolutions;
//  timeold = millis();
//  half_revolutions = 0;
//  velocity = 2 * WHEEL_RADIUS * 3.14 * rpm; // in cm/min
//  Serial.println("Speed (cm/min):");
//  Serial.println(velocity);
}

/*LED Strip*/
void lightAll(uint16_t stripNum, color curColor) //Lights all LEDS on strip (designated by stripNum; either 1 or 2)
{
  switch (stripNum) {
    case 1:
      for (int i = 0; i < numLED1; i++) {
        strip1.setPixelColor(i, curColor.red, curColor.grn, curColor.blu);
      }
      strip1.show();
      break;

    case 2:
      for (int i = 0; i < numLED2; i++) {
        strip2.setPixelColor(i, curColor.red, curColor.grn, curColor.blu);
      }
      strip2.show();
      break;
  }
}

void setBright(uint16_t lvl) //Sets brightness for both strips
{
  strip1.setBrightness(lvl);
  strip2.setBrightness(lvl);
}

void lightsOff() //Turns off all lights on both strips
{
  strip1.show();
  strip2.show();
}

/*void pulseBoth( uint16_t numPulses, color curColor) //Pulsates both strips
{
  for ( int n = 0; n < numPulses; n++) {
    for (int i = 0; i < max(numLED1, numLED2); i++)
    {
      if (i < numLED1) {
        strip1.setPixelColor(i, curColor.red, curColor.grn, curColor.blu);
      }
      if (i < numLED2) {
        strip2.setPixelColor(i, curColor.red, curColor.grn, curColor.blu);
      }
      strip1.show()
      strip2.show();
      delay(50);
    }
  }
}*/
