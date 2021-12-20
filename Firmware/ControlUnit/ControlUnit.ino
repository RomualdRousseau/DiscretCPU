#include "global.h"
#include "opcodes.h"

void setup() {

  // Setup pins I/O
  
  DDRB = B11111111 & ~DATA_HIGH;
  DDRC = B11111111 & ~DATA_LOW;
  DDRD = B11111111 & ~digitalPinToBitMask(CLOCK_PIN);

  // Setup SPI output

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  // Ouput to a stable state (0)

  PORTB &= ~SELECT_PIN;
  SPI.transfer(0);
  SPI.transfer(0);
  PORTB |= SELECT_PIN;

  // Fill microcodes with NOPs (containing one Von Newman Fetch)
  
  memset(microcodes, 0, sizeof(microcodes));
  for(int i = 0; i < 64; i++) {
      memcpy_P(microcodes[i], OP_NOP, sizeof(OP_NOP));
  }

  // Fill with instructions
  
  memcpy_P(microcodes[0x00 | 0x00 | 0x01], OP_LDA_i, sizeof(OP_LDA_i));
  memcpy_P(microcodes[0x10 | 0x00 | 0x01], OP_LDA_a, sizeof(OP_LDA_a));
  memcpy_P(microcodes[0x10 | 0x00 | 0x02], OP_STA_a, sizeof(OP_STA_a));

  memcpy_P(microcodes[0x00 | 0x00 | 0x05], OP_JMP_a, sizeof(OP_JMP_a));
  memcpy_P(microcodes[0x10 | 0x00 | 0x05], OP_BCS_ac, sizeof(OP_BCS_ac));
  memcpy_P(microcodes[0x20 | 0x00 | 0x05], OP_BEQ_az, sizeof(OP_BEQ_az));
  
  memcpy_P(microcodes[0x00 | 0x00 | 0x06], OP_OUT_A, sizeof(OP_OUT_A));
  memcpy_P(microcodes[0x00 | 0x00 | 0x07], OP_IN_A, sizeof(OP_IN_A));
  
  memcpy_P(microcodes[0x00 | 0x08 | 0x00], OP_ADD_i, sizeof(OP_ADD_i));
  memcpy_P(microcodes[0x10 | 0x08 | 0x00], OP_ADD_a, sizeof(OP_ADD_a));
  memcpy_P(microcodes[0x00 | 0x08 | 0x01], OP_SUB_i, sizeof(OP_SUB_i));
  memcpy_P(microcodes[0x10 | 0x08 | 0x01], OP_SUB_a, sizeof(OP_SUB_a));
  memcpy_P(microcodes[0x00 | 0x08 | 0x03], OP_CMP_i, sizeof(OP_CMP_i));
  memcpy_P(microcodes[0x10 | 0x08 | 0x03], OP_CMP_a, sizeof(OP_CMP_a));
  
  // Start the micro code counter

  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), nextMicroCodeFunc, FALLING);
}

void nextMicroCodeFunc() {
  count++;
}

void loop() {
  const byte opcode = PINC & DATA_LOW;
  const byte flags = PINB & DATA_HIGH;
  
  cli();

  // Skip microcodes depending of the flags

//  byte mask = (flags >> 2) | B00000100;
//  if ((opcode & mask) == mask) {
//    count++;
//  }
  byte mask = microcodes[opcode][count][0];
  while ((flags & mask) != mask) {
    count++;
    mask = microcodes[opcode][count][0];
  }

  // Fetch microcode controls

  const byte ctrl1 = microcodes[opcode][count][1];
  const byte ctrl2 = microcodes[opcode][count][2];

  // Reset counter if end of the microcodes for the instruction

  if (ctrl1 == 0 && ctrl2 == 0) {
    count = 0;
  }

  sei();

  // Output control bits 

  PORTB &= ~SELECT_PIN;
  SPI.transfer(ctrl2);
  SPI.transfer(ctrl1);
  PORTB |= SELECT_PIN;

  delayMicroseconds(10);
}
