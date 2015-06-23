/********************************/
/*  Rob Seward 2008-2009        */
/*  v1.0                        */
/*  4/20/2009                   */
/*                              */
/*  Extended by Daniel Romao    */
/*  6/12/2015                   */
/********************************/

#include <SoftwareSerial.h>
#include <Entropy.h>

SoftwareSerial rngSerial(10, 11);

#define BINS_SIZE 256
#define CALIBRATION_SIZE 50000

#define NO_BIAS_REMOVAL 0
#define EXCLUSIVE_OR 1
#define VON_NEUMANN 2

#define ASCII_BYTE 0
#define BINARY 1
#define ASCII_BOOL 2
#define BYTE 3

#define INTERNAL_ONLY 0
#define SINGLE 1
#define DUAL 2

/***  Configure the RNG **************/
int rng_mode = DUAL;
int rng_internal = false;
int bias_removal = EXCLUSIVE_OR;
int output_format = BYTE;
int baud_rate = 19200;
/*************************************/

unsigned int bins[2][BINS_SIZE];
int adc_pins[] = {4, 5};
int led_pin = 13;
boolean initializing = true;
unsigned int calibration_counter = 0;
byte threshold[2];


void setup(){
  pinMode(led_pin, OUTPUT);
  Serial.begin(baud_rate);
  
  for (int i=0; i < rng_mode; i++){
      clear_bins(i);
  }
  
  if (rng_internal){
    Entropy.initialize();
  }
  
  rngSerial.begin(baud_rate);
  log_starting();
}

void loop(){

  byte adc_byte[2];
  int adc_value;
  int i;
  
  for (i=0; i < rng_mode; i++){
    adc_value = analogRead(adc_pins[i]);
    adc_byte[i] = adc_value >> 2;
  }
    
  if (calibration_counter >= CALIBRATION_SIZE){
  
    for (i=0; i < rng_mode; i++){
      threshold[i] = findThreshold(i);
      clear_bins(i);
    }
  
    calibration_counter = 0;
    initializing = false;
  }
  
  for (i=0; i < rng_mode; i++){
    calibrate(adc_byte[i], i);
  }
  
  if (rng_mode != INTERNAL_ONLY){
    calibration_counter++;
  }

  if (initializing == false || rng_mode == INTERNAL_ONLY){
    processInput(adc_byte, threshold);
  } else {
      printStatus();
    }
}

void processInput(byte adc_byte[], byte threshold[]){
  boolean input_bool[2];
  boolean input_bool_after;
  int i;
  
  for (i=0; i < rng_mode; i++){
    input_bool[i] = (adc_byte[i] < threshold[i]) ? 1 : 0;
  }
     
  if (rng_mode == DUAL){
    input_bool_after = input_bool[0] ^ input_bool[1];
  } else if (rng_mode == SINGLE) {
      input_bool_after = input_bool[0];
    }

  if (rng_internal){
    uint8_t bool_internal = Entropy.random(2);
    if (rng_mode == INTERNAL_ONLY){
      input_bool_after = bool_internal;
    } else {
        input_bool_after ^= bool_internal;
      }
  }
    
  switch(bias_removal){
    case VON_NEUMANN:
      vonNeumann(input_bool_after); 
      break;
    case EXCLUSIVE_OR:
      exclusiveOr(input_bool_after);
      break;
    case NO_BIAS_REMOVAL:
      buildByte(input_bool_after);
      break;
  }
}


void buildByte(boolean input){
  static int byte_counter = 0;
  static byte out = 0;

  if (input == 1){
    out = (out << 1) | 0x01;
  }
  else{
    out = (out << 1);
  }
  byte_counter++;
  byte_counter %= 8;
  if(byte_counter == 0){
    if (output_format == ASCII_BYTE) rngSerial.println(out, DEC);
    if (output_format == BINARY) rngSerial.print(out, BIN);
    if (output_format == BYTE) rngSerial.write(out);
    out = 0;  
  }
  if (output_format == ASCII_BOOL) rngSerial.print(input, DEC);
}

