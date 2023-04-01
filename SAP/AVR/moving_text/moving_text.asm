; definice pro nas typ procesoru
.include "m169def.inc"
; podprogramy pro praci s displejem
.org 0x1000
.include "print.inc"

; Zacatek programu - po resetu
.org 0


; Zacatek programu - hlavni program
	.dseg
.org 0x100
buf: .byte 0x100
	.cseg
jmp start
input: .db "DLOUHY TEXT", 0

start:
    ; Inicializace zasobniku
	ldi r16, 0xFF
	out SPL, r16
	ldi r16, 0x04
	out SPH, r16
    ; Inicializace displeje
	call init_disp

	; *** ZDE muzeme psat nase instrukce

	ldi r30, low(input*2) ; Inicializace, pouze Z ukazuje do PM
	ldi r31, high(input*2)

	ldi r28, low(buf) ; Y
	ldi r29, high(buf)
	
	ldi r20, 6
	inc r20
	mov r15, r20; delka display
	
	ldi r22, 1 ; nastaveni smeru - 0 zprava - 1 zleva
	cpi r22, 0
	breq right

	
	ldi r21, 32
	ldi r20, 0
	mov r2, r20
	mov r3, r20
	mov r4, r20
	mov r5, r20
	mov r6, r20

	st y+, r20

loadst:
	lpm r20, z+
	cpi r20, 0
	breq fillzeros
	st y+, r20
	jmp loadst	
fillzeros:
	/*st y+, r20
	st y+, r20
	st y+, r20
	st y+, r20
	st y+, r20*/
	jmp skipright

right:
	ldi r20, 0
	mov r1, r20
	mov r2, r20
	mov r3, r20
	mov r4, r20
	mov r5, r20
	ldi r26, 32

skipright:
	
	ldi r20, 5 ; count when finishing sequence

	cycle:
		ldi r17, 2 ; char pos
		cpi r22, 1
		breq continueleft

		ldi r28, low(buf)
		mov r1, r2 ; pousovani
		st y+, r1
		mov r2, r3
		st y+, r2
		mov r3, r4
		st y+, r3
		mov r4, r5
		st y+, r4
		mov r5, r26
		st y+, r5

		cpi r26, 0
		breq skipr26

		lpm r26, z+
		st y+, r26

	skipr26:
		ldi r28, low(buf)

		jmp print



	continueleft:
		jmp print

	continue:

		cpi r26, 0
		breq finish
	back:	
		call wait
		jmp cycle

	again:
		call wait
		jmp start	

	jmp end
end: jmp end ; should never get here

finish:
	ldi r26, 0
	cpi r20, 0
	breq again
	dec r20
	jmp back

wait:
	ldi r27, 3
	cek3: 
		ldi r18, 200
		cek2: 
			ldi r19, 200
			cek:
				dec r19
		    	brne cek
    		dec r18
    		brne cek2
	dec r27
	brne cek3
	ret

print:
	cpi r22, 0
	breq printright
	ld r16, -y
	continueprinting: 
	
	cpi r16, 0
	breq zero
	call show_char
next:
	cp r17, r15 ; cpi r17, 7
	breq continue
	inc r17
	jmp print

zero:
	ldi r16, 32
	call show_char
	jmp next

printright:
	ld r16, y+
	jmp continueprinting






	
