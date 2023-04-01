; definice pro nas typ procesoru
.include "m169def.inc"
; podprogramy pro praci s displejem
.org 0x1000
.include "print.inc"

; Zacatek programu - po resetu
.org 0
jmp start

; Zacatek programu - hlavni program
.org 0x100
start:
    ; Inicializace zasobniku
    ldi r16, 0xFF
    out SPL, r16
    ldi r16, 0x04
    out SPH, r16
    ; Inicializace displeje
    call init_disp
    ; Inicializace joysticku
    call init_joy

    ldi r17, 2           ; nastaveni pozice pro vypis stavu
	ldi r21, 0			 ;

main_loop:               ; hlavni smycka
	ldi r17, 2
    call read_joy        ; nacti stav joysticku do r20
    cpi r20, 0           ; podivej se, co je v nem za hodnotu
    brne yes_enter        ; je enter -> preskoc

    
    ldi r16, 'S'         ; neni enter
	call show_char

	ldi r16, 'T'
	inc r17
	call show_char

	ldi r16, 'A'
	inc r17
	call show_char

	ldi r16, 'R'
	inc r17
	call show_char

	ldi r16, 'T'
	inc r17
	call show_char

	jmp main_loop



yes_enter:
	ldi r16, 32         ; je enter
	inc  r17
	call show_char
	inc  r17
	call show_char
	inc  r17
	call show_char
	inc  r17
	call show_char
	
	ldi r17, 2

	ldi r16, 48
    call sequence
	mov r1, r16

	inc r17
	ldi r16, 48
	call sequence
	mov r2, r16

	inc r17
	ldi r16, 48
	call sequence
	mov r3, r16
	
	ldi r25, 0    ; bude se loopovat lvípiss
	cp r1, r2
	brne loser

	cp r2, r3
	brne loser ; otherwise go to winner

winner:
	ldi r17, 2
	ldi r16, 'W'         
	call show_char

	ldi r16, 'I'
	inc r17
	call show_char

	ldi r16, 'N'
	inc r17
	call show_char

	ldi r16, 'N'
	inc r17
	call show_char

	ldi r16, 'E'
	inc r17
	call show_char

	ldi r16, 'R'
	inc r17
	call show_char
	
	ldi r22, 7
	call wait
	call clear_screen
	ldi r22, 7
	call wait

	inc r25
	cpi r25, 3
	brne winner

	jmp main_loop	


loser:
	ldi r17, 2
	ldi r16, 'L'         
	call show_char

	ldi r16, 'O'
	inc r17
	call show_char

	ldi r16, 'S'
	inc r17
	call show_char

	ldi r16, 'E'
	inc r17
	call show_char

	ldi r16, 'R'
	inc r17
	call show_char
	
	ldi r22, 7
	call wait
	call clear_screen
	ldi r22, 7
	call wait

	inc r25
	cpi r25, 3
	brne loser

	jmp main_loop	

clear_screen:
	ldi r17, 2
	ldi r16, 32
	call clear_screen_loop
	ret

clear_screen_loop:
	call show_char
	inc r17
	cpi r17, 8
	brne clear_screen_loop
	ret

sequence:
	call show_char

	ldi r22, 3
	call wait

	call read_joy        ; nacti stav joysticku do r20
    cpi r20, 0           ; podivej se, co je v nem za hodnotu
    brne skipped

	inc r16
	cpi r16, 58
	brne sequence

	ldi r16, 48
	jmp sequence

skipped:
	ret

wait:
	
	cek3: 
		ldi r23, 150
		cek2: 
			ldi r24, 200
			cek:
				dec r24
		    	brne cek
    		dec r23
    		brne cek2
	dec r22
	brne cek3
	ret

end: jmp end

init_joy:                ; inicializace joysticku
    in r17, DDRE
    andi r17, 0b11110011
    in r16, PORTE
    ori r16, 0b00001100
    out DDRE, r17
    out PORTE, r16
    ldi r16, 0b00000000
    sts DIDR1, r16
    in r17, DDRB
    andi r17, 0b00101111
    in r16, PORTB
    ori r16, 0b11010000
    out DDRB, r17
    out PORTB, r16
ret

read_joy:                ; ulozi smer joysticku do registru r20
    push r16             ; uklid r16 a r17
    push r17

joy_reread:
    in r16, PINB         ; nacti hodnotu joysticku 1

    ldi r20, 255         ; chvili cekej 2
joy_wait: dec r20
    brne joy_wait

    in r17, PINB         ; nacti jeste jednou

    andi r16, 0b00010000 ; vymaskuj ostatni bity 3
    andi r17, 0b00010000

    cp r16, r17
    brne joy_reread      ; hodnoty se nerovnaly -> nacti znovu

    ldi r20, 0           ; vychozi hodnota - nic neni aktivni
    cpi r16, 0
    brne joy_no_enter    ; hodnota je inverzni -> neni 0 znamena neni aktivni 4
	cp r20, r21
	brne pressed_enter
	ldi r20, 1           ; r20 = 1, kdyz je enter aktivni
	ldi r21, 1
	jmp pressed_enter

joy_no_enter:
	ldi r21, 0

pressed_enter:
   pop r17               ; obnoveni r16 a r17
   pop r16
ret
