.model small
.stack 100h

.data   
;alerts
    enter_string_alert db "Enter string:",0Dh,0Ah,'$'
    enter_word_alert db 0Dh,0Ah,"Enter word:",0Dh,0Ah,'$'
    your_string_alert db 0Dh,0Ah,"Your string:",0Dh,0Ah,'$' 
    
    length equ 203   
    maxSybols equ 200
    string db length dup('$')
    subString db length dup('$')


.code 
OUTPUT_STRING proc
    mov ah, 09h
    int 21h    
ret
OUTPUT_STRING endp

INPUT_STRING proc
    mov ah, 0Ah
    int 21h
ret
INPUT_STRING endp
                     
                     
IS_EMPTY:
    mov ah, [string[1]]
    cmp ah, 0
    je OUTPUT_RESULT    
    mov al, [subString[1]] 
    cmp al, 0
    je OUTPUT_RESULT
    jmp IS_BIG_ENOUGH
    
IS_BIG_ENOUGH:
    cmp ah,al
    jg FIND_WORD
    jmp OUTPUT_RESULT

FIND_WORD:
    mov si, offset string[1]
    mov di, offset subString[2]    
    
FIND_FIRST_SYMBOL:
    call IS_END
    cmp [si], ' '
    je FIND_FIRST_SYMBOL
    mov dl, [si]  ;for cpm with another string symbol
    cmp dl, [di]    ;first subString symbol     
    je compareWords
    jmp skipWord
    
compareWords:
    inc di
    cmp [di], 0Dh   
    je CHEK_END_OF_WORD
    call IS_END
    mov dl, [si]  ;for cpm with another string symbol  
    cmp dl, [di]
    je compareWords
    mov di, offset subString[2] ;check first symbol of subStr again
    jmp skipWord

skipWord:
    call IS_END            
    cmp [si], ' '
    je FIND_FIRST_SYMBOL
    jmp skipWord

CHEK_END_OF_WORD:
    call IS_END
    cmp [si], ' '
    je FIND_NEXT_WORD_START
    mov di, offset subString[2] ;check first symbol of subStr again
    jmp skipWord

FIND_NEXT_WORD_START:
    call IS_END
    cmp [si], ' '
    je FIND_NEXT_WORD_START
    mov bx, si ;next word first symbol pos
    jmp FIND_NEXT_WORD_END

FIND_NEXT_WORD_END:
    inc si
    cmp [si], '$'
    je DELETE_NEXT_WORD
    cmp [si], ' '
    je DELETE_NEXT_WORD
    jmp FIND_NEXT_WORD_END
    
DELETE_NEXT_WORD:
    mov dl, [si]
    mov [bx], dl
    cmp [bx], '$'
    je OUTPUT_RESULT
    inc bx
    inc si
    jmp DELETE_NEXT_WORD
    
        
IS_END proc   ;check next symbol with '$' symbol
    inc si
    cmp [si], '$'
    je OUTPUT_RESULT
ret
IS_END endp 

;delete all subString words exept 1st
CONVERT_SUBSTRIGN_TO_WORD proc
    lea si, subString[1]
    
CONVERT_SUBSTRIGN_TO_WORD_LOOP:
    inc si    
    cmp [si], 0Dh
    je CONVERT_SUBSTRIGN_TO_WORD_END
    cmp [si], ' '
    jne CONVERT_SUBSTRIGN_TO_WORD_LOOP

    mov [si], 0Dh
    mov [si+1], '$'        
CONVERT_SUBSTRIGN_TO_WORD_END:    
ret                   

CONVERT_SUBSTRIGN_TO_WORD endp

START:

    mov ax, @data
    mov ds, ax 
    mov es, ax
    

    mov [string], maxSybols
    mov [subString], maxSybols
    
    mov dx, offset enter_string_alert  ;output enterStr
    call OUTPUT_STRING 
    
    mov dx, offset string      ;input string
    call INPUT_STRING
    
    mov dx, offset enter_word_alert    ;output enterSubStr
    call OUTPUT_STRING 
    
    mov dx, offset subString      ;input string
    call INPUT_STRING 
    
    call CONVERT_SUBSTRIGN_TO_WORD
    
    jmp IS_EMPTY
   
OUTPUT_RESULT:    
    
    mov dx, offset your_string_alert     ;output result
    call OUTPUT_STRING 
           
    mov dx, offset string[2]     ;output result
    call OUTPUT_STRING 
           
    
    ;mov ax, 4c00h ; exit to operating system.
    ;int 21h    
    mov     ah, 0 
    int     16h

end START ; set entry point and stop the assembler.