
void web_update(int field,String text){
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = "https://api.thingspeak.com/update?api_key=LAESAN9FEHX95W58&field"+String(field)+"="+text;
      
      http.begin(serverPath.c_str());
      
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
