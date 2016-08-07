/////////////////////////////////////////////////////// Part5 LED Struct

void struct_Turn_on_LED(int i) {

  location = 0;
  DURATION = 0;
  TEMPO = 0;
  notesCount = 0;
  rest_Time = 0;
  move_Time = 0;
  play_Time = 0;

  if ( rNote[3] == '!' ) {
    int Cal_t = (rNote[0] - '0') * 100 + (rNote[1] - '0') * 10 + (rNote[2] - '0');
    TEMPO = 60000 / (double)Cal_t;
  } else {
    TEMPO = 750;
  }
  original_TEMPO = TEMPO; // by SEOL

  start_Time = millis();
  previousMillis = start_Time;
  //////////////////////////////////////////////// by SEOL - 9.12 곡의 전체 재생 시간은 rTime에 저장되어 있어야 함 calculate_total_playtime() 함수 쓰지 않기
  // 대신에 여기 함수 들어오기 전에 total_Time = atol(rTime); 이렇게 호출했을 것. 아니면 여기서 호출 // by SEOL 9.12
  //total_Time = calculate_total_playtime();
  //  SerialUSB.print("total_Time @ struct_Turn_on_LED(): "); SerialUSB.println(total_Time);

  for (int j = 4; j < strlen(rNote); j++) { // should use "strlen()" NOT sizeof

    ch = rNote[j];

    if (ch == 'W')           DURATION = TEMPO * 4;
    else if (ch == 'H')      DURATION = TEMPO * 2;
    else if (ch == 'Q')      DURATION = TEMPO * 1;
    else if (ch == 'E')      DURATION = TEMPO * 0.5;
    else if (ch == 'S')      DURATION = TEMPO * 0.25;
    //successive 3-note DURATION
    else if (ch == 'q')      DURATION = (TEMPO * 1) / 3.0;
    else if (ch == 'e')      DURATION = (TEMPO * 0.5) / 3.0;
    else if (ch == 's')      DURATION = (TEMPO * 0.25) / 3.0;
    else if (ch >= '0' && ch <= '9') {
      if (location > 0 )    location = location * 10 + ch - '0';
      else            location = ch - '0';
    }
    else if (ch == ',') {
      line = location;
      location = 0;
    }
    else if (ch == '-') { // a new note is identified
      fret = location;
      location = 0;

      notes[notesCount][0] = line;
      notes[notesCount][1] = fret;
      notesCount++;

    } else if (ch ==  '@') {

      original_DURATION = DURATION; //by SEOL
      stime = millis();
      //      Timer3.start(10000);
      Timer4.start(1000);

      do {

        updatePlayMenu();

        if (mymenu == PAUSE_MENU) stime = millis(); pause_Time = millis();
        if (mymenu == MAIN_MENU) return;

        //        if ( is_move_Time_updated == 1 )  break;

        for (int i = 0; i < notesCount; i++) {
          if (notes[i][1] == 0) { // open string case 개방현인 경우 색상을 다르게해서 1~3 fret을 켜자
            playOpenString( notes[i][0] ); // current note's string number
            continue;
          }
          else {
            setNote( notes[i][0], notes[i][1] );
          }

          //          play(GREEN);

          if (sensing_notesCount > 0) {
            
            for(int j = 0; j < sensing_notesCount; j++)              
            if (notes[i][0] == sensing_notes[j][1] && notes[i][0] == sensing_notes[j][1]) play(YELLOW);
            
          }
          else play(GREEN);

          LED_turnoff();
        }

        //        if (sensing_notesCount > 0) {
        //          for (int i = 0; i < sensing_notesCount; i++) {
        //            setNote( sensing_notes[i][1], sensing_notes[i][0] );
        //            play(YELLOW);
        //            LED_turnoff();
        //          }
        //        }

        current_time = millis();
        elapsed_time = current_time - stime;

      } while ( elapsed_time < DURATION );

      LED_turnoff();
      initData();
      notesCount = 0;

      // 곡의 마지막까지 이동한 경우 loop를 빠져나오도록
      if ( play_Time >= total_Time ) {
        play_Time = 0;
        Timer3.stop();
        Timer4.stop();
        break; // if you move to the end of the song, performance will stop.
      }

      if ( play_Time < 0 || j <= 3 ) {
        rest_Time = 0;
        move_Time = 0;
        play_Time = 0;
        j = 3; // when you continue this for statement, j will be 4
        start_Time = millis();
        previousMillis = start_Time;
        continue; // play from the beginning
      }

      // handling repeat A-B
      if ( repeat_status == SET_B && play_Time >= repeat_end_time ) {
        move_Time = move_Time - (play_Time - repeat_start_time);
        play_Time = repeat_start_time;
        is_move_Time_updated = 1;
      }

      if ( is_move_Time_updated == 1 ) {

        int newposition = play_Time * strlen(rNote) / total_Time; //그냥 대충 비슷한 위치로 가자.

        // 그래도 @ 다음 문자부터 시작하도록
        j = 3; //j's default value is the beginning position of rNote. but j will be closest '@' position to the newposition.
        for (int pos = newposition; pos >= 4; pos--) {
          if (rNote[pos] == '@') {
            j = pos;
            break;
          }
        }
      }

      // repeat 중에 A지점 이전으로 이동하려는 경우 방지
      if ( repeat_status != NONE && play_Time < repeat_start_time ) {
        play_Time = repeat_start_time;
        int newposition = play_Time * strlen(rNote) / total_Time; //그냥 대충 비슷한 위치로 가자.
        j = 3; //j's default value is the beginning position of rNote. but j will be closest '@' position to the newposition.
        for (int pos = newposition; pos >= 4; pos--) {
          if (rNote[pos] == '@') {
            j = pos;
            break;
          }
        }
        continue;
      }

    }

  }

  Timer3.stop();
  Timer4.stop();
  mymenu = PLAYLIST_MENU;

}

void playOpenString( int string_number ) {
  int max_fret = 1;
  for (int i = 0; i < notesCount; i++) {
    if (notes[i][1] > max_fret) max_fret = notes[i][1];
  }
  setNote( string_number, max_fret );
  play(RED);
  LED_turnoff();
}

void setNote(int line, int fret) { // only one note will be set for playing

  //  initData();
  //  //ST_Raw = ~(0x01 << (line-1));
  //  ST_Data = ~(0x01 << (line - 1));
  //
  //  FR_L_Data = 0x0008 << (fret - 1);
  //  FR_H_Data = 0x0008 << (fret - 1); // 우쿨렐레

  initData();

  ST_Data = ~(0x01 << (line - 1));

  if ( fret < 8 )  FR_L_Data = 0x0003 << (fret * 2); // 0000 0000 0000 0011 프렛마다 두개씩 민다.
  else        FR_H_Data = 0x0004 << (fret - 8); // 0000 0000 0000 0100 프렛마다 하나씩 민다.

}

void play(int color) { //우크렐레
  // color
  if ( color == RED ) {
    //ST_Data = ((ST_Raw<<8) | 0xff); //for red
    digitalWrite( RED_LED_DIMM, LOW );
    digitalWrite( GREEN_LED_DIMM, HIGH );
  } else if (color == GREEN) {
    //ST_Data = ((0xff<<8) | ST_Raw) ; //for green
    digitalWrite( RED_LED_DIMM, HIGH );
    digitalWrite( GREEN_LED_DIMM, LOW );
  } else if (color == YELLOW) { // YELLOW
    digitalWrite( RED_LED_DIMM, LOW );
    digitalWrite( GREEN_LED_DIMM, LOW );
  }

  ST_ShiftResistor();
  FR_ShiftResistor();

}
void initData() {
  ST_Raw = 0xff; //initialize raw position string
  ST_Data = 0xff; // off all strings
  FR_L_Data = 0x0000; // no fret selected
  FR_H_Data = 0x0000;
}

void LED_turnoff()
{
  //all string reset
  digitalWrite( ST_STCP, LOW );
  shiftOut( ST_DS, ST_SHCP, MSBFIRST, 0xff );
  shiftOut( ST_DS, ST_SHCP, MSBFIRST, 0xff );
  digitalWrite( ST_STCP, HIGH );
  //all fret reset
  digitalWrite( FR_LE, LOW );

  shiftOut( FR_SDI, FR_CLK, LSBFIRST, 0x00 );
  shiftOut( FR_SDI, FR_CLK, LSBFIRST, 0x00 );
  shiftOut( FR_SDI, FR_CLK, LSBFIRST, 0x00 );
  shiftOut( FR_SDI, FR_CLK, LSBFIRST, 0x00 );

  digitalWrite( FR_LE, HIGH );
  digitalWrite( FR_LE, LOW) ;

}

void ST_ShiftResistor()
{
  digitalWrite( ST_STCP, LOW );
  shiftOut( ST_DS, ST_SHCP, MSBFIRST, ( ST_Data >> 8 ) );
  shiftOut( ST_DS, ST_SHCP, MSBFIRST, ST_Data );
  digitalWrite( ST_STCP, HIGH );
}


void FR_ShiftResistor()
{
  digitalWrite( FR_LE, LOW );

  shiftOut( FR_SDI, FR_CLK, LSBFIRST, FR_L_Data );
  shiftOut( FR_SDI, FR_CLK, LSBFIRST, ( FR_L_Data >> 8 ) );

  shiftOut( FR_SDI, FR_CLK, LSBFIRST, FR_H_Data );
  shiftOut( FR_SDI, FR_CLK, LSBFIRST, ( FR_H_Data >> 8 ) );

  digitalWrite( FR_LE, HIGH );
  digitalWrite( FR_LE, LOW) ;
}

/////////////////////////////////////////////////////// Part5 END
