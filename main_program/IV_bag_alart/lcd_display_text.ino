
void display_print(int x,int y,String text){
  lcd.setCursor(x,y);
  lcd.print(text);
  }

void display_clear(int x,int y,int z){
  String d="";
  for(int i=0;i<z;i++){
    d +=" ";
    }
  lcd.setCursor(x,y);
  lcd.print(d);
  }

void display_all_data(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Flow rate");
  lcd.setCursor(0,1);
  lcd.print(flow_rate);

  lcd.setCursor(10,0);
  lcd.print("Flow sta");
  lcd.setCursor(10,1);
  lcd.print(flow);

  lcd.setCursor(0,2);
  lcd.print("Fluid weight=");
  lcd.setCursor(14,2);
  lcd.print(current_weight);
  
  lcd.setCursor(0,3);
  lcd.print("alert weight=");
  lcd.setCursor(14,3);
  lcd.print(alert_value);
  }
