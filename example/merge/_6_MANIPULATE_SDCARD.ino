
/////////////////////////////////////////////////////// Part6 Make File(SD), Load, Save

// 1. download and file make.
int makeFile(bool isRecord, String fileName) {

  String recv_data;
  String path;

  const char* p_path;
  const char* p_data;

  if ( isRecord == true ) {

    // path setting
    path = "Record/";
    path += fileName;
    path += ".txt";


    if ( isFileExist("Record", fileName) )    return 0;

    // file open and append new file name
    if ( !list_file.open("Record/RECORDLIST.txt", O_WRITE | O_AT_END ) )
      error("error code #1-1");

    fileName += "\n";
    const char* p_name = fileName.c_str();

    list_file.write( p_name , strlen(p_name) );
    if ( !list_file.close() )
      error("error code #1-2");


  } else if ( isRecord == false ) {

    // path setting
    path = "Score/";
    path += fileName;
    path += ".txt";


    if ( isFileExist("Score", fileName) )    return 0;

    // file open and append new file name
    if ( !list_file.open("Score/SONGLIST.txt", O_WRITE | O_AT_END ) )
      error("error code #1-3");

    fileName += "\n";
    const char* p_name = fileName.c_str();

    list_file.write( p_name , strlen(p_name) );
    if ( !list_file.close() )
      error("error code #1-4");
  }

  p_path = path.c_str();
  if (  !contents_file.open(p_path, O_CREAT | O_WRITE ) )
    error("error code #1-5");

  // title, user, tempo, contents
  for (int i = 0; i < 4; i++) {

    if ( i != 3 ) {
      recv_data = Serial3.readStringUntil('\n');
      recv_data += "\n";
    }
    else  recv_data = Serial3.readStringUntil(':');

    SerialUSB.print(i);    SerialUSB.print(recv_data);


    p_data = recv_data.c_str();

    contents_file.write(p_data, strlen(p_data) );

  }

  if ( !contents_file.close() )
    error("error code #1-6");


  // return success
  return 1;
}

void sendFileList(bool isRecord) {}
void removeSelectedFile(bool isRecord, String name) {}
void sendFileContents(String name) {}
bool isFileExist(String path,String fileName) {}

void makeFilename(char *title) {
  int len = strlen(title);
  //  Serial.print("title : "); Serial.println(title);
  //  Serial.print("title len : "); Serial.println(len);

  len = (len > 8 ) ? 8 : len;
  //  Serial.print("new len : "); Serial.println(len);
  strncpy(gFilename, title, len);
  gFilename[len] = '.';
  gFilename[len + 1] = 'T';
  gFilename[len + 2] = 'X';
  gFilename[len + 3] = 'T';
  gFilename[len + 4] = '\0';
  //  Serial.print("gFilename : "); Serial.println(gFilename);


  for (int i = 0; i < strlen(gFilename); i++) {
    if ( gFilename[i] == ' ' ) gFilename[i] = '_';
    if ( gFilename[i] == '\'' ) gFilename[i] = '9';
  }

  //  Serial.print("gFilename : "); Serial.println(gFilename);

}



void getTitlesFromSDCard() {  //  SONGLIST.TXT 를 읽어  songList[song_count].title 만든다ㅏ
  char ch;
  int char_index = 0;
  song_count = 0;

/*
  ///////////////////////////////////////////// directory setting Start (Score)
  if ( !SD.chdir() ) {
    SerialUSB.println("chdir to root failed");
  }

  if (!SD.chdir("Score")) {
    SerialUSB.println("chdir failed for Secord.");
  }
  cout << F("chdir to Score\n");
  ///////////////////////////////////////////// directory setting End
*/



  //  SerialUSB.println("# read SONGLIST.TXT #");
  myFile = SD.open("SONGLIST.TXT", FILE_READ);
  /*
  if ( !list_file.open("SONGLIST.TXT", O_READ ) )
      error("error code #0-1");
  
  if( list_file.available() ) {
      
      const char* p_data;  
      String read_data = list_file.read( p_data, list_file.fileSize() );
      
  }
  */
  if (myFile) {

    SerialUSB.println("Read SDcard...");

    while (myFile.available()) {
      ch = myFile.read();
      if ( ch == '_' ) ch = ' ';
      if ( ch == '9' ) ch = '\'';
      if ( ch < 0 ) continue;

      songList[song_count].title[char_index++] = ch;

      if ( ch == '\n' ) {
        songList[song_count].title[char_index - 1] = '\0';
        SerialUSB.println(songList[song_count].title);
        // reading
        SerialUSB.print(song_count); SerialUSB.print("   ]   "); SerialUSB.print("songList   :  "); SerialUSB.println(songList[song_count].title);
        song_count++;
        char_index = 0;
      }

    }

    //     Serial.println("right after SONGLIST.TXT creation");
    //      for(int i=0; i<10; i++){
    //         Serial.print(i); Serial.print("   ]   "); Serial.print("songList   :  "); Serial.println(songList[i].title);
    ////        Serial.print(i); Serial.print("->");
    ////        Serial.println(songList[i].title);
    ////      }

    myFile.close();
  } else { // SONGLIST.TXT 파일이 없을때
    // default temporary music for test
    song_count = 7;
    strcpy( songList[0].title, "JingleBell");
    strcpy( songList[1].title, "Noname");
    strcpy( songList[2].title, "Untitled1");
    strcpy( songList[3].title, "Untitled2");
    strcpy( songList[4].title, "Untitled3");
    strcpy( songList[5].title, "Untitled4");
    strcpy( songList[6].title, "Untitled5");

    strcpy( rArtist, "Anonymous");
    strcpy( rTime, "36000"); // 징글벨 연주시간 36seconds
    //    strcpy( rTime, "60000");

  }

  //  Serial.print("song_count"); Serial.println(song_count);

}





void makeRecordfile() {

  for (int i = 0; i <= 7; i++) {
    gFilename[i] = record_title[i];
  }

  gFilename[8] = '.';
  gFilename[9] = 'T';
  gFilename[10] = 'X';
  gFilename[11] = 'T';

  while (SD.exists(gFilename)) {
    record_count++;
    record_title[6] = '0' + (record_count / 10);
    record_title[7] = '0' + (record_count % 10);

    gFilename[6] = record_title[6];
    gFilename[7] = record_title[7];

    SerialUSB.println(" record_title  :  ");
    SerialUSB.println(record_title);
  }

  char play_time_char = 0;
  int play_time = 0;
  int cal_tempo = 0;
  int same_note = 0;
  double dif_time = 0;
  char content[3200];
  int current_cursor = 0;
  int end_of_cursor = 0;
  int total_play_time = 0;
  int num = 0;

  TEMPO = 750; // default 60000 / 80

  end_of_cursor = current_cursor + strlen(record_title);

  //  SerialUSB.print("  title] end_of_cursor   :   ");
  //  SerialUSB.println(end_of_cursor);

  // title
  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
    content[current_cursor] = record_title[num++];
  }

  num = 0;
  end_of_cursor = current_cursor + strlen(record_artist) + 1;
  content[current_cursor++] = '\n';
  //    content[current_cursor++] = 'a';

  //  SerialUSB.print("  artist] end_of_cursor   :   ");
  //  SerialUSB.println(end_of_cursor);
  //  SerialUSB.print("  after title] current cursor   :   ");
  //  SerialUSB.println(current_cursor);

  // artist
  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
    content[current_cursor] = record_artist[num++];
  }

  content[current_cursor] = '\n';
  //    content[current_cursor] = 'b';

  //  SerialUSB.print("  after artist] current cursor   :   ");
  //  SerialUSB.println(current_cursor);

  // temp values
  record_note[0].noteFret = 1;
  record_note[0].noteString = 5;
  record_note[0].startTime = 3000.000;
  record_note[0].endTime = 3500.000;

  record_note[1].noteFret = 2;
  record_note[1].noteString = 4;
  record_note[1].startTime = 3700.000;
  record_note[1].endTime = 4000.000;

  record_note[2].noteFret = 3;
  record_note[2].noteString = 3;
  record_note[2].startTime = 4100.000;
  record_note[2].endTime = 5000.000;

  record_note[3].noteFret = 13;
  record_note[3].noteString = 6;
  record_note[3].startTime = 4100.000;
  record_note[3].endTime = 5000.000;

  // calculate play_time

  current_cursor = end_of_cursor + 12;

  for (int j = 0; j < record_max; j++ ) {

    if (record_note[j].noteFret == 99 || record_note[j].noteString == 99) break;

    DURATION = record_note[j].endTime - record_note[j].startTime;

    play_time_char = 'W';
    dif_time = abs(TEMPO * 4 - DURATION);

    if (dif_time > abs(TEMPO * 2 - DURATION)) {
      play_time_char = 'H';
      play_time = TEMPO * 2;
      dif_time = abs(TEMPO * 2 - DURATION);
    }
    if (dif_time > abs(TEMPO * 1 - DURATION)) {
      play_time_char = 'Q';
      play_time = TEMPO * 1;
      dif_time = abs(TEMPO * 1 - DURATION);
    }
    if (dif_time > abs(TEMPO * 0.5 - DURATION)) {
      play_time_char = 'E';
      play_time = TEMPO * 0.5;
      dif_time = abs(TEMPO * 0.5 - DURATION);
    }
    if (dif_time > abs(TEMPO / 3 - DURATION)) {
      play_time_char = 'q';
      play_time = TEMPO / 3;
      dif_time = abs(TEMPO / 3  - DURATION);
    }
    if (dif_time > abs(TEMPO * 0.25 - DURATION)) {
      play_time_char = 'S';
      play_time = TEMPO * 0.25;
      dif_time = abs(TEMPO * 0.25 - DURATION);
    }
    if (dif_time > abs(TEMPO * 0.5 / 3 - DURATION)) {
      play_time_char = 'e';
      play_time = TEMPO * 0.5 / 3;
      dif_time = abs(TEMPO * 0.5 / 3 - DURATION);
    }
    if (dif_time > abs(TEMPO * 0.25 / 3 - DURATION)) {
      play_time_char = 's';
      play_time = TEMPO * 0.25 / 3;
      dif_time = abs(TEMPO * 0.25 / 3 - DURATION);
    }

    if (!same_note) {
      content[current_cursor++] = play_time_char;
      total_play_time += play_time;
    }

    if (record_note[j].noteFret >= 10) {
      content[current_cursor++] = '0' + (record_note[0].noteFret / 10);
      content[current_cursor++] = '0' + (record_note[0].noteFret % 10);
    }
    else content[current_cursor++] = '0' + record_note[0].noteFret;

    content[current_cursor++] = ',';
    content[current_cursor++] = '0' + record_note[0].noteString;
    content[current_cursor++] = '-';

    if (j == record_max - 1) content[current_cursor++] = '@';
    else if (abs(record_note[j].startTime - record_note[j + 1].startTime) >= 100) {
      content[current_cursor++] = '@';
      same_note = 0;
    }
    else same_note = 1;

  }

  content[current_cursor] = '\0';

  //  SerialUSB.print("  total play time   :   ");
  //  SerialUSB.println(total_play_time);

  current_cursor = end_of_cursor + 1;
  end_of_cursor = current_cursor + 6;

  //  SerialUSB.print("  before total_play_time] current cursor   :   ");
  //  SerialUSB.println(current_cursor);

  // total_play_time
  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
    if (end_of_cursor - current_cursor == 6) content[current_cursor] = '0' + total_play_time / 100000;
    else if (end_of_cursor - current_cursor == 5) content[current_cursor] = '0' + total_play_time % 100000 / 10000;
    else if (end_of_cursor - current_cursor == 4) content[current_cursor] = '0' + total_play_time % 10000 / 1000;
    else if (end_of_cursor - current_cursor == 3) content[current_cursor] = '0' + total_play_time % 1000 / 100;
    else if (end_of_cursor - current_cursor == 2) content[current_cursor] = '0' + total_play_time % 100 / 10;
    else if (end_of_cursor - current_cursor == 1) content[current_cursor] = '0' + total_play_time % 10;
  }

  //  end_of_cursor = current_cursor + 4;
  content[current_cursor++] = '\n';
  //  content[current_cursor] = 'c';

  //  SerialUSB.print("  after total_play_time] current cursor   :   ");
  //  SerialUSB.println(current_cursor);

  // TEMPO
  cal_tempo = 60000 / (int)TEMPO; // cal_tempo = 80

  content[current_cursor++] = '0' + cal_tempo / 100;
  content[current_cursor++] = '0' + cal_tempo % 100 / 10;
  content[current_cursor++] = '0' + cal_tempo % 10;

  //  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
  //    if (end_of_cursor - current_cursor == 3) content[current_cursor] = '0' + cal_tempo / 100;
  //    else if (end_of_cursor - current_cursor == 2) content[current_cursor] = '0' + cal_tempo % 100 / 10;
  //    else if (end_of_cursor - current_cursor == 1) content[current_cursor] = '0' + cal_tempo % 10;
  //  }

  content[current_cursor] = '!';

  //  SerialUSB.print("  after TEMPO] current cursor   :   ");
  //  SerialUSB.println(current_cursor);

  SerialUSB.println("    Contents   ]  ");

  //  for (int i = 0; i < strlen(content); i++) {
  //    SerialUSB.print(content[i]);
  //  }

  int result = fileSave(record_title, content); // file name and contents

  if ( result == 1 ) {
    myFile = SD.open("SONGLIST.TXT", FILE_WRITE);
    while (myFile) {
      for (int j = 0; j < strlen(record_title) ; j++) {
        myFile.print(record_title[j]);
      }
      myFile.print('\n');
      myFile.close();
    }
  }

  song_count++;

}

int fileSave(char *title, char *content) {

  makeFilename(title); // set *.txt filename to global variable gFilename
  SerialUSB.print("gFilename:"); SerialUSB.println( gFilename );

  ///////////////////////////////////////////// directory setting Start (Record)
  if ( !SD.chdir() ) {
    SerialUSB.println("chdir to root failed");
  }

  if (!SD.chdir("Record")) {
    SerialUSB.println("chdir failed for Record.");
  }
  cout << F("chdir to Record\n");
  ///////////////////////////////////////////// directory setting End

  if ( SD.exists(gFilename) ) SerialUSB.println("file exists");
  else if (!SD.exists(gFilename)) { // 파일이 없는경우만 저장하자
    myFile = SD.open(gFilename, FILE_WRITE);
    for (int j = 0; j < strlen(content); j++) {
      myFile.print(content[j]);

    }
    SerialUSB.println("file save done");
    myFile.close();
    return 1; // success
  }
  return 0;

}

//char* recordContent(char* title, char* artist) {
//
//  char play_time_char = 0;
//  int play_time = 0;
//  int cal_tempo = 0;
//  double dif_time = 0;
//  char content[3200];
//  int current_cursor = 0;
//  int end_of_cursor = 0;
//  int total_play_time = 0;
//  int num = 0;
//
//  TEMPO = 750; // default 60000 / 80
//
//  end_of_cursor = current_cursor + strlen(title);
//
//  SerialUSB.print("  title] end_of_cursor   :   ");
//  SerialUSB.println(end_of_cursor);
//
//  // title
//  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
//    content[current_cursor] = title[num++];
//  }
//
//  num = 0;
//  end_of_cursor = current_cursor + strlen(artist) + 1;
//  content[current_cursor++] = '\n';
////    content[current_cursor++] = 'a';
//
//  SerialUSB.print("  artist] end_of_cursor   :   ");
//  SerialUSB.println(end_of_cursor);
//
//  SerialUSB.print("  after title] current cursor   :   ");
//  SerialUSB.println(current_cursor);
//
//  // artist
//  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
//    content[current_cursor] = artist[num++];
//  }
//
//  content[current_cursor] = '\n';
////    content[current_cursor] = 'b';
//
//  SerialUSB.print("  after artist] current cursor   :   ");
//  SerialUSB.println(current_cursor);
//
//  // temp values
//  record_note[0].noteFret = 1;
//  record_note[0].noteString = 5;
//  record_note[0].startTime = 3000.000;
//  record_note[0].endTime = 3500.000;
//
//  record_note[1].noteFret = 2;
//  record_note[1].noteString = 4;
//  record_note[1].startTime = 3700.000;
//  record_note[1].endTime = 4000.000;
//
//  record_note[2].noteFret = 3;
//  record_note[2].noteString = 3;
//  record_note[2].startTime = 4100.000;
//  record_note[2].endTime = 5000.000;
//
//  // calculate play_time
//
//  current_cursor = end_of_cursor + 12;
//
//  for (int j = 0; j < record_max; j++ ) {
//
////    if (record_note[j].noteFret == 99 && record_note[j].noteString == 99) break;
//
//    DURATION = record_note[j].endTime - record_note[j].startTime;
//
//    play_time_char = 'W';
//    dif_time = abs(TEMPO * 4 - DURATION);
//
//    if (dif_time > abs(TEMPO * 2 - DURATION)) {
//      play_time_char = 'H';
//      play_time = TEMPO * 2;
//      dif_time = abs(TEMPO * 2 - DURATION);
//    }
//    if (dif_time > abs(TEMPO * 1 - DURATION)) {
//      play_time_char = 'Q';
//      play_time = TEMPO * 1;
//      dif_time = abs(TEMPO * 1 - DURATION);
//    }
//    if (dif_time > abs(TEMPO * 0.5 - DURATION)) {
//      play_time_char = 'E';
//      play_time = TEMPO * 0.5;
//      dif_time = abs(TEMPO * 0.5 - DURATION);
//    }
//    if (dif_time > abs(TEMPO / 3 - DURATION)) {
//      play_time_char = 'q';
//      play_time = TEMPO / 3;
//      dif_time = abs(TEMPO / 3  - DURATION);
//    }
//    if (dif_time > abs(TEMPO * 0.25 - DURATION)) {
//      play_time_char = 'S';
//      play_time = TEMPO * 0.25;
//      dif_time = abs(TEMPO * 0.25 - DURATION);
//    }
//    if (dif_time > abs(TEMPO * 0.5 / 3 - DURATION)) {
//      play_time_char = 'e';
//      play_time = TEMPO * 0.5 / 3;
//      dif_time = abs(TEMPO * 0.5 / 3 - DURATION);
//    }
//    if (dif_time > abs(TEMPO * 0.25 / 3 - DURATION)) {
//      play_time_char = 's';
//      play_time = TEMPO * 0.25 / 3;
//      dif_time = abs(TEMPO * 0.25 / 3 - DURATION);
//    }
//
//    content[current_cursor++] = play_time_char;
//
//    if (record_note[j].noteFret >= 10) {
//      content[current_cursor++] = '0' + (record_note[0].noteFret / 10);
//      content[current_cursor++] = '0' + (record_note[0].noteFret % 10);
//    }
//    else content[current_cursor++] = '0' + record_note[0].noteFret;
//
//    content[current_cursor++] = ',';
//    content[current_cursor++] = '0' + record_note[0].noteString;
//    content[current_cursor++] = '-';
//    content[current_cursor++] = '@';
//
//    total_play_time += play_time;
//
//  }
//
//  SerialUSB.print("  total play time   :   ");
//  SerialUSB.println(total_play_time);
//
//  current_cursor = end_of_cursor + 1;
//  end_of_cursor = current_cursor + 6;
//
//  SerialUSB.print("  before total_play_time] current cursor   :   ");
//  SerialUSB.println(current_cursor);
//
//  // total_play_time
//  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
//    if (end_of_cursor - current_cursor == 6) content[current_cursor] = '0' + total_play_time / 100000;
//    else if (end_of_cursor - current_cursor == 5) content[current_cursor] = '0' + total_play_time % 100000 / 10000;
//    else if (end_of_cursor - current_cursor == 4) content[current_cursor] = '0' + total_play_time % 10000 / 1000;
//    else if (end_of_cursor - current_cursor == 3) content[current_cursor] = '0' + total_play_time % 1000 / 100;
//    else if (end_of_cursor - current_cursor == 2) content[current_cursor] = '0' + total_play_time % 100 / 10;
//    else if (end_of_cursor - current_cursor == 1) content[current_cursor] = '0' + total_play_time % 10;
//  }
//
////  end_of_cursor = current_cursor + 4;
//  content[current_cursor++] = '\n';
////  content[current_cursor] = 'c';
//
//  SerialUSB.print("  after total_play_time] current cursor   :   ");
//  SerialUSB.println(current_cursor);
//
//  // TEMPO
//  cal_tempo = 60000 / (int)TEMPO; // cal_tempo = 80
//
//  content[current_cursor++] = '0' + cal_tempo / 100;
//  content[current_cursor++] = '0' + cal_tempo % 100 / 10;
//  content[current_cursor++] = '0' + cal_tempo % 10;
//
////  for (current_cursor; current_cursor < end_of_cursor; current_cursor++) {
////    if (end_of_cursor - current_cursor == 3) content[current_cursor] = '0' + cal_tempo / 100;
////    else if (end_of_cursor - current_cursor == 2) content[current_cursor] = '0' + cal_tempo % 100 / 10;
////    else if (end_of_cursor - current_cursor == 1) content[current_cursor] = '0' + cal_tempo % 10;
////  }
//
//  content[current_cursor] = '!';
//
//  SerialUSB.print("  after TEMPO] current cursor   :   ");
//  SerialUSB.println(current_cursor);
//
//  return content;
//
//}

/////////////////////////////////////////////////////// Part6 END
