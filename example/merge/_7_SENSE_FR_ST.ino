
/////////////////////////////////////////////////////// Part7 Sense

void getFret() {

  int line = 0;
  int fret = 0;
  sensing_notesCount = 0;
  unsigned int temp = 0;

  for (int j = 0; j < 4; j++) {
    digitalWrite(Latch_Sensing, LOW);
    delayMicroseconds(5);
    digitalWrite(Latch_Sensing, HIGH);
    for (int i = 0; i < 30 ; i++) {

      switch (j) {
        case 0: temp = digitalRead(Sens_Data1); break;
        case 1: temp = digitalRead(Sens_Data2); break;
        case 2: temp = digitalRead(Sens_Data3); break;
        case 3: temp = digitalRead(Sens_Data4); break;
      }

      if (temp) {

        line = i % 6 + 1;
        fret = i / 6 + 1 + (5 * j);
        //        fret = i / 6 + 1;

        sensing_notes[sensing_notesCount][0] = fret;
        sensing_notes[sensing_notesCount][1] = line;

        //        axis[0] = '(';
        //        axis[1] = '0' + fret / 10;
        //        axis[2] = '0' + fret % 10;
        //        axis[3] = ',';
        //        axis[4] = '0' + line;
        //        axis[5] = ')';
        //        axis[6] = '\0';

        //        record_arr[sensing_notesCount] = axis;
        //        SerialUSB.print("   --- fret index ---     ");
        //        SerialUSB.print(sensing_notes[sensing_notesCount][0]);
        //        SerialUSB.print("   ,  ");
        //        SerialUSB.println(sensing_notes[sensing_notesCount][1]);

        //        SerialUSB.println("   --- axis ---     ");
        //        SerialUSB.println(axis);

        sensing_notesCount++;

      }

      //set HIGH
      REG_PIOA_SODR = 0x1 << 4;
      //set LOW
      REG_PIOA_CODR = 0x1 << 4;
    }
  }

}


int getFretNo(int stringNo) {

  int line = 0;
  int fret = 0;
  int maxfret = 0;

  unsigned int temp = 0;

  for (int j = 0; j < 4; j++) {

    digitalWrite(Latch_Sensing, LOW);
    delayMicroseconds(5);
    digitalWrite(Latch_Sensing, HIGH);

    for (int i = 0; i < 30 ; i++) {

      switch (j) {
        case 0: temp = digitalRead(Sens_Data1); break;
        case 1: temp = digitalRead(Sens_Data2); break;
        case 2: temp = digitalRead(Sens_Data3); break;
        case 3: temp = digitalRead(Sens_Data4); break;
      }

      if (temp) {
        line = i % 6 + 1;
        fret = i / 6 + 1 + (5 * j);
      }

      if (line == stringNo && maxfret < fret) maxfret = fret;

      //set HIGH
      REG_PIOA_SODR = 0x1 << 4;
      //set LOW
      REG_PIOA_CODR = 0x1 << 4;

    }

  }

  return maxfret;

}

void sense_Note() {

  timeCount++; //시간의 흐름을 구하기 위함

  analog_Read();

  // string 1

  if (scan1 > (avg_scan1 + MAX_SCAN1) && stringFlag1 == false) {
    play_count1++;
  }

  if (play_count1 >= 25) {

    sTime = timeCount;
    play_count1 = 0;
    stringFlag1 = true;

  }

  if (scan1 > (avg_scan1 - 2) && scan1 < (avg_scan1 + 2) && stringFlag1 == true) count1++;
  if (scan1 > avg_scan1 + MID_SCAN1) count1 = 0;
  if (count1 >= 50 && scan1 > (avg_scan1 - 2) && scan1 < (avg_scan1 + 2) && stringFlag1 == true) {
    count1 = 0;
    stringFlag1 = false;
  }

  // string 2

  if (scan2 > (avg_scan2 + MAX_SCAN2) && stringFlag2 == false) {
    play_count2++;
  }

  if (play_count2 >= 25) {

    sTime = timeCount;
    play_count2 = 0;
    stringFlag2 = true;

  }

  if (scan2 > (avg_scan2 - 2) && scan2 < (avg_scan2 + 2) && stringFlag2 == true) count2++;
  if (scan2 > (avg_scan2 + MID_SCAN2)) count2 = 0;
  if (count2 >= 100 && scan2 > (avg_scan2 - 2) && scan2 < (avg_scan2 + 2) && stringFlag2 == true) {
    count2 = 0;
    stringFlag2 = false;
  }


  // string 3

  if (scan3 > (avg_scan3 + MAX_SCAN3) && stringFlag3 == false) {
    play_count3++;
  }

  if (play_count3 >= 25) {

    sTime = timeCount;
    play_count3 = 0;
    stringFlag3 = true;

  }

  if (scan3 > (avg_scan3 - 2) && scan3 < (avg_scan3 + 2) && stringFlag3 == true) count3++;
  if (scan3 > (avg_scan3 + MID_SCAN3)) count3 = 0;
  if (count3 >= 50 && scan3 > (avg_scan3 - 2) && scan3 < (avg_scan3 + 2) && stringFlag3 == true) {
    count3 = 0;
    stringFlag3 = false;
  }


  // string 4

  if (scan4 > (avg_scan4 + MAX_SCAN4) && stringFlag4 == false) {
    play_count4++;
  }

  if (play_count4 >= 25) {

    sTime = timeCount;
    play_count4 = 0;
    stringFlag4 = true;

  }

  if (scan4 > (avg_scan4 - 2) && scan4 < (avg_scan4 + 2) && stringFlag4 == true) count4++;
  if (scan4 > (avg_scan4 + MID_SCAN4)) count4 = 0;
  if (count4 >= 50 && scan4 > (avg_scan4 - 2) && scan4 < (avg_scan4 + 2) && stringFlag4 == true) {
    count4 = 0;
    stringFlag4 = false;
  }


  // string 5

  if (scan5 > (avg_scan5 + MAX_SCAN5) && stringFlag5 == false) {
    play_count5++;
  }

  if (play_count5 >= 25) {

    sTime = timeCount;
    play_count5 = 0;
    stringFlag5 = true;

  }

  if (scan5 > (avg_scan5 - 2) && scan5 < (avg_scan5 + 2) && stringFlag5 == true) count5++;
  if (scan5 > (avg_scan5 + MID_SCAN5)) count5 = 0;
  if (count5 >= 50 && scan5 > (avg_scan5 - 2) && scan5 < (avg_scan5 + 2) && stringFlag5 == true) {
    count5 = 0;
    stringFlag5 = false;
  }


  // string 6

  if (scan6 > (avg_scan6 + MAX_SCAN6) && stringFlag6 == false) {
    play_count6++;
  }

  if (play_count6 >= 25) {

    sTime = timeCount;
    play_count6 = 0;
    stringFlag6 = true;

  }

  if (scan6 > (avg_scan6 - 2) && scan6 < (avg_scan6 + 2) && stringFlag6 == true) count6++;
  if (scan6 > (avg_scan6 + MID_SCAN6)) count6 = 0;

  if (count6 >= 50 && scan6 > (avg_scan6 - 2) && scan6 < (avg_scan6 + 2) && stringFlag6 == true) {
    count6 = 0;
    stringFlag6 = false;
  }

  sense_note_LED();

}

void record_sense_Note() {

  timeCount++; //시간의 흐름을 구하기 위함

  analog_Read();

  // string 1

  if (scan1 > (avg_scan1 + MAX_SCAN1) && stringFlag1 == false) {
    play_count1++;
  }

  if (play_count1 >= 25) {

    sTime = timeCount;
    play_count1 = 0;
    stringFlag1 = true;
    
    record_note[noteIndex].startTime = timeCount;
    record_note[noteIndex].noteFret = getFretNo(1);
    record_note[noteIndex].noteString = 1;
    setNote( record_note[noteIndex].noteString, record_note[noteIndex].noteFret );

    SerialUSB.print("[Fret,String]   :   ");
    SerialUSB.print(record_note[noteIndex].noteFret);
    SerialUSB.print(" , ");
    SerialUSB.println(record_note[noteIndex].noteString);
    SerialUSB.println("");

    noteIndex++;

  }

  if (scan1 > (avg_scan1 - 2) && scan1 < (avg_scan1 + 2) && stringFlag1 == true) count1++;
  if (scan1 > avg_scan1 + MID_SCAN1) count1 = 0;

  if (count1 >= 50 && scan1 > (avg_scan1 - 2) && scan1 < (avg_scan1 + 2) && stringFlag1 == true) {
    count1 = 0;
    stringFlag1 = false;
    record_note[noteIndex].endTime = timeCount;
  }


  // string 2

  if (scan2 > (avg_scan2 + MAX_SCAN2) && stringFlag2 == false) {
    play_count2++;
  }

  if (play_count2 >= 25) {

    sTime = timeCount;
    play_count2 = 0;
    stringFlag2 = true;
    
    record_note[noteIndex].startTime = timeCount;
    record_note[noteIndex].noteFret = getFretNo(2);
    record_note[noteIndex].noteString = 2;
    setNote( record_note[noteIndex].noteString, record_note[noteIndex].noteFret );

    SerialUSB.print("[Fret,String]   :   ");
    SerialUSB.print(record_note[noteIndex].noteFret);
    SerialUSB.print(" , ");
    SerialUSB.println(record_note[noteIndex].noteString);
    SerialUSB.println("");

    noteIndex++;

  }

  if (scan2 > (avg_scan2 - 2) && scan2 < (avg_scan2 + 2) && stringFlag2 == true) count2++;
  if (scan2 > (avg_scan2 + MID_SCAN2)) count2 = 0;

  if (count2 >= 50 && scan2 > (avg_scan2 - 2) && scan2 < (avg_scan2 + 2) && stringFlag2 == true) {
    count2 = 0;
    stringFlag2 = false;
    record_note[noteIndex].endTime = timeCount;
  }


  // string 3

  if (scan3 > (avg_scan3 + MAX_SCAN3) && stringFlag3 == false) {
    play_count3++;
  }

  if (play_count3 >= 25) {

    sTime = timeCount;
    play_count3 = 0;
    stringFlag3 = true;
    
    record_note[noteIndex].startTime = timeCount;
    record_note[noteIndex].noteFret = getFretNo(3);
    record_note[noteIndex].noteString = 3;
    setNote( record_note[noteIndex].noteString, record_note[noteIndex].noteFret );

    SerialUSB.print("[Fret,String]   :   ");
    SerialUSB.print(record_note[noteIndex].noteFret);
    SerialUSB.print(" , ");
    SerialUSB.println(record_note[noteIndex].noteString);
    SerialUSB.println("");

    noteIndex++;

  }

  if (scan3 > (avg_scan3 - 2) && scan3 < (avg_scan3 + 2) && stringFlag3 == true) count3++;
  if (scan3 > (avg_scan3 + MID_SCAN3)) count3 = 0;

  if (count3 >= 50 && scan3 > (avg_scan3 - 2) && scan3 < (avg_scan3 + 2) && stringFlag3 == true) {
    count3 = 0;
    stringFlag3 = false;
    record_note[noteIndex].endTime = timeCount;
  }


  // string 4

  if (scan4 > (avg_scan4 + MAX_SCAN4) && stringFlag4 == false) {
    play_count4++;
  }

  if (play_count4 >= 25) {

    sTime = timeCount;
    play_count4 = 0;
    stringFlag4 = true;

    record_note[noteIndex].startTime = timeCount;
    record_note[noteIndex].noteFret = getFretNo(4);
    record_note[noteIndex].noteString = 4;
    setNote( record_note[noteIndex].noteString, record_note[noteIndex].noteFret );

    SerialUSB.print("[Fret,String]   :   ");
    SerialUSB.print(record_note[noteIndex].noteFret);
    SerialUSB.print(" , ");
    SerialUSB.println(record_note[noteIndex].noteString);
    SerialUSB.println("");

    noteIndex++;

  }

  if (scan4 > (avg_scan4 - 2) && scan4 < (avg_scan4 + 2) && stringFlag4 == true) count4++;
  if (scan4 > (avg_scan4 + MID_SCAN4)) count4 = 0;

  if (count4 >= 50 && scan4 > (avg_scan4 - 2) && scan4 < (avg_scan4 + 2) && stringFlag4 == true) {
    count4 = 0;
    stringFlag4 = false;
    record_note[noteIndex].endTime = timeCount;
  }


  // string 5

  if (scan5 > (avg_scan5 + MAX_SCAN5) && stringFlag5 == false) {
    play_count5++;
  }

  if (play_count5 >= 25) {

    sTime = timeCount;
    play_count5 = 0;
    stringFlag5 = true;
    
    record_note[noteIndex].startTime = timeCount;
    record_note[noteIndex].noteFret = getFretNo(5);
    record_note[noteIndex].noteString = 5;
    setNote( record_note[noteIndex].noteString, record_note[noteIndex].noteFret );

    SerialUSB.print("[Fret,String]   :   ");
    SerialUSB.print(record_note[noteIndex].noteFret);
    SerialUSB.print(" , ");
    SerialUSB.println(record_note[noteIndex].noteString);
    SerialUSB.println("");

    noteIndex++;

  }

  if (scan5 > (avg_scan5 - 2) && scan5 < (avg_scan5 + 2) && stringFlag5 == true) count5++;
  if (scan5 > (avg_scan5 + MID_SCAN5)) count5 = 0;

  if (count5 >= 50 && scan5 > (avg_scan5 - 2) && scan5 < (avg_scan5 + 2) && stringFlag5 == true) {
    count5 = 0;
    stringFlag5 = false;
    record_note[noteIndex].endTime = timeCount;
  }


  // string 6

  if (scan6 > (avg_scan6 + MAX_SCAN6) && stringFlag6 == false) {
    play_count6++;
  }

  if (play_count6 >= 25) {

    sTime = timeCount;
    play_count6 = 0;
    stringFlag6 = true;
    
    record_note[noteIndex].startTime = timeCount;
    record_note[noteIndex].noteFret = getFretNo(6);
    record_note[noteIndex].noteString = 6;
    setNote( record_note[noteIndex].noteString, record_note[noteIndex].noteFret );

    SerialUSB.print("[Fret,String]   :   ");
    SerialUSB.print(record_note[noteIndex].noteFret);
    SerialUSB.print(" , ");
    SerialUSB.println(record_note[noteIndex].noteString);
    SerialUSB.println("");

    noteIndex++;

  }

  if (scan6 > (avg_scan6 - 2) && scan6 < (avg_scan6 + 2) && stringFlag6 == true) count6++;
  if (scan6 > (avg_scan6 + MID_SCAN6)) count6 = 0;

  if (count6 >= 50 && scan6 > (avg_scan6 - 2) && scan6 < (avg_scan6 + 2) && stringFlag6 == true) {
    count6 = 0;
    stringFlag6 = false;
    record_note[noteIndex].endTime = timeCount;
  }

  sense_note_LED();

}


void analog_Read() {

  //    while ((ADC->ADC_ISR & 0x3C30) != 0x3C30); // wait for conversion

  //1

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0020;     // use channels 5, 4, 10~13 , Channel Enable Register


  while ((ADC->ADC_ISR & 0x0020) != 0x0020); // wait for conversion

  scan1 = ADC->ADC_CDR[5]; //get values from Channel Date Register


  //2

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0010;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x0010) != 0x0010); // wait for conversion

  scan2 = ADC->ADC_CDR[4]; //get values from Channel Date Register

  //3

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0400;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x0400) != 0x0400); // wait for conversion

  scan3 = ADC->ADC_CDR[10]; //get values from Channel Date Register

  //4

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0800;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x0800) != 0x0800); // wait for conversion

  scan4 = ADC->ADC_CDR[11]; //get values from Channel Date Register

  //5

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x1000;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x1000) != 0x1000); // wait for conversion

  scan5 = ADC->ADC_CDR[12]; //get values from Channel Date Register

  //6

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x2000;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x2000) != 0x2000); // wait for conversion

  scan6 = ADC->ADC_CDR[13]; //get values from Channel Date Register

}

void sense_note_LED() {

  sensing_notesCount = 0;

  if (stringFlag1 == true) {
    sensing_notes[sensing_notesCount][0] = getFretNo(1);
    sensing_notes[sensing_notesCount][1] = 1;
    sensing_notesCount++;
  }

  if (stringFlag2 == true) {
    sensing_notes[sensing_notesCount][0] = getFretNo(2);
    sensing_notes[sensing_notesCount][1] = 2;
    sensing_notesCount++;
  }

  if (stringFlag3 == true) {
    sensing_notes[sensing_notesCount][0] = getFretNo(3);
    sensing_notes[sensing_notesCount][1] = 3;
    sensing_notesCount++;
  }

  if (stringFlag4 == true) {
    sensing_notes[sensing_notesCount][0] = getFretNo(4);
    sensing_notes[sensing_notesCount][1] = 4;
    sensing_notesCount++;
  }

  if (stringFlag5 == true) {
    sensing_notes[sensing_notesCount][0] = getFretNo(5);
    sensing_notes[sensing_notesCount][1] = 5;
    sensing_notesCount++;
  }

  if (stringFlag6 == true) {
    sensing_notes[sensing_notesCount][0] = getFretNo(6);
    sensing_notes[sensing_notesCount][1] = 6;
    sensing_notesCount++;
  }

}

void Do_calibration() {


  //    while ((ADC->ADC_ISR & 0x3C30) != 0x3C30); // wait for conversion

  //1

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0020;     // use channels 5, 4, 10~13 , Channel Enable Register


  while ((ADC->ADC_ISR & 0x0020) != 0x0020); // wait for conversion

  scan1 += ADC->ADC_CDR[5]; //get values from Channel Date Register


  //2

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0010;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x0010) != 0x0010); // wait for conversion

  scan2 += ADC->ADC_CDR[4]; //get values from Channel Date Register

  //3

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0400;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x0400) != 0x0400); // wait for conversion

  scan3 += ADC->ADC_CDR[10]; //get values from Channel Date Register

  //4

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x0800;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x0800) != 0x0800); // wait for conversion

  scan4 += ADC->ADC_CDR[11]; //get values from Channel Date Register

  //5

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x1000;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x1000) != 0x1000); // wait for conversion

  scan5 += ADC->ADC_CDR[12]; //get values from Channel Date Register

  //6

  ADC->ADC_CHDR = 0x3CFF; // disable all channels , Channel Disable Register
  ADC->ADC_CHER = 0x2000;     // use channels 5, 4, 10~13 , Channel Enable Register

  while ((ADC->ADC_ISR & 0x2000) != 0x2000); // wait for conversion

  scan6 += ADC->ADC_CDR[13]; //get values from Channel Date Register

  sample_count++;

}
/////////////////////////////////////////////////////// Part7 END
