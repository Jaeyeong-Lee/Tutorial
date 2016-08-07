
/////////////////////////////////////////////////////// Part1 SETUP

// switch
void uiSetup(void) {

  // Rotary Switch`
  pinMode(uiKeySelect, INPUT);           // set pin to input
  //  digitalWrite(uiKeySelect, HIGH);       // turn on pullup resistors

  // configure input keys
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  attachInterrupt(encoderPin1, updateEncoder, CHANGE);
  attachInterrupt(encoderPin2, updateEncoder, CHANGE);

  // PWR, Charger LED
  pinMode(PWR_Latch, OUTPUT);
  pinMode(UNO_LED, OUTPUT);//arduino led
  digitalWrite(PWR_Latch, HIGH);

}

// OLED
void OLEDSetup(void) {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  display.clearDisplay();
  menu_redraw_required = 1;
}

//LED
void LEDBoardSetup(void) {

  // LED turn ON/OFF
  pinMode(ST_SHCP, OUTPUT);
  pinMode(ST_STCP, OUTPUT);
  pinMode(ST_DS, OUTPUT);
  pinMode(FR_SDI, OUTPUT);
  pinMode(FR_CLK, OUTPUT);
  pinMode(FR_LE, OUTPUT);
  pinMode(RED_LED_DIMM, OUTPUT);
  pinMode(GREEN_LED_DIMM, OUTPUT);

  // Sensing
  pinMode(Latch_Sensing, OUTPUT);
  pinMode(CK_Sensing, OUTPUT);
  pinMode(Sens_Data1, INPUT);
  pinMode(Sens_Data2, INPUT);
  pinMode(Sens_Data3, INPUT);
  pinMode(Sens_Data4, INPUT);

  displayLogo();
//  test_LED_scattering();
}

/////////////////////////////////////////////////////// Part1 END
