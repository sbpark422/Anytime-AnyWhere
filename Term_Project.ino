#define CAP_THRESHOLD 2
#include "pins_arduino.h" 

int keys[] = {3,4,5,6,7,8,9,10};

// return a number from 0 to 17 according to the level of capacitance on the pin,
// when touching the pin the number will get higher
uint8_t readCapacitivePin(int pinToMeasure) {

  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;

  byte bitmask;

  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));

  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  delay(1);

  uint8_t SREG_old = SREG;

  noInterrupts();

  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // how long the pin to get pulled up. 
  
  uint8_t cycles = 17;

  if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}

  // turn interrupts back on if they were on before, or leave them off if they were off before
  SREG = SREG_old;


  // Discharge the pin again by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;

}

void setup() {
    Serial.begin(9600);    // init Serial communication
    
    // initialize row pins as INPUT_PULLUP to use the internal pull-up resistor 
    for(int i=0; i<8; i++) {
        pinMode(keys[i], INPUT_PULLUP);
    }
    
}

void loop() {
 for (int i = 0; i < 8; ++i) {
  
  //compare with a threshold
  if(readCapacitivePin(keys[i])>CAP_THRESHOLD){
    Serial.println(i+1);
      delay(500);
    }
  }
}


