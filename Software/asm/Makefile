.PHONY: clean

ASM = python asm.py
BURN = minipro -p AT28C256 -w

%.bin: %.asm
	$(ASM) -o $@ $< 

test1: test1.bin
	$(BURN) $<
	
test2: test2.bin
	$(BURN) $<

test3: test3.bin
	$(BURN) $<

test4: test4.bin
	$(BURN) $<

fibonacci: fibonacci.bin
	$(BURN) $<
	
clean:
	rm *.bin
		
