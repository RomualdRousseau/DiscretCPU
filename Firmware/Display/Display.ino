#include <SPI.h>

#define SELECT_PIN   B00000100
#define MODE_PIN     B00000010
#define DATA_HIGH   B11000000
#define DATA_LOW    B00111111

#define MINUS           10
#define PLUS             11

#define DIGIT1            (1 << 3)
#define DIGIT2            (1 << 2)
#define DIGIT3            (1 << 1)
#define DIGIT4            (1 << 0)

const byte glyphes[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111, // 9
  B01000000, // -
  B00000000  // +
};

void setup() {

  // Configure inputs pins (data and mode)
  
  DDRB = B11111111 & ~DATA_HIGH & ~MODE_PIN;
  DDRC = B11111111 & ~DATA_LOW;

  // Configure SPI

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
}

void loop() {

  // Get data and mode
  
  const byte data = (PINB & DATA_HIGH) | (PINC & DATA_LOW);
  const int value = ((PINB & MODE_PIN) == MODE_PIN) ? (char) data : data;
  const int abs_value = abs(value);

  // Dispay each digits

  printGlyph(DIGIT1, abs_value % 10);
  printGlyph(DIGIT2, (abs_value / 10) % 10);
  printGlyph(DIGIT3, (abs_value / 100) % 10);

  // Dispay the sign

  printGlyph(DIGIT4, (value < 0) ? MINUS : PLUS);
}

void printGlyph(byte n, byte g) {
  PORTB &= ~SELECT_PIN;
  SPI.transfer(glyphes[g]);
  SPI.transfer(~n);
  PORTB |= SELECT_PIN;
}
