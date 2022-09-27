

void load_cell_setup(){
  scale.begin(loadcell_DOUT, loadcell_SCK);

  scale.set_scale(Cal_fact);   // Calfac=()/(know weight)
  scale.tare();  //for reseting the scale
  }

float load_cell_read(){
  if (scale.wait_ready_timeout(200)) {
  //float reading = round(scale.get_units());
  float reading =scale.get_units();
    Serial.print("Weight: ");
    Serial.println(reading);
    return reading;
  }
  else {
    Serial.println("HX711 not found.");
    return NULL;
  }
  }
