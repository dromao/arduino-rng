                                          
/********************************/
/*  Rob Seward 2008-2009        */
/*  v1.0                        */
/*  4/20/2009                   */
/*                              */
/*  Modified by Daniel Romao    */
/*  6/30/2015                   */
/********************************/

#include <SoftwareSerial.h>

SoftwareSerial rngSerial(10, 11); // RX (Green), TX (White)

#define BINS_SIZE 256
#define CALIBRATION_SIZE 50000
//#define CALIBRATION_SIZE 5000

#define NO_BIAS_REMOVAL 0
#define EXCLUSIVE_OR 1
#define VON_NEUMANN 2

#define ASCII_BYTE 0
#define BINARY 1
#define ASCII_BOOL 2
#define BYTE 3

/***  Configure the RNG **************/
int bias_removal = VON_NEUMANN;
int output_format = BINARY;
int baud_rate = 19200;
/*************************************/


unsigned int bins[BINS_SIZE];
int adc_pin = 5;
int led_pin = 13;
boolean initializing = true;
unsigned int calibration_counter = 0;
byte threshold;


void setup(){
  pinMode(led_pin, OUTPUT);
  Serial.begin(baud_rate);
  clear_bins();
  
  rngSerial.begin(baud_rate);
  log_starting();  
}

void loop(){

  int adc_value = analogRead(adc_pin);
  byte adc_byte = adc_value >> 2;
  
  if(calibration_counter >= CALIBRATION_SIZE){
    threshold = findThreshold();
    calibration_counter = 0;
    clear_bins();
    initializing = false;
  }
  
  calibrate(adc_byte);
  calibration_counter++;
  
  if(initializing == false){
    processInput(adc_byte, threshold);
  } else {
      printStatus();
    }
}

void processInput(byte adc_byte, byte threshold){
  boolean input_bool;
  input_bool = (adc_byte < threshold) ? 1 : 0;
  switch(bias_removal){
    case VON_NEUMANN:
      vonNeumann(input_bool); 
      break;
    case EXCLUSIVE_OR:
      exclusiveOr(input_bool);
      break;
    case NO_BIAS_REMOVAL:
      buildByte(input_bool);
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

