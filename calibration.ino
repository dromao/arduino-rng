void calibrate(byte adc_byte, int ng){
  bins[ng][adc_byte]++;
}

unsigned int findThreshold(int ng){
  unsigned long half;
  unsigned long total = 0;
  int i;

  for(i=0; i < BINS_SIZE; i++){
    total += bins[ng][i];
  }

  half = total >> 1;
  total = 0;
  for(i=0; i < BINS_SIZE; i++){
    total += bins[ng][i];
    if(total > half){
      break;
    }
  }
  
  print_threshold(ng, i);
  
  return i;
}
