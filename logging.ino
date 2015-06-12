void log_starting(){
  Serial.println(F("\nTRNG Starting..."));

  Serial.print(rng_mode);
  Serial.println(F(" external noise generator(s) will be used"));
  
  Serial.print(F("The internal noise generator is "));
  
  if (rng_internal) {
    Serial.println(F("enabled"));
  } else {
      Serial.println(F("disabled"));
    }
  
  Serial.print(F("Filtering applied: "));
  
   switch(bias_removal){
    case VON_NEUMANN:
      Serial.println(F("von Neumann")); 
      break;
    case EXCLUSIVE_OR:
      Serial.println(F("xor"));
      break;
    case NO_BIAS_REMOVAL:
      Serial.println(F("none"));
      break;
  }

  Serial.print(F("The output format is "));

  switch(output_format){    
    case ASCII_BYTE:
      Serial.println(F("ASCII byte")); 
      break;
    case BINARY:
      Serial.println(F("binary"));
      break;
    case ASCII_BOOL:
      Serial.println(F("ASCII boolean"));
      break;
    case BYTE:
      Serial.println(F("byte"));
      break;
  }
}

void print_threshold(int ng, int threshold){
  Serial.print(F("\nThe threshold "));
  Serial.print(ng+1);
  Serial.print(F(" is: "));
  Serial.println(threshold);
}
