void set_fluid(){
  int tw=0,aw=0;
  lcd.clear();
  display_print(0,0,"Fluid weight");
  int count=0;
  while(true){
    while(digitalRead(up_but)==0 && count<2000){
      count+=50;
      delay(700);
      lcd.setCursor(0,1);
      lcd.print(count);
      }
    while(digitalRead(down_but)==0 && count>0){
      count-=50;
      delay(700);
      lcd.setCursor(0,1);
      lcd.print(count);
      }
      if(digitalRead(ok_but)==0){
        while(digitalRead(ok_but)==0){}
        tw=count;
        break;
        }
    }
    count=0;
    lcd.clear();
    display_print(0,0,"Alert Weight");
    delay(500);
  while(true){
    while(ok_but==0){}
    while(digitalRead(up_but)==0 && count<2000){
      count+=10;
      delay(100);
      lcd.setCursor(0,1);
      lcd.print(count);
      }
    while(digitalRead(down_but)==0 && count>0){
      count-=10;
      delay(100);
      lcd.setCursor(0,1);
      lcd.print(count);
      }
      if(digitalRead(ok_but)==0){
        while(digitalRead(ok_but)==0){}
        aw=count;
        break;
        }
         }
      delay(700);
      lcd.clear();
      display_print(0,0,"Save data ??");
          eeprom_write_int(150,tw);
          eeprom_write_int(160,aw);
          delay(500);
          display_print(0,1,"Done Restart");
          delay(500);
 
  }
