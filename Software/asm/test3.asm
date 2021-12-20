zp = $80
x = zp + 0

	in
	sta x

loop:
	lda x
	out

	sbc #1
	sta x

	beq end
	jmp loop
	
	lda x
	out

end:	
	jmp end 


