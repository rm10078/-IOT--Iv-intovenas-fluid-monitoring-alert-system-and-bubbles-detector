


void send_tel_alart(String text){
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = "https://api.telegram.org/bot"+token+"/sendMessage?chat_id="+chat_id+"&text="+text;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
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
