void exclusiveOr(byte input){
  static boolean flip_flop = 0;
  flip_flop = !flip_flop;
  buildByte(flip_flop ^ input);
}

void vonNeumann(byte input){
  static int count = 1;
  static boolean previous = 0;
  static boolean flip_flop = 0;
  
  flip_flop = !flip_flop;

  if(flip_flop){
    if(input == 1 && previous == 0){
      buildByte(0);
    }
    else if (input == 0 && previous == 1){
      buildByte(1); 
    }
  }
  previous = input;
}

