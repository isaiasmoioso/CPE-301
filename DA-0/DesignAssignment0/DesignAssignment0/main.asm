;
; DesignAssignment0.asm
;
; Created: 2/16/2016 8:54:39 PM
; Author : Isaias Osorio
;


; Replace with your application code
start:
    ldi		r16,	33		;y
	ldi		r17,	36
	ldi		r18,	39
	ldi		r19,	42
	ldi		r20,	45

	sbi		DDRB,	2		; Port B set as output using pin 2
	out		PORTB,	r0		; Set all outputs to 0

	add		r20,	r16		;For some reason loading immediates only starting at register 16
	add		r20,	r17		;Add the integers
	add		r20,	r18
	add		r20,	r19
	

	brcc	End				; Carry flag
	ldi		r17,	4
	out		PORTB,	r17		;Port B, Set output high at pin2
End:
    rjmp	End