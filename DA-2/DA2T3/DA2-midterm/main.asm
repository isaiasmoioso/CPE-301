; TASK 3 - ASM
; Created: 2/18/2016 8:07:11 PM
; Author : Isaias Osorio
;


	SBI DDRC, 5			;PC5 as an output
	SBI DDRC, 4			;PC6 as an output
	LDI R16, 0XFF
	OUT DDRB, R16		;SET PB AS OUTPUT
	LDI R17, 0x01
	LDI R16, 0x01
	LDI R18, 0			;count on every rising edge
	LDI R21, 0			;count on every 5 rising edges
	LDI R22, 0			;count on every 10 rising edges
	LDI R23, 0X00		;use for to toggle pin 4
	LDI R24, 0X00		;used to toggle pin 5

BEGIN:
	RCALL DELAY
	EOR R17,R16			;toggle D5 of R17;
	CP	R17, R16
	BRNE SKIP
	INC	R18
	INC R21				;increment every5rising
	INC R22				;increment every10rising
	CPI R21, 5			;Checks to see if 5 rising edges have passed
	BREQ FIVE			
CHECKTEN:
	CPI R22, 10			;Checks to see if 10 rising edges have passed
	BREQ TEN
SKIP:
	OUT PORTB, R18		;toggle PB5
	RJMP BEGIN			

FIVE:
	LDI R21, 0
	LDI R16, 0x10
	IN R23, PORTC
	EOR R23,  R16
	OUT PORTC,R23		;toggle PB5
	LDI R16, 0x01
	RJMP CHECKTEN

TEN:
	LDI R22, 0
	LDI	R16, 0x20
	EOR R24, R16		;TOGGLE PB4
	OUT PORTC, R24
	LDI R16, 0X01
	RJMP SKIP

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
