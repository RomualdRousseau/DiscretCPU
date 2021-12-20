; Compute Fibonacci Sequance

zp = $80
x = zp + 0
y = zp + 1
z = zp + 2
n = zp + 3

	nop
	in

	sta n

	lda #1
	sta x
	sta y
	
loop:
	out

	adc x
	sta z

	lda n
	sbc #1
	sta n
	beq end

	lda y
	sta x
	lda z
	sta y

	jmp loop

end:
	jmp end
