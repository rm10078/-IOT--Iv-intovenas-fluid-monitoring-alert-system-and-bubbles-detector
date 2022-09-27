#include "HX711.h"
#include <WiFi.h>
#include <Wire.h> 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;

#define Cal_fact 103.768

LiquidCrystal_I2C lcd(0x27,20,4);  //lcd display init 
HX711 scale;  //load cell init
const int loadcell_DOUT = 16;
const int loadcell_SCK = 4;

const int air_sensor=18;
const int set_dev=17;
const int up_but=25;
const int down_but=26;
const int ok_but=27;
const int back_but=14;
const int bt_sta=32;

int flow_rate=0;
String flow="Run";
int alert_value=0;
int fluid_weight=0;
float current_weight=0;
float total_weight=0;
float ext_weight=0;
float bat_val=0;
int air=0;

String ssid;
String password;
String pa_name;
String deviceid;

//pin declearition
int config_pin=19;
int sub_status=0;
//end pin declearition

int config_status=0;


const String token="5415006207:AAGpvOblJ9XLM71jBltrmdSost-yWZIMIH0";    //tonken for telegram bot
String chat_id="829301848";

AsyncWebServer server(80);

const char sub_html[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        h1{
            margin: auto;
            text-align: center;
            font-family: cursive;
            margin-top: 30%;
            font-size: 15vw;
        }
    </style>
    <title>submit</title>
</head>
<body>
    <h1>Submit done</h1>
</body>
</html>)rawliteral";

const char config_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        *{
    margin: 0%;
    padding: 0%;
    box-sizing: border-box;
}
body{
    background-color: #f1f1f1;
    font-family: 'Roboto', sans-serif;
}
.pop_mas{
  background-color: red;
  color: white;
  }
.title{
    margin: auto;
    text-align: center;
    margin-top: 3vw;
    font-size: 3vw;
    font-family: Monospace;
}
.data_ps form{
    margin:auto;
    text-align: center;
    margin-top: 3vw;
}
.data_ps form input{
    margin: 1vw;
    font-size: 2vw;
    font-family: Monospace;
}
.data_ps form h3{
    font-size: 2vw;
    font-family: Cursive;
    margin-top: 1vw;
}
.data_ps form button{
    display: block;
    margin: auto;
    margin-top: 3vw;
    font-size: 2vw;
    font-family: Monospace;
    padding: 1vw;
    border-radius: 1vw;
    border-style: none;
    background-color: #00d5ff;
    color: white;
    box-shadow: 0 0 1vw #00d5ff;
    margin-bottom: 3vw;
}
.data_ps form button:hover{
    box-shadow: 0 0 1vw #ff87e3;
}
@media only screen and (max-width: 600px) {
    .data_ps form h3{
        font-size: 7vw;
    }
    .data_ps form input{
        width: 60vw;
        font-size: 6vw;
    }
    .data_ps form button{
        font-size: 5vw;
        margin-top: 7vw;
    }
    .title{
        font-size: 6vw;
    }
  }
    </style>
    <title>Config page</title>
</head>
<body>
    %msg%
    <div class="title">
        <h1>Config your device</h1>
    </div>
    <div class="data_ps">
        <form action="/sub" method="get">
            <h3 class="ssid">SSID</h3>
            <input type="text" name="ssid" id="ssid" placeholder="WiFi Name">
            <h3 class="password">Password</h3>
            <input type="password" name="password" id="password" placeholder="WiFi Password">
            <h3 class="ssid">Patient name</h3>
            <input type="text" name="p_name" id="p_name" placeholder="Patient name">
            <h3 class="devid">Device ID</h3>
            <input type="text" name="devid" id="devid" placeholder="Device ID">
            <h3 class="telbot">Telegram chat id</h3>
            <input type="text" name="tcid" id="tcid" placeholder="Chat id">
            <button type="submit">Submit</button>
        </form>
    </div>
</body>
</html>
)rawliteral";


const char main_html[] PROGMEM = R"rawliteral(%sss%)rawliteral";




String processor(const String& var){
  if(sub_status==1){
  if(var=="msg"){
    String tem ="<div class='pop_msg'><h3>Data saved</h3></div>";
    sub_status=0;
    return tem;
    }
  }
  else{
  return String();
  }}

String main_processor(const String& var){
  //Serial.println(var);
  if(var == "sss"){
    String tx = "<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"    <title>Offlinepage</title>\n"
"    <style>\n"
"    *{\n"
"    margin:0;\n"
"    padding: 0;\n"
"    box-sizing: border-box;\n"
"}\n"
"body{\n"
" background-color: rgb(19, 25, 26);   \n"
"}\n"
".text_dcolor{\n"
"    color: white;\n"
"}\n"
".title{\n"
"    margin-top: 2vw;\n"
"    text-align: center;\n"
"    font-style: oblique;\n"
"    font-size: 8vw;\n"
"}\n"
".sub_title{\n"
"    text-align: center;\n"
"}\n"
"\n"
".info{\n"
"    display: flex;\n"
"    flex-direction: row;\n"
"    margin: auto;\n"
"    margin-top: 3vw;\n"
"    width: 80vw;\n"
"    height: 30vw;\n"
"    border-radius: 2vw;\n"
"    border-color: white;\n"
"    border-width: 2px;\n"
"    border-style: solid;\n"
"    box-shadow: 0 0 2vw rgb(0, 255, 221);\n"
"}\n"
".subinfo{\n"
"    margin: auto;\n"
"    border-radius: 2vw;\n"
"    width: 22vw;\n"
"    height: 24vw;\n"
"    background-color: #ffffff;\n"
"    text-align: center;\n"
"    box-shadow: 0 0 2vw rgb(255, 255, 255);\n"
"}\n"
".subinfo h1{\n"
"    margin-top:6vw;\n"
"    font-size: 4vw;\n"
"    color: rgb(0, 0, 0);\n"
"}\n"
".control{\n"
"    margin: auto;\n"
"    margin-top: 3vw;\n"
"    margin-bottom: 3vw;\n"
"    width: 80vw;\n"
"    height: auto;\n"
"}\n"
".control button{\n"
"    width: 22vw;\n"
"    height: auto;\n"
"    font-size: 3vw;\n"
"    border-radius: 2vw;\n"
"}\n"
".start_but{\n"
"    padding: 0.5vw;\n"
"    box-shadow: 0 0 1vw #0166d3;\n"
"    color: white;\n"
"    background-color: #4ad5ff;\n"
"    border-style: none;\n"
"}\n"
".stop_but{\n"
"    padding: 0.5vw;\n"
"    margin-left: 10vw;\n"
"    box-shadow: 0 0 1vw rgb(185, 0, 108);\n"
"    color: white;\n"
"    background-color: rgb(255, 46, 168);\n"
"    border-style: none;\n"
"}\n"
"@media only screen and (max-width: 600px) {\n"
"    .title{\n"
"        font-size: 7vw;\n"
"    }\n"
"    .sub_title{\n"
"        font-size: 2.5vw;\n"
"    }\n"
"    .info{\n"
"        flex-direction: column;\n"
"        width: 80vw;\n"
"        height: auto;\n"
"        padding-bottom: 3vw;\n"
"    }\n"
"    .subinfo{\n"
"        margin: auto;\n"
"        width: 60vw;\n"
"        height: 60vw;\n"
"        margin-top: 5vw;\n"
"    }\n"
"    .subinfo h1{\n"
"        margin-top: 18vw;\n"
"        font-size: 11vw;\n"
"    }\n"
"    .stop_but{\n"
"        margin-left: 20vw;\n"
"    }\n"
"    .control button{\n"
"        height: auto;\n"
"        font-size: 5vw;\n"
"    }\n"
"    .control{\n"
"        margin-bottom: 10vw;\n"
"    }\n"
"}\n"
"    </style>\n"
"\n"
"</head>\n"
"<body>\n"
"    <div><h1 class=\"text_dcolor title\">IV Monitoring and alart</h1></div>\n"
"    <div class=\"text_dcolor sub_title\">\n"
"        <h2>Present Name: "+pa_name+" </h2>\n"
"        <h2>Bad number: 987654321</h2>\n"
"        <h2>Device ID: "+deviceid+"</h2>\n"
"    </div>\n"
"\n"
"    <div class=\"info\">\n"
"        <div class=\"subinfo si0\">\n"
"            <h2>Flow status</h2>\n"
"            <h1>"+flow+"</h1>\n"
"        </div>\n"
"        <div class=\"subinfo si1\">\n"
"            <h2>Current weight</h2>\n"
"            <h1>"+current_weight+"g</h1>\n"
"        </div>\n"
"        <div class=\"subinfo si2\">\n"
"            <h2>Flow rate(g/min)</h2>\n"
"            <h1>"+flow_rate+"</h1>\n"
"        </div>\n"
"    </div>\n"
"\n"
"    <div class=\"info in4\">\n"
"        <div class=\"subinfo si00\">\n"
"            <h2>Total weight</h2>\n"
"            <h1>"+fluid_weight+"</h1>\n"
"        </div>\n"
"        <div class=\"subinfo si11\">\n"
"            <h2>Battery V</h2>\n"
"            <h1>"+bat_val+"</h1>\n"
"        </div>\n"
"        <div class=\"subinfo si22\">\n"
"            <h2>Drip rate(gtts/min)</h2>\n"
"            <h1>"+flow_rate+"</h1>\n"
"        </div>\n"
"    </div>\n"
"\n"
"    <div class=\"control\">\n"
"        <button class=\"start_but\" onclick=\"startbut()\">Start flow</button>\n"
"        <button class=\"stop_but\" onclick=\"stopbut()\">Stop flow</button>\n"
"    </div>\n"
"</body>\n"
"<script>\n"
"    console.log(\"Hello world\");\n"
"function startbut() {\n"
"    console.log(\"start\");\n"
"}\n"
"function stopbut(params) {\n"
"    console.log(\"stop\");\n"
"}\n"
"setTimeout(() => {\n"
"  document.location.reload();\n"
"}, 8000);\n"
"</script>\n"
"</html>";
    
    return tx;
  }
  return String();
}

//ISR fun
void IRAM_ATTR ISR(){
  Serial.println("Air is present inside the tube.");
  if(WiFi.status()==WL_CONNECTED){}
  air=1;
  }

//ISR fun

void setup() {
delay(1000);
pinMode(config_pin,INPUT_PULLUP);
pinMode(set_dev,INPUT_PULLUP);

pinMode(up_but,INPUT_PULLUP);
pinMode(down_but,INPUT_PULLUP);
pinMode(ok_but,INPUT_PULLUP);
pinMode(back_but,INPUT_PULLUP);
pinMode(air_sensor,INPUT);
pinMode(bt_sta,INPUT);

Serial.begin(115200);
EEPROM.begin(512);
myservo.attach(13);
myservo.write(0);

attachInterrupt(air_sensor,ISR,RISING);

Serial.println("Power on..... ");



lcd.init();
lcd.init();
lcd.backlight();
if(digitalRead(back_but)==0){
  set_fluid();
  }

ssid=eeprom_read(0);
password=eeprom_read(30);
pa_name=eeprom_read(60);
deviceid=eeprom_read(90);
chat_id=eeprom_read(120);
fluid_weight=eeprom_read_int(150);
alert_value=eeprom_read_int(160);    //problem

Serial.print("All eeprom data=");
Serial.println("  "+ssid+"  "+password+"  "+pa_name+" "+deviceid+" "+chat_id+"  "+fluid_weight+"  "+alert_value);


Serial.print("config pin Status:");
Serial.println(digitalRead(config_pin));
if(digitalRead(config_pin)==0){
  config_status=1;
  display_print(0,0,"Config mode....");
  
  WiFi.softAP("IVMA_config","hit@1234");
  delay(500);
  display_print(0,1,"192.168.4.1");
  IPAddress ip=WiFi.softAPIP();
  Serial.println(ip);

  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", config_html, processor);
  });
  
  server.on("/sub", HTTP_GET, [](AsyncWebServerRequest *request){
    String message,t_ssid,t_password,t_pname,t_devid,t_tcid;
    if (request->hasParam("ssid")) {
      message = request->getParam("ssid")->value();
      t_ssid = message;
    }
    if (request->hasParam("password")) {
      message = request->getParam("password")->value();
      t_password = message;
    }
    if (request->hasParam("p_name")) {
      message = request->getParam("p_name")->value();
      t_pname = message;
    }
    if (request->hasParam("devid")) {
      message = request->getParam("devid")->value();
      t_devid = message;
    }
    if (request->hasParam("tcid")) {
      message = request->getParam("tcid")->value();
      t_tcid = message;
    }

    if(t_ssid != ""){
    request->send_P(200, "text/html", sub_html, processor);
    eeprom_write(t_ssid,0);
    eeprom_write(t_password,30);
    eeprom_write(t_pname,60);
    eeprom_write(t_devid,90);
    eeprom_write(t_tcid,120);
    }
    Serial.println(t_ssid+"     "+t_password+"     "+t_pname+"     "+t_devid+"    "+t_tcid);
  });
  server.begin();
  }
  else{
    char mssid[30],mpassword[30];
    for(int i=0;i<ssid.length();i++){
      mssid[i]=ssid[i];
      }
    for(int i=0;i<password.length();i++){
      mpassword[i]=password[i];
      }
   //Serial.println(mssid+"  "+mpassword);
    WiFi.begin(mssid,mpassword); 
    Serial.print("connecting");

    if(WiFi.status()!=WL_CONNECTED){
      display_print(0,0,"Connecting wifi");
      }
    
    while(WiFi.status()!=WL_CONNECTED){
      Serial.print(".");
      delay(100);
      }

  lcd.clear();
    
  if(WiFi.status()==WL_CONNECTED){
 Serial.println("Wifi is connected");
 Serial.println(WiFi.localIP());
 String ip_s=WiFi.localIP().toString().c_str();
 display_print(0,0,"Set IV bag");
 display_print(0,1,ip_s);
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", main_html, main_processor);
  });
server.begin();
send_tel_alart("Power on.....");
  }
    display_print(0,2,"Remove all weight.");
    display_print(0,3,"Press ok");
    while(digitalRead(ok_but)==1){}  
    load_cell_setup();
    delay(500);
    display_print(0,2,"Add   Fluid   bag.");
    display_print(0,3,"Press ok");
    while(digitalRead(ok_but)==1){}
    delay(800);
    display_print(0,2,"                   ");
    display_print(0,2,"Total weight.");
    display_print(0,3,"Press ok");
    while(digitalRead(ok_but)==1){
      float tem=load_cell_read();
      lcd.setCursor(10,3);
      lcd.print(tem);
      total_weight=tem;
      }
    ext_weight=total_weight-fluid_weight;
    display_all_data();
    lcd.clear();
    
    }
}

long now=0;
long pre=0;
long pre_we=0;
long cw_pre=0.0;
long alt_t=0;
long t=0;

void loop() {
  if(config_status!=1){
    now=millis();
    if(digitalRead(back_but)==0){
      myservo.write(0);
      }
  if(now-pre>=10000){
    float we=load_cell_read();
    flow_rate=(pre_we-we)*6;
    pre_we=we;
    if(flow_rate==0){
      flow="Stop";
      }
    else{
      flow="Run";
      }
    display_all_data();
    pre=now;
    int f_s=0;
    if(flow=="Run"){
      f_s=1;
      }
    else{
      f_s=0;
      }
    web_update(1,String(flow_rate));
    web_update(2,String(current_weight));
    web_update(3,String(f_s));
   // web_update(4,String(alert_value));
    }
  current_weight=(load_cell_read()-ext_weight);
  
  if(now-cw_pre>=2000){
    lcd.setCursor(14,2);
    lcd.print(current_weight);
    if(current_weight<alert_value){
      t+=10000;
      Serial.println("Alart");
      send_tel_alart("Warning!!! Fluid level is low. Fluid current Weight="+String(current_weight)+".");
      }
    cw_pre=now;
    }
  if(air==1){
    Serial.println("air inside the pipe.");
    send_tel_alart("Warning!!! Air bubble is present in the line.");
    air=0;
    }
  int tem=analogRead(bt_sta);
  bat_val=((3.3*tem)/4095)*2;
  bat_val+=0.4;
  Serial.println(tem);
  
}
}
