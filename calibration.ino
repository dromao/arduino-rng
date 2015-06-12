void calibrate(byte adc_byte){
  bins[adc_byte]++;
}

unsigned int findThreshold(){
  unsigned long half;
  unsigned long total = 0;
  int i;

  for(i=0; i < BINS_SIZE; i++){
    total += bins[i];
  }

  half = total >> 1;
  total = 0;
  for(i=0; i < BINS_SIZE; i++){
    total += bins[i];
    if(total > half){
      break;
    }
  }
  Serial.print("\nThe threshold is: ");
  Serial.println(i);
  return i;
}
