void log_starting(){
  Serial.println("\n");
  Serial.println("TRNG Starting...");
  
   switch(bias_removal){
    case VON_NEUMANN:
      Serial.println("The filtering applied is von Neumann"); 
      break;
    case EXCLUSIVE_OR:
      Serial.println("The filtering applied is XOR");
      break;
    case NO_BIAS_REMOVAL:
      Serial.println("No filtering applied");
      break;
  }
}
