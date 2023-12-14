
/* Bringup Test Software written by Edwin Chiu 2023
 *  To interface with the 96-Well LED Board
 *  Write to the array state[], an array with bytes with length equal to the number of chips on the board
 *  The bottom-left cell of the board (well H1) is byte 0, bit 0.
 *  The next cell up (cell G1) is byte 0, bit 1.
 *  Cell H2 is byte 1, bit 0.
 *  Cell G2 is byte 1, bit 1.
 *  ...etc
 *  Cell A12 is byte 7, bit 7.
 *  When you have written your intended pattern, call myLED.printDirect(state) to send the pattern to the board at time you desire.
 *  
 *  This sofware is based on and uses the TLC591x library by Andy4495: https://github.com/Andy4495/TLC591x
 *  To install this library in your Arduino IDE, go to Sketch -> Include Library -> Manage Libraries... -> Search for TL591x
 */

#include <TLC591x.h>
#if defined(ENERGIA_ARCH_MSP432R)
#include <stdio.h>
#endif

// Set up parameters
#define NUMCHIPS 12

// First parameter in constructor is # of TLC591x chips -- this example assumes 2 chips
// Constructor parameters: # of chips, SDI in, CLK pin, LE pin, OE pin (optional parameter)
TLC591x myLED(NUMCHIPS, 11, 13, 9);    // Uncomment if using software SPI and not using OE pin  NOTE THAT USING HARDWARE SPI SEEMS TO INTRODUCE TIMING JITTER AND RUNT SIGNALS
//TLC591x myLED(NUMCHIPS, 9);    // Uncomment if using hardware SPI and not using OE pin


// Set up array to hold LED values
uint8_t state[NUMCHIPS];

// Set up other variables
int nowTime = 0;

void setup() {
  
 //SPI.begin();  //uncomment only if using hardware SPI, comment otherwise
 
}

void loop() {
  int chipIndex = 0;

// First, blank the display
  for (int i=0; i < NUMCHIPS; i++) {
    state[i] = 0x00;
  }
  myLED.printDirect(state);
 
// One-by-one control test
  for (int i=0; i < NUMCHIPS*8; i++) {
    chipIndex = i/8;
    state[chipIndex] = pow(2,i%8);
    delay(100);
    myLED.printDirect(state);
    state[chipIndex] = 0x00;  // blank the line we just wrote
  }

 // Checkerboard (i.e. whole board) test
  for (int i=0; i < 10; i++) {
    for (int k=0; k < NUMCHIPS; k++) {
      (k+i)%2 == 0 ? state[k] = 0b01010101 : state[k] = 0b10101010;
    }
    delay(500);
    myLED.printDirect(state);
  }

// Performance test
  // 2ms
  for (int i=0; i < 5000; i++) {
    for (int k=0; k < NUMCHIPS; k++) {
      (k+i)%2 == 0 ? state[k] = 0b01010101 : state[k] = 0b10101010;
    }
    delay(2);
    myLED.printDirect(state);
  }
  
  // 1ms
  for (int i=0; i < 10000; i++) {
    for (int k=0; k < NUMCHIPS; k++) {
      (k+i)%2 == 0 ? state[k] = 0b01010101 : state[k] = 0b10101010;
    }
    delay(1);
    myLED.printDirect(state);
  }

  // 0.5ms
  for (int i=0; i < 20000; i++) {
    for (int k=0; k < NUMCHIPS; k++) {
      (k+i)%2 == 0 ? state[k] = 0b01010101 : state[k] = 0b10101010;
    }
    nowTime = micros();
    while (micros()<nowTime+500) {};      // Note this is an workaround. Arduino's delayMicroseconds() function is not accurate.
    myLED.printDirect(state);
  }

  // 0.25ms
  for (int i=0; i < 40000; i++) {
    for (int k=0; k < NUMCHIPS; k++) {
      (k+i)%2 == 0 ? state[k] = 0b01010101 : state[k] = 0b10101010;
    }
    nowTime = micros();
    while (micros()<nowTime+250) {};
    myLED.printDirect(state);
  }

  // without delay
  for (int i=0; i < 40000; i++) {
    for (int k=0; k < NUMCHIPS; k++) {
      (k+i)%2 == 0 ? state[k] = 0b01010101 : state[k] = 0b10101010;
    }
    myLED.printDirect(state);
  }

  // blank the board
  for (int i=0; i < NUMCHIPS; i++) {
    state[i] = 0x00;
  }
  myLED.printDirect(state);
  delay(1000);
  
}
