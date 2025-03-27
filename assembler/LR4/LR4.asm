 org $8000

 ; 8200..821f
 ; 8220..823f
 
 ldx #$8200
 ldy #$8220

LOOP:
 ldaa $0,x
 ldab $0,y
 
 anda #%00001111 
 andb #%11110000
 aba ;ycxm
 
 ldab $0,x
 staa $0,x
 ldaa $0,y
 
 anda #%00001111 
 andb #%11110000
 aba

 staa $0,y

CONTINUE:
 inx
 iny
 cpx #$8220 ;x-8220
 bne LOOP