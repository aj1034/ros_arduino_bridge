/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_rear_enc_pos = 0L;
  volatile long left_front_enc_pos = 0L;
  volatile long right_rear_enc_pos = 0L;
  volatile long right_front_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_rear_last=0;        
	  enc_rear_last <<=2; //shift previous state two places
	  enc_rear_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_rear_enc_pos += ENC_STATES[(enc_rear_last & 0x0f)];

    static uint8_t enc_front_last=0;        
	  enc_front_last <<=2; //shift previous state two places
	  enc_front_last |= (PIND & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
  	left_front_enc_pos += ENC_STATES[(enc_front_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
    static uint8_t enc_rear_last=0;      	
    enc_rear_last <<=2; //shift previous state two places
	  enc_lrear_ast |= (PINC & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
  	right_rear_enc_pos += ENC_STATES[(enc_rear_last & 0x0f)];


    static uint8_t enc_front_last=0;      	
    enc_front_last <<=2; //shift previous state two places
	  enc_front_last |= (PINC & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	right_front_enc_pos += ENC_STATES[(enc_front_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT_REAR) return left_rear_enc_pos;
    else if (i== LEFT_FRONT) return left_front_enc_pos;
    else if (i == RIGHT_REAR) return right_rear_enc_pos;
    else return right_front_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT_REAR){
      left_rear_enc_pos=0L;
      return;
    }
    else if (i == LEFT_FRONT){
      left_front_enc_pos=0L;
      return;      
    }
    else if(i == RIGHT_REAR){
      right_rear_enc_pos=0L;
      return;
    }
    else { 
      right_front_enc_pos=0L;
      return;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT_REAR);
  resetEncoder(LEFT_FRONT);
  resetEncoder(RIGHT_REAR);
  resetEncoder(RIGHT_FRONT);
}

#endif

