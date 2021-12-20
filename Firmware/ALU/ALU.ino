void setup() {
  DDRA = B11110000;
  DDRB = B11100000;
}

void loop() {
  byte in1 = PINA & B00001111;
  byte in2 = PINB & B00001111;
  byte ci = (PINB & B00010000) >> 4;

  byte result = ci + in1 + in2;

  byte out = (result & B00001111) << 4;
  byte co = (result > 15) ? B00100000 : B00000000;

  PORTA = (PORTA & B00001111) | out;
  PORTB = (PORTB & B11011111) | co;
}
