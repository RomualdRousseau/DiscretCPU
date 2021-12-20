#include <SPI.h>

#define CLOCK_PIN      3
#define SELECT_PIN     B00000100
#define DATA_HIGH      B11000000
#define DATA_LOW       B00111111

#define ALWAYS        B00000000
#define IF_ZER        B10000000
#define IF_CAR        B01000000

#define PC_I        _BV(0)
#define PC_EN       _BV(1)
#define PC_O        _BV(2)
#define MAR_I       _BV(3)
#define MDR_I       _BV(5) | _BV(6)
#define MDR_O       _BV(6)
#define ALU_O       _BV(4)
#define CIR_I       _BV(7)

#define A_I         _BV(0)
#define A_O         _BV(1)
#define B_I         _BV(2)
#define B_O         _BV(3)
#define OUT_I       _BV(4)
#define IN_O        _BV(5)

byte microcodes[64][8][3];

volatile byte count = 0;
