.model small

org 100h

.data
    numbersCount equ 10
    numbers db '0123456789'
    errorInput db 0Dh,0Ah,'You entered the wrong number!$'
    enter_first_num_alert db 0Dh,0Ah,'Enter the first number: $'    
    enter_second_num_alert db 0Dh,0Ah,0Dh,0Ah,'Enter the second number: $'
    sum_alert db 0Dh,0Ah,'first + second = $'
    sub1_alert db 0Dh,0Ah,'first - second = $'
    sub2_alert db 0Dh,0Ah,'second - first = $'
    mul_alert db 0Dh,0Ah,'first * second = $'
    div1_alertQuotient db 0Dh,0Ah,'first / second = $'
    div2_alertQuotient db 0Dh,0Ah,'second / first = $'
    remainder db ', remainder = $'
    ofMessage db 'OF$'    
    
    value1 dw 00h
    value2 dw 00h 
    res dd 00h
    result db '$$$$$$$$$$'
    
    min1 db 00h
    min2 db 00h
.code
START:

FIRST_INPUT:
    mov min1,00h
    mov value1,00h
    
    mov dx,offset enter_first_num_alert
    call output

    mov ah,01h
    int 21h
        
    cmp al,0Dh
    je FIRST_INPUT 
        
    cmp al,2Dh
    je .min1True
    
    push cx
    
    mov cx,numbersCount
    mov si,00h

FIRST_INPUT_TEST:    
    cmp al,numbers[si]
    je .trueFirstInput
    inc si
    loop FIRST_INPUT_TEST
    
    mov dx,offset errorInput
    call output
    jmp short FIRST_INPUT
      
    .min1True:
    mov min1,01h
    
    .trueFirstInput:
    mov cx,05h
    
    cmp al,2Dh
    je .startInput
    
    dec cx
    xor ah,ah
    sub al,30h
    mov value1,ax
    
    .startInput:
    inc cx
    push cx    

INPUT_NUMBER: 
    pop cx
    dec cx
    cmp cx,00h
    je .endInput
    
    mov ah,01h
    int 21h
    
    cmp al,0Dh
    je .endInput
    
    push cx
    mov si,00h
    mov cx,numbersCount

INPUT_TEST:    
    cmp al,numbers[si]
    je .numberEntry
    inc si
    loop INPUT_TEST    
    pop cx
    
    .OForNOTNUMBER:
    mov dx,offset errorInput
    call output
    jmp FIRST_INPUT
    
    .numberEntry:
    xor ah,ah
    sub al,30h
    mov bx,ax
    mov al,10
    mul value1
    jc .OForNOTNUMBER ;если произошло переполнение
    js .OForNOTNUMBER ;если знаковый бит стоит, число отрицательное
    add ax,bx
    jc .OForNOTNUMBER
    js .OForNOTNUMBER
    mov value1,ax
    jmp INPUT_NUMBER
    
    .endInput: ;перевод число в доп код
    cmp min1,01h ;проверяем флаг
    jne SECOND_INPUT
    mov ax,value1
    not ax
    add ax,1    
    jc .OForNOTNUMBER ;проверяем на переполнение
    jns .OForNOTNUMBER ;проверяем на отрицательное
    mov value1,ax
    
;==============================================================================

SECOND_INPUT:
    mov min2,00h
    mov value2,00h
    
    mov dx,offset enter_second_num_alert
    call output

    mov ah,01h
    int 21h
        
    cmp al,0Dh
    je SECOND_INPUT 
        
    cmp al,2Dh
    je .min2True
    
    push cx
    
    mov cx,numbersCount
    mov si,00h

SECOND_INPUT_TEST:    
    cmp al,numbers[si]
    je .trueSecondInput
    inc si
    loop SECOND_INPUT_TEST
    
    mov dx,offset errorInput
    call output
    jmp short SECOND_INPUT
      
    .min2True:
    mov min2,01h
    
    .trueSecondInput:
    mov cx,05h
    
    cmp al,2Dh
    je .startInput_2
    
    dec cx
    xor ah,ah
    sub al,30h
    mov value2,ax
    
    .startInput_2:
    inc cx
    push cx    

INPUT_NUMBER_2: 
    pop cx
    dec cx
    cmp cx,00h
    je .endInput_2
    
    mov ah,01h
    int 21h
    
    cmp al,0Dh
    je .endInput_2
    
    push cx
    mov si,00h
    mov cx,numbersCount

INPUT_TEST_2:    
    cmp al,numbers[si]
    je .numberEntry_2
    inc si
    loop INPUT_TEST_2    
    pop cx
    
    .OForNOTNUMBER_2:
    mov dx,offset errorInput
    call output
    jmp SECOND_INPUT
    
    .numberEntry_2:
    xor ah,ah
    sub al,30h
    mov bx,ax
    mov al,10
    mul value2
    jc .OForNOTNUMBER_2
    js .OForNOTNUMBER_2
    add ax,bx
    jc .OForNOTNUMBER_2
    js .OForNOTNUMBER_2
    mov value2,ax
    jmp INPUT_NUMBER_2
    
    .endInput_2:    
    cmp min2,01h
    jne SUM
    mov ax,value2
    not ax
    add ax,1    
    jc .OForNOTNUMBER_2
    jns .OForNOTNUMBER_2
    mov value2,ax

SUM:
    
    mov ax,value1
    cwd ;расширяем число лежит в dx:ax делает 4б
    
    mov cx,dx
    mov bx,ax
    
    mov ax,value2
    cwd
    
    add ax,bx ;складываем как многобайтные
    adc dx,cx 
    
    mov word ptr [res],ax ;заносим в res
    mov word ptr [res+2],dx

    mov dx,offset sum_alert
    call output
    
    call outputNumber ; выводит рес

SUB_1:

    mov ax,value1
    cwd 
    
    mov cx,dx
    mov bx,ax  
    
    mov ax,value2
    cwd
    
    sub bx,ax
    sbb cx,dx
    mov word ptr [res],bx
    mov word ptr [res+2],cx

    mov dx,offset sub1_alert
    call output
    
    call outputNumber

SUB_2:
    
    mov ax,value1
    cwd
    mov cx,dx
    mov bx,ax
    mov ax,value2
    cwd
    sub ax,bx
    sbb dx,cx
    mov word ptr [res],ax
    mov word ptr [res+2],dx

    mov dx,offset sub2_alert
    call output
    
    call outputNumber

MULL:
    
    mov ax,value1
    imul value2 ;умножение со знаком
    
    mov word ptr [res],ax ;мл
    mov word ptr [res+2],dx

    mov dx,offset mul_alert
    call output
    
    call outputNumber

DIV_1:
    mov ax,value1
    cwd    
    idiv value2 ;делим с учетом знака
    
    push dx  ;остаток
    mov dx,offset div1_alertQuotient
    call output
    mov word ptr [res],ax
    cwd ;расшир частное
    mov word ptr [res+2],dx
    call outputNumber
    mov dx,offset remainder
    call output
    pop ax ;остаток
    cwd
    mov word ptr [res],ax
    mov word ptr [res+2],dx 
    call outputNumber ;вывод остатка
    
DIV_2:
    mov ax,value2
    cwd
    idiv value1
    push dx
    mov dx,offset div2_alertQuotient
    call output
    mov word ptr [res],ax
    cwd
    mov word ptr [res+2],dx
    call outputNumber
    mov dx,offset remainder
    call output
    pop ax
    cwd
    mov word ptr [res],ax
    mov word ptr [res+2],dx 
    call outputNumber
    
    mov ax,4C00h
    int 21h
output proc
    push ax
    mov ah,09h
    int 21h
    pop ax
    ret    
output endp 

outputNumber proc
    mov si,00h
    mov bx,10          ;чтобы делить на 10 резалт чтобы отнимать кусочек и выводить
    mov result[0],30h  ; result - dd 4б
    mov result[1],'$'
    test res[2],0FFFFh ;побитовое и, если да sf-1 знач доп код
    jns .numberInput ;если прямой код
    
    not res ;переводим
    not res[2]
    inc res
    
    mov ah,02h ;выводим минус
    mov dl,'-'
    int 21h    
    
    .numberInput:
    mov ax,word ptr [res] ;младшая ax
    mov dx,word ptr [res+2] ;старшая часть ds
    cmp dx,0Ah ; если dx больше 0Аб то частное очень большое и не помещается в ах
    jge .OFreturn ;если так то
    .nextNumber:
    div bx ;делим ax dx на bx
    
    add dx,30h ;тут остаток
    mov result[si],dl
    
    cmp ax,00h
    je .exitNumberInput ;если частное 0 - выходим
    inc si
    xor dx,dx
    jmp short .nextNumber
    .exitNumberInput:
    inc si
    mov ah,02h ;прерывание выводт символы
    .inputNumber:
    dec si
    mov dl,result[si]
    int 21h
    
    cmp si,0h ;дошли ли до конца
    jne .inputNumber ; нет - выводим
   
    ret
    
    .OFreturn:
    mov dx,offset ofMessage
    call output
    ret    
outputNumber endp    

end START