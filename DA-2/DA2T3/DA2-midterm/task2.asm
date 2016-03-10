;
; TASK 2 - ASM
;
; 
; Author : Isaias Osorio
;
;
; TASK 1 - ASM
;
; Created: 2/18/2016 8:07:11 PM
; Author : Isaias Osorio
;


	SBI DDRC,0		;PC0 as an output
	LDI R17,0x01
	LDI R16, 0x01
	OUT PORTC,R17		;PB5&4 = 0
	LDI R18, 0
	LDI R19, 0X01

BEGIN:
	RCALL DELAY
	EOR R17,R16			;toggle D5 of R17;
	CP	R17, R19
	BRNE SKIP
	INC	R18
	OUT PORTB, R19
SKIP:
	OUT PORTB,R17		;toggle PB5
	RJMP BEGIN


DELAY:
	LDI R20, HIGH(34286)
	STS TCNT1H, R20		;TCNT1H = 0xA4 timer1 high
	LDI R20, LOW(34286)
	STS TCNT1L, R20	;TCNT1L = 0x72 timer1 low
	LDI R20,0x00
	STS TCCR1A, R20		;WGM11:10 = 00
	LDI R20,0x03
	STS TCCR1B, R20		;WGM13:12 = 05, Normal mode, prescaler = 1024

AGAIN:
	IN R20,TIFR1		;read TIFR
	SBRS R20,TOV1		;if TOV1 is set skip next instruction
	RJMP AGAIN
	LDI R20,0x00
	STS TCCR1B,R20		;stop Timer1
	LDI R20,0xFF
	OUT TIFR1, R20		;clear TOV1 flag
	RET
