/////////////////////////////////////////////////////// Part3 OLED for drawing menu

//void drawMainMenu() {
//
//  display.setTextSize(1);
//  display.setTextColor(2);
//
//  for (int i = 0; i < menu_count; i++) {
//
//    if ( i == menu_current ) display.fillRect(0, display.height() / 6 * (i + 1), display.width(), display.height() / 6, 1);
//
//    display.setCursor(5, (display.height() / 6) * (i + 1) + 1);
//    display.println(main_strings[i]);
//
//  }
//  display.display();
//  display.clearDisplay();
//
//}

void drawMainMenu() {

  display.fillRoundRect(-5, 25, 86, display.height() / 6 + 4, 7, 1);
  display.drawLine(84, 2, 84, display.height() - 2, 1);
  display.drawBitmap(115, 0,  bluetoothbmp, 12, 12, 1);

  switch (menu_current) {

    case 0:  display.drawBitmap(88, 13,  play_list_bmp, 40, 40, 1); break;
    case 1:  display.drawBitmap(88, 13,  guitar_chord_bmp, 40, 40, 1); break;
    case 2:  display.drawBitmap(88, 13,  live_play_bmp, 40, 40, 1); break;
    case 3:  display.drawBitmap(88, 13,  record_bmp, 40, 40, 1); break;
    case 4:  display.drawBitmap(88, 13,  file_manager_bmp, 40, 40, 1); break;
    case 5:  display.drawBitmap(88, 13,  format_bmp, 40, 40, 1); break;
    case 6:  display.drawBitmap(88, 13,  setting_bmp, 40, 40, 1); break;

  }

  display.setTextSize(1);
  display.setTextColor(2);

  if (menu_current == 0) {

    display.setCursor(3, 13);
    display.println(main_strings[MAIN_ITEMS - 1]);
    display.setCursor(3, 28);
    display.println(main_strings[menu_current]);
    display.setCursor(3, 43);
    display.println(main_strings[menu_current + 1]);

  }
  else if (menu_current == MAIN_ITEMS - 1) {

    display.setCursor(3, 13);
    display.println(main_strings[menu_current - 1]);
    display.setCursor(3, 28);
    display.println(main_strings[menu_current]);
    display.setCursor(3, 43);
    display.println(main_strings[0]);

  }
  else {

    display.setCursor(3, 13);
    display.println(main_strings[menu_current - 1]);
    display.setCursor(3, 28);
    display.println(main_strings[menu_current]);
    display.setCursor(3, 43);
    display.println(main_strings[menu_current + 1]);

  }

  //  display.fillTriangle(84, 26,
  //                       82, 28,
  //                       84, 30,1);

  display.display();
  display.clearDisplay();

}

void drawListMenu() {

  uint8_t max_menu = 5;
  menu_count = song_count;

  display.setTextSize(1);
  display.setTextColor(2);

  if (menu_count > 4) {
    is_scroll = 1; // default is_scroll = 0
    // menu_count를 4로 나눠서 나머지가 있으면, 스크롤이 하나 더 필요할 것.
    scroll_count = menu_count / 4 + ((menu_count % 4 == 0) ? 0 : 1);
  } else is_scroll = 0;

  if (scroll_current == scroll_count - 1 && (menu_count % 4 != 0 )) max_menu = menu_count % 4 + 1; // default scroll_current = 0, default scroll_count = 0, default max_menu = 5

  if (is_scroll == 1) {
    for (int i = 0; i < max_menu; i++) {
      if ( i == menu_current ) display.fillRect(0, display.height() / 6 * (i + 1), display.width(), display.height() / 6, 1);

      display.setCursor(5, (display.height() / 6) * (i + 1) + 1);

      if (i == 0) display.println("Back");
      else display.println(songList[i - 1 + 4 * scroll_current].title);

    }
    if (scroll_current < scroll_count - 1) max_current = 5;
    else max_current = max_menu;

  }
  else {
    for (int i = 0; i < 3; i++ ) {
      if ( i == menu_current ) display.fillRect(0, display.height() / 6 * (i + 1), display.width(), display.height() / 6, 1);

      display.setCursor(5, (display.height() / 6) * (i + 1) + 1);

      if ( i == 0 ) display.println("Back");
      else display.println(songList[i - 1].title);

    }
    max_current = menu_count + 1;
  }

  display.display();
  display.clearDisplay();

}

void drawPlayMenu() {

  uint8_t bx, ax;

  display.setFont(&FreeSerifItalic9pt7b);
  display.setTextSize(1);
  display.setTextColor(2);
  display.setCursor(5, 16);
  display.println(songList[song_index - 1].title);

  display.setFont();
  display.setTextSize(1);
  display.setTextColor(2);
  display.setCursor(5, display.height() / 4 + 7);
  display.println(rArtist);

  makeTime(printTime_for_play, play_Time);
  display.setTextSize(1);
  display.setTextColor(2);
  display.setCursor(57, display.height() / 4 + 17);
  display.println(printTime_for_play);
  display.setCursor(87, display.height() / 4 + 17);
  display.println("/");
  makeTime(printTime, total_Time);
  display.setCursor(93, display.height() / 4 + 17);
  display.println(printTime);

  display.drawRect(5, display.height() / 4 + 28, 118, 6, 2);


  switch ( repeat_status ) {
    case NONE: break;
    case SET_B:

      if ( repeat_end_time < repeat_start_time ) { //항상 A < B 가 되도록 설정해주자
        long temp = repeat_start_time;
        repeat_start_time = repeat_end_time;
        repeat_end_time = temp;
      }
      if ( play_Time + 200 >= repeat_end_time ) play_Time = repeat_end_time; //보정: 깔끔하게 채우자 200ms 정도남았으면...

      bx = (118.0 * repeat_end_time / total_Time) + 5;

      display.drawLine(bx, display.height() / 4 + 26, bx, display.height() / 4 + 35, 1);

      display.setCursor(5, display.height() * 3 / 4 + 7);
      display.println("repeat A-B");

    case SET_A:
      ax = (118.0 * repeat_start_time / total_Time) + 5;

      display.drawLine(ax, display.height() / 4 + 26, ax, display.height() / 4 + 35, 1);

      if ( repeat_status == SET_B) break;
      display.setCursor(5, display.height() * 3 / 4 + 7);
      display.println("repeat A-");
      break;
  }

  if ( repeat_status == NONE ) display.fillRect(5, display.height() / 4 + 28, 118.0 * play_Time / total_Time, 6, 1);
  else display.fillRect(ax, display.height() / 4 + 28, 118.0 * (play_Time - repeat_start_time) / total_Time, 6, 1);

  display.setCursor(95, display.height() * 3 / 4 + 7);
  display.println(tempo_string);

  display.display();
  display.clearDisplay();

}

void drawPauseMenu() {

  display.setTextSize(1);
  display.setTextColor(2);

  for (int i = 0; i < menu_count; i++) {

    if ( i == menu_current ) display.fillRect(0, display.height() / 6 * (i + 1), display.width(), display.height() / 6, 1);

    display.setCursor(5, (display.height() / 6) * (i + 1) + 1);
    display.println(pause_strings[i]);

    if ( i == 2 ) {
      display.setCursor(50, (display.height() / 6) * (i + 1) + 1);
      display.println(tempo_string);
    }


  }

  display.display();
  display.clearDisplay();

}

//void drawChordMenu() {
//
//  display.setTextSize(1);
//  display.setTextColor(2);
//  display.setCursor(2, 2);
//  display.println("SELECT CHORD");
//
//  display.fillRect(display.width() / 4, 5 + 8, display.width() / 4 * 2, display.height() - 5 - 8, 1);
//
//  if (menu_current == 0) {
//    display.setTextSize(6);
//    display.setTextColor(2);
//    display.setCursor(display.width() / 4 + 17, 40);
//    display.println(chord_strings[0]);
//  } else {
//    display.setTextSize(6);
//    display.setTextColor(2);
//    display.setCursor(display.width() / 4 + 17, 18);
//    display.println(chord_strings[menu_current]);
//  }
//
//  if (menu_current == 7) {
//    display.setTextSize(3);
//    display.setTextColor(2);
//    display.setCursor(display.width() * 3 / 4 + 10, display.height() / 4 + 26);
//    display.println(chord_strings[0]);
//  } else {
//    display.setTextSize(3);
//    display.setTextColor(2);
//    display.setCursor(display.width() * 3 / 4 + 10, display.height() / 4 + 13);
//    display.println(chord_strings[menu_current + 1]);
//  }
//
//  if (menu_current == 0) {
//    display.setTextSize(3);
//    display.setTextColor(2);
//    display.setCursor(7, display.height() / 4 + 13);
//    display.println(chord_strings[CHORD_ITEMS - 1]);
//  }
//  else if (menu_current == 1) {
//    display.setTextSize(3);
//    display.setTextColor(2);
//    display.setCursor(7, display.height() / 4 + 26);
//    display.println(chord_strings[menu_current - 1]);
//  }
//  else {
//    display.setTextSize(3);
//    display.setTextColor(2);
//    display.setCursor(7, display.height() / 4 + 13);
//    display.println(chord_strings[menu_current - 1]);
//  }
//
//  display.display();
//  display.clearDisplay();
//
//}

void drawChordMenu() {

  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(1, 2);
  display.println("SELECT CHORD");

  if (mymenu == CHORD_MENU) {

    display.fillTriangle(11, 15, 6, 20, 16, 20, 1);
    display.fillTriangle(11, 49, 6, 44, 16, 44, 1);
    display.drawRect(0, 13, 23, 40, 2);

    display.setTextSize(1);
    display.setTextColor(1);
    display.setFont(&FreeSerifBold12pt7b);
    display.setCursor(3, display.height() / 2 + 8);
    if (menu_current == 0) display.drawBitmap(2, display.height() / 2 - 9, backbmp, 20, 18, 1);
    else display.println(chord_strings[menu_current]);

    display.setFont(&FreeSerifBold9pt7b);

    for (int i = 0; i < 6; i++) {

      if (i == 0) display.setCursor(34, 28);
      else if (i == 1) display.setCursor(63, 28);
      else if (i == 2) display.setCursor(101, 28);
      else if (i == 3) display.setCursor(37, 48);
      else if (i == 4) display.setCursor(68, 48);
      else if (i == 5) display.setCursor(99, 48); // 1 to 6

      display.println(subchord_strings[menu_current][i]);

    }

    display.setFont();

  }
  else {

    display.fillRect(0, 13, 23, 40, 2);
    display.drawRect(2, 15, 19, 36, 2);
    display.setTextSize(1);
    display.setTextColor(2);
    display.setFont(&FreeSerifBold12pt7b);
    display.setCursor(3, display.height() / 2 + 8);
    display.println(chord_strings[chord_current]);

    if (menu_current <= 2) {
      display.drawRect(23 + 35 * menu_current, 13, 35, 20, 1);
    }
    else if (menu_current <= 5) {
      display.drawRect(23 + 35 * (menu_current % 3), 33, 35, 20, 1);
    }
    else if (menu_current <= 8) {
      display.drawRect(23 + 35 * (menu_current % 6), 13, 35, 20, 1);
    }
    else if (menu_current <= 10) {
      display.drawRect(23 + 35 * (menu_current % 9) , 33, 35, 20, 1);
    }

    display.setTextColor(1);
    display.setFont(&FreeSerifBold9pt7b);

    if (menu_current <= 5) {

      for (int i = 0; i <= 5; i++) {
        if (i == 0) display.setCursor(34, 28);
        else if (i == 1) display.setCursor(63, 28);
        else if (i == 2) display.setCursor(101, 28);
        else if (i == 3) display.setCursor(37, 48);
        else if (i == 4) display.setCursor(68, 48);
        else if (i == 5) display.setCursor(99, 48);

        display.println(subchord_strings[chord_current][i]);
      }

    }
    else {

      for (int i = 0; i <= 4; i++) {
        if (i == 0) display.setCursor(33, 28);
        else if (i == 1) display.setCursor(64, 28);
        else if (i == 2) display.setCursor(96, 28);
        else if (i == 3) display.setCursor(26, 48);
        else if (i == 4) display.drawBitmap(66, 34, backbmp, 20, 18, 1);

        display.println(subchord_strings[chord_current][i + 6]);
      }

    }

    display.setFont();
    display.setTextSize(1);
    display.setTextColor(1);
    display.setCursor(107, 57);

    if (menu_current <= 5) display.println("1/2");
    else display.println("2/2");

  }

  display.display();
  display.clearDisplay();

}

void drawRecordMenu() {

  display.setTextSize(1);
  display.setTextColor(2);
  display.setCursor(1, 2);
  display.println("RECORD SELECT");

  if (menu_current == 0)  display.fillRect(display.width() / 4 - 18, 33, 40, 15, 1); else display.drawRect(display.width() / 4 - 18, 33, 40, 15, 1);
  display.setCursor(display.width() / 4 - 9, 37);
  display.println("BACK");
  if (menu_current == 1)  display.fillRect(display.width() * 3 / 4 - 18, 33, 40, 15, 1); else display.drawRect(display.width() * 3 / 4 - 18, 33, 40, 15, 1);
  display.setCursor(display.width() * 3 / 4 - 15, 37);
  display.println("RECORD");

  display.display();
  display.clearDisplay();

}

void drawPlayRecordMenu() {

  display.setTextSize(1);
  display.setTextColor(2);
  display.setCursor(1, 2);
  display.println("REC..");

  if (menu_current == 0)  display.fillRect(0, 52, 37, 12, 1); else display.drawRect(0, 52, 37, 12, 1);
  if (menu_current == 1)  display.fillRect(91, 52, 37, 12, 1); else display.drawRect(91, 52, 37, 12, 1);

  if (record_status == 1) {
    display.setCursor(4, 54);
    display.println("PAUSE");
  } else if (record_status == 0) {
    display.setCursor(1, 54);
    display.println("RESUME");
  }
  display.setCursor(98, 54);
  display.println("SAVE");

  display.drawCircle(63, 29, 24, 1);
  display.drawCircle(63, 29, 22, 1);
  if (record_status == 1) display.fillCircle(63, 29, 7, 1); else if (record_status == 0) {
    display.fillRect(54, 19, 7, 21, 1);
    display.fillRect(66, 19, 7, 21, 1);
  }

  display.display();
  display.clearDisplay();

}

void drawSettingMenu() {

  display.setTextSize(1);
  display.setTextColor(2);

  for (int i = 0; i < menu_count; i++) {

    if ( i == menu_current ) display.fillRect(0, display.height() / 6 * (i + 1), display.width(), display.height() / 6, 1);

    display.setCursor(5, (display.height() / 6) * (i + 1) + 1);
    display.println(setting_strings[i]);

  }
  display.display();
  display.clearDisplay();

}

void drawCalibration() {


  if (sample_count >= 1000) {
    display.setCursor(1, 50);
    display.println("--- COMPLETE !!");
    display.display();
    delay(1000);

    display.clearDisplay();
    menu_redraw_required = 1;
  }
  else {
    display.setTextSize(1);
    display.setTextColor(2);
    display.setCursor(1, 2);
    display.println("Start Calibration !!");
    display.display();
    delay(1000);
    display.setCursor(1, 12);
    display.println("For Accuracy, Please,");
    display.setCursor(1, 22);
    display.println("DO NOT TOUCH !!");
    display.setCursor(1, 32);
    display.println("ANY STRINGS !!");
    display.display();
    delay(1500);
  }

}

void drawSubMenu() {

  display.setTextSize(2);
  display.setTextColor(2);

  switch (mymenu) {

    case LIVEPLAY_MENU:
      display.setCursor(5, (display.height() / 2) - 5);
      display.println("Playing...");
      break;
    case DOWNLOAD_MENU:
      display.setCursor(5, (display.height() / 2) - 5);
      display.println("Waiting...");
      break;
    case FORMAT_MENU:
      display.setCursor(2, (display.height() / 2) - 5);
      display.println("formatting");
      break;

  }

  display.display();
  display.clearDisplay();

}

void makeTime ( char* display_time, long playtime ) { // modified by SEOL
  int printMinute, printSecond;
  playtime = playtime / 1000;      // 전체 초
  if ( playtime > 5940 ) {
    printMinute = 99;
    printSecond = 99; // to show overflow state
  } else {
    printMinute = playtime / 60;     // 출력할 분
    printSecond = playtime % 60; // 출력할 초
  }
  display_time[0] = (char) ('0' + printMinute / 10);
  display_time[1] = (char) ('0' + printMinute % 10);
  display_time[2] = ':';
  display_time[3] = (char) ('0' + printSecond / 10);
  display_time[4] = (char) ('0' + printSecond % 10);
  display_time[5] = '\0';
}

/////////////////////////////////////////////////////// Part3 END
