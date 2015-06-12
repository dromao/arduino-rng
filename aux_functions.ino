//Blinks an LED after each 10th of the calibration completes
void printStatus(){
  unsigned int increment = CALIBRATION_SIZE / 10;
  static unsigned int num_increments = 0; //progress units so far
  unsigned int threshold;

  threshold = (num_increments + 1) * increment;
  if(calibration_counter > threshold){
    num_increments++;
    Serial.print("*");
    blinkLed();
  }
}

void blinkLed(){
  digitalWrite(led_pin, HIGH);
  delay(30);
  digitalWrite(led_pin, LOW);
}

void clear_bins(){
  int i;
  for(i=0; i < BINS_SIZE; i++){
      bins[i]=0;
  }
}
