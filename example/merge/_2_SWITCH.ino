/////////////////////////////////////////////////////// Part2 SWITCH

void updateEncoder() {

  lastencoderValue = encoderValue;

  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

void uiStep(void) {

  uiKeyCodeSecond = uiKeyCodeFirst;
  if (  digitalRead(uiKeySelect) == HIGH )
    uiKeyCodeFirst = KEY_SELECT;
  else if ( lastencoderValueUsed - encoderValue > 0 ) {
    lastencoderValueUsed = encoderValue;
    key_timer = 0;
    uiKeyCodeFirst = KEY_PREV;
  }
  else if ( lastencoderValueUsed - encoderValue < 0 ) {
    lastencoderValueUsed = encoderValue;
    key_timer = 0;
    uiKeyCodeFirst = KEY_NEXT;
  }
  else
    uiKeyCodeFirst = KEY_NONE;

  uiKeyCode = uiKeyCodeFirst;

}
void checkPowerOff() {
  if ( uiKeyCode == KEY_SELECT ) {
    key_timer ++;
    //    SerialUSB.print("key_timer :    "); // for power test
    //    SerialUSB.println(key_timer);
  }
  else {
    key_timer = 0;
  }
  if ( key_timer >= off_time ) {
    key_timer = 0;
    digitalWrite(PWR_Latch, LOW);
  }
}

/////////////////////////////////////////////////////// Part2 END

