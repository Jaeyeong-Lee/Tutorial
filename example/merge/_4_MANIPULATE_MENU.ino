/////////////////////////////////////////////////////// Part4 Manipulating menu

void updateMenu() {

  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) return;

  last_key_code = uiKeyCode;

  switch (uiKeyCode) {

    case KEY_NEXT:

      if (mymenu == PLAY_MENU) {

        move_Time += skip_Time;
        is_move_Time_updated = 1;

      }
      else {

        menu_current++;
        if (is_scroll) {
          if ( menu_current >= max_current && scroll_current >= scroll_count - 1 ) scroll_current = 0;
          else if (menu_current >= max_current && scroll_current <= scroll_count - 1) scroll_current++;
        }
        if ( menu_current >= max_current ) menu_current = 0;

      }

      menu_redraw_required = 1;
      break;

    case KEY_PREV:

      if (mymenu == PLAY_MENU) {

        if ( (play_Time - skip_Time) < 0 ) {
          move_Time -= play_Time;
        } else {
          move_Time -= skip_Time;
        }
        is_move_Time_updated = 1;

      }
      else {

        menu_current--;
        if (is_scroll) {
          if ( menu_current == 255 && (scroll_current == 0) ) {
            scroll_current = scroll_count - 1; // 마지막장

            if ( menu_count % (item_count - 1) == 0 ) {
              menu_current = (item_count - 1);
            } else
              menu_current = menu_count % (item_count - 1);
          }
          else if (menu_current == 255 && (scroll_current == scroll_count - 1)) {
            scroll_current--;
            menu_current = (item_count - 1);
          }
          else if (menu_current == 255) {
            scroll_current--;
            menu_current = max_current - 1 ;
          }
        }
        if ( menu_current == 255 ) menu_current = max_current - 1 ;

      }

      menu_redraw_required = 1;
      break;

    case KEY_SELECT:

      selectMenu();
      menu_redraw_required = 1;
      break;
  }
}

void updatePlayMenu() {

  is_move_Time_updated = 0;
  uiStep();
  updateMenu();

  currentMillis = millis();

  if ( (is_move_Time_updated == 1 || currentMillis - previousMillis > 1000)) {
    previousMillis = currentMillis;

    play_Time = currentMillis  - ((long)start_Time) - rest_Time + move_Time; // next_Time - prev_Time;

    menu_redraw_required = 1;
  }

  if ( menu_redraw_required != 0 ) {

    switch ( mymenu ) {

      case MAIN_MENU: Timer3.stop();  drawMainMenu(); break;
      case PLAY_MENU:
        if ( play_Time > total_Time) play_Time = total_Time;
        drawPlayMenu(); break;
      case PAUSE_MENU: drawPauseMenu(); break;

    }
    menu_redraw_required = 0;

  }

}

void selectMenu() {

  // by umin newcode
  if (mymenu == MAIN_MENU) { // in main menu

    switch (menu_current + 1) {
      case PLAYLIST_MENU:
        mymenu = PLAYLIST_MENU;
        item_count = PLAYLIST_ITEMS;
        SerialUSB.println("call getTitlesFromSDCard");
        scroll_current = 0;
        scroll_count = 0;
        is_scroll = 0;
        getTitlesFromSDCard();
        break;
      case CHORD_MENU:
        max_current = CHORD_ITEMS;
        item_count = CHORD_ITEMS;
        scroll_current = 0;
        scroll_count = 0;
        menu_current = 0;
        is_scroll = 0;
        mymenu = CHORD_MENU;
        break;
      case LIVEPLAY_MENU:
        mymenu = LIVEPLAY_MENU;
        is_liveplay = 1;
        break;
      case RECORD_MENU:
        mymenu = RECORD_MENU;
        menu_count = 2;
        max_current = menu_count;
        item_count = 2;
        scroll_current = 0;
        scroll_count = 0;
        menu_current = 0;
        is_scroll = 0;
        break;
      case DOWNLOAD_MENU:
        mymenu = DOWNLOAD_MENU;
        //        menu_Download();
        break;
      case FORMAT_MENU:
        mymenu = FORMAT_MENU;
        break;
      case SETTING_MENU:
        mymenu = SETTING_MENU;
        menu_count = SETTING_ITEMS;
        max_current = menu_count;
        item_count = SETTING_ITEMS;
        menu_current = 0;
        break;
    }

  }
  else if (mymenu == PLAYLIST_MENU) { // in playlist menu

    if (menu_current == 0) {
      mymenu = MAIN_MENU;
      menu_count = MAIN_ITEMS;
      max_current = menu_count;
      is_play = 0;
      scroll_current = 0;
      scroll_count = 0;
      is_scroll = 0;
    }
    else {
      mymenu = PLAY_MENU;
      song_index = menu_current + scroll_current * (item_count - 1);
      tempo_scale = 10;
      tempo_string[1] = '1';
      tempo_string[3] = '0';
      repeat_status = NONE;
    }

  }
  else if (mymenu == PLAY_MENU) {

    mymenu = PAUSE_MENU;
    menu_count = PAUSE_ITEMS;
    max_current = menu_count;
    item_count = PAUSE_ITEMS;

    stack.push(is_scroll);
    stack.push(scroll_count);
    stack.push(scroll_current);
    stack.push(menu_current);

    menu_current = 0;
    scroll_current = 0;
    scroll_count = 0;
    is_scroll = 0;

  }
  else if (mymenu == PAUSE_MENU) {

    if (menu_current == 0) {
      mymenu = PLAY_MENU;
      menu_count = PLAYLIST_ITEMS;
      max_current = menu_count;
      item_count = PLAYLIST_ITEMS;

      menu_current = stack.pop();
      scroll_current = stack.pop();
      scroll_count = stack.pop();
      is_scroll = stack.pop();

      rest_Time += ( millis() - pause_Time ) ;
    }
    else if (menu_current == 1) {
      mymenu = PLAY_MENU;
      menu_count = PLAYLIST_ITEMS;
      max_current = menu_count;
      item_count = PLAYLIST_ITEMS;

      menu_current = stack.pop();
      scroll_current = stack.pop();
      scroll_count = stack.pop();
      is_scroll = stack.pop();

      // repeat_status = SET_A SET_B NONE
      if ( repeat_status == NONE ) {
        repeat_start_time = play_Time;
        repeat_status = SET_A;
      } else if ( repeat_status == SET_A ) {
        repeat_end_time = play_Time;
        repeat_status = SET_B;
      } else {
        repeat_status = NONE;
      }

      rest_Time += ( millis() - pause_Time ) ;
    }
    else if (menu_current == 2) {

      tempo_scale--;
      if (tempo_scale == 0 ) tempo_scale = 12;
      tempo_string[1] = (char)('0' + tempo_scale / 10);
      tempo_string[3] = (char)('0' + tempo_scale % 10);

      TEMPO = original_TEMPO / (tempo_scale / 10.0);
      DURATION = original_DURATION / (tempo_scale / 10.0); // to change current notes' duration.
      total_Time = original_total_Time / (tempo_scale / 10.0);

      delta_play_Time = ((double)prev_play_Time / prev_total_Time * total_Time) - prev_play_Time;
      move_Time = original_move_Time +  delta_play_Time; // 플레이 타임도 이동해야하기 때문에 move_Time을 수정해줌 by SEOL - 9.12

      repeat_status = NONE; // 일단 구간반복 취소 시키자

    }
    else if (menu_current == 3) {
      mymenu = MAIN_MENU;
      menu_count = MAIN_ITEMS;
      max_current = menu_count;
      menu_current = 0;
      is_play = 0;
      scroll_current = 0;
      scroll_count = 0;
      is_scroll = 0;
    }

  }
  else if (mymenu == CHORD_MENU) {

    if (menu_current == 0) {
      menu_count = MAIN_ITEMS;
      max_current = menu_count;
      mymenu = MAIN_MENU;
      item_count = MAIN_ITEMS;
      menu_current = 1;
      scroll_current = 0;
      scroll_count = 0;
      is_scroll = 0;
    }
    else {
      menu_count = SUBCHORD_ITEMS;
      max_current = menu_count;
      mymenu = SUBCHORD_MENU;
      item_count = SUBCHORD_ITEMS;
      chord_current = menu_current;
      menu_current = 0;
    }

  }
  else if (mymenu == SUBCHORD_MENU) {

    if (menu_current == 10) {
      max_current = CHORD_ITEMS;
      item_count = CHORD_ITEMS;
      scroll_current = 0;
      scroll_count = 0;
      menu_current = 0;
      is_scroll = 0;
      mymenu = CHORD_MENU;
    }
    else {
      if (chord_current <= 6) chord_current++;
      else if (chord_current <= 7) chord_current = 1;
    }

  }
  else if (mymenu == RECORD_MENU) {

    if (menu_current == 0) {
      mymenu = MAIN_MENU;
      menu_count = MAIN_ITEMS;
      max_current = menu_count;
      menu_current = 3;
      is_play = 0;
      scroll_current = 0;
      scroll_count = 0;
      is_scroll = 0;
    }
    else {
      mymenu = PLAY_RECORD_MENU;
      menu_count = 2;
      max_current = menu_count;
      menu_current = 0;
      record_status = 1;
      play_Record();
    }

  }
  else if (mymenu == PLAY_RECORD_MENU) {

    if (menu_current == 0) {
      if (record_status == 1) record_status = 0; else if (record_status == 0) record_status = 1;
    }
    else {
      mymenu = RECORD_MENU;
      menu_current = 0;
      record_status = 0;
      makeRecordfile();
      for (int i = 0; i < 600; i++) {
        record_note[i].noteFret = 99;
        record_note[i].noteString = 99;
      }
    }

  }
  else if (mymenu == LIVEPLAY_MENU)      mymenu = MAIN_MENU;
  else if (mymenu == DOWNLOAD_MENU)      mymenu = MAIN_MENU;
  else if (mymenu == FORMAT_MENU)        mymenu = MAIN_MENU;
  else if (mymenu == SETTING_MENU) {

    if (menu_current == 0) {
      mymenu = MAIN_MENU;
      menu_count = MAIN_ITEMS;
      max_current = menu_count;
      is_play = 0;
      scroll_current = 0;
      scroll_count = 0;
      is_scroll = 0;
      menu_current = 6;
    }
    else if (menu_current == 3) {

      setting_calibration();

    }
    else {
      mymenu = MAIN_MENU;
      menu_count = MAIN_ITEMS;
      max_current = menu_count;
      is_play = 0;
      scroll_current = 0;
      scroll_count = 0;
      is_scroll = 0;
      menu_current = 6;
    }

  }

}

void menu_Download() {

  while ((ch = (char)Serial3.read()) != '#') {

    Serial.println(ch);
    delay(200);

    uiStep();
    updateMenu();
    checkPowerOff();
    if (mymenu == MAIN_MENU) break;
    //    if ( ch < 0 ) continue;
    if ( (int)ch == 255 ) continue;

    //    Serial.print(ch);

  }

  if (mymenu == DOWNLOAD_MENU) {

    Serial3.write("1");

    int char_index = 0;
    int enter_count = 0;

    while ( (ch = (char)Serial3.read()) != '#' ) {
      //      if ( ch < 0 ) continue;
      if ( (int)ch == 255 ) continue;

      //if( enter_count==0 && ch==' ') ch='_';
      rNote[char_index++] = ch;
      //      Serial.print(ch);

      if ( ch == '\n' ) {
        enter_count++;
        switch (enter_count) {
          case 1: if ( rNote[0] == 'E' && rNote[1] == 'O' && rNote[2] == 'M') break;
            strncpy( songList[song_count].title, rNote, char_index - 1);
            songList[song_count].title[char_index - 1] = '\0';
            //                                                Serial.print("  title len:  "); Serial.println(strlen( songList[song_count].title ));
            //                                                Serial.print("  title  "); Serial.print( songList[song_count].title ); Serial.println("]");

            break; // should set the size of the title??
          case 4: // end of each song
            rNote[char_index - 1] = '\0';
            char_index = 0;

            int result = fileSave(songList[song_count].title, rNote);
            if ( result == 1 ) {
              myFile = SD.open("SONGLIST.TXT", FILE_WRITE);
              while (myFile) {
                for (int j = 0; j < strlen(songList[song_count].title) ; j++) {
                  myFile.print(songList[song_count].title[j]);
                }
                myFile.print('\n');
                myFile.close();
              }
            }
            /////////////////////////////////////////////////////////
            song_count++;
            Serial3.write("1");
            enter_count = 0;
            //break;
        }
      }
      if (ch == '*') {
        Serial3.write("#");
        break;
      }
    }
    //    Serial.println("end of download");

    myFile = SD.open("SONGLIST.TXT", FILE_READ);
    if (myFile) {
      //        Serial.println("song list.txt file reading...");
      while (myFile.available()) { // test 파일의 내용을 시리얼 모니터에 출력한다.
        ch = myFile.read();
        SerialUSB.print(ch);
      }
      myFile.close();
    }

  }
}

void play_Record() {

  //  Timer4.start(1000);

  menu_redraw_required = 1;

  while (noteIndex < 600) {

    uiStep();
    updateMenu();
    checkPowerOff();

    if ( menu_redraw_required != 0 ) {
      drawPlayRecordMenu();
      menu_redraw_required = 0;
    }

    if (mymenu == RECORD_MENU) {
      //      Timer4.stop;
      break;
    }

    if ( record_status ) record_sense_Note();
    delay(0.75);

    if (sensing_notesCount > 0) {
      for (int j = 0; j < sensing_notesCount; j++) play(GREEN);
    }

  }

  mymenu = RECORD_MENU;

}

void setting_calibration() {

  drawCalibration();

  while (sample_count < 1000) {
    Do_calibration();
    delay(2);
  }

  avg_scan1 = scan1 / 1000;
  avg_scan2 = scan2 / 1000;
  avg_scan3 = scan3 / 1000;
  avg_scan4 = scan4 / 1000;
  avg_scan5 = scan5 / 1000;
  avg_scan6 = scan6 / 1000;

  //      SerialUSB.print("avg_scan1    :");
  //      SerialUSB.println(avg_scan1);
  //      SerialUSB.print("avg_scan2    :");
  //      SerialUSB.println(avg_scan2);
  //      SerialUSB.print("avg_scan3    :");
  //      SerialUSB.println(avg_scan3);
  //      SerialUSB.print("avg_scan4    :");
  //      SerialUSB.println(avg_scan4);
  //      SerialUSB.print("avg_scan5    :");
  //      SerialUSB.println(avg_scan5);
  //      SerialUSB.print("avg_scan6    :");
  //      SerialUSB.println(avg_scan6);
  //
  //      SerialUSB.println(); SerialUSB.println();
  //
  //      SerialUSB.print("max_scan1    :");
  //      SerialUSB.print(avg_scan1 + 40);
  //      SerialUSB.print("mid_scan1    :");
  //      SerialUSB.print(avg_scan1 + 20);
  //
  //      SerialUSB.println(); SerialUSB.println();
  
  drawCalibration();

  scan1 = 0;
  scan2 = 0;
  scan3 = 0;
  scan4 = 0;
  scan5 = 0;
  scan6 = 0;
  sample_count = 0;

}

/////////////////////////////////////////////////////// Part4 END
