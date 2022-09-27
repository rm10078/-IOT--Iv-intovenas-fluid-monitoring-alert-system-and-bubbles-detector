void eeprom_write(String word,int start_add) {
  delay(1);
  for (int i = 0; i < word.length(); ++i) {
    //Serial.println(word[i]);
    EEPROM.write(start_add+i, word[i]);
  }

  EEPROM.write(start_add+word.length(), '\0');
  EEPROM.commit();
}

String eeprom_read(int start_add) {
  String word;
  char readChar='n';
  int i = 0;

  while (readChar != '\0') {
    int tem=start_add+i;
    readChar = char(EEPROM.read(tem));
    delay(1);
    i++;

    if (readChar != '\0') {
      word += readChar;
    }
  }

  return word;
}

void eeprom_write_int(int s_add,int val){
  int data=(val/5);
  for(int i=0;i<5;i++){
  EEPROM.write(s_add+i,data);
  }
  EEPROM.commit();
  }
  
int eeprom_read_int(int s_add){
  int data=0;
  for(int i=0;i<5;i++){
  data += EEPROM.read(s_add+i);
  }
  return data;
  }
