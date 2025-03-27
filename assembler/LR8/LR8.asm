.model small   
.stack 100h
.data  
    noDataStr db "No data!", '$'
    noFileStr db "The file with this name doesn't exist!", '$'
    amountStr db "The amount of non-empty lines is:", 9h, '$'  
    procFinStr db "File processing has finished.", '$'
	finStr db "Program executed successfully.", '$'
	addAmountStr db " additional amount:", 9h, '$' 
    endl db 0Dh, 0Ah, '$'
        
    errMessage1 db "File not found!", '$' 
    errMessage2 db "Path not found!", '$'
    errMessage3 db "Access denied!", '$'   
    errMessage4 db "Read error", '$'

    maxCmdLen equ 126
    cmdLen dw ? 
    cmdLine db 126 dup(?)
    
    fileDescr dw ?      
    bufSize equ 50
    buf db bufSize+2 dup('$') 
    
    addAmount dw 0 
    nonEmptyLines dw 0
    chars dw 0    
    cf dw 0 
    eof dw 0
.code                                     
 
print_str macro string
    pusha
    lea dx, string
    mov ah, 09h
    int 21h
    popa
endm 

macro exit
   mov ax,4C00h
   int 21h  
endm

 
start: 
    mov ax, @data
    mov ds, ax    
    call getComArgs    
    
    mov ax, cmdLen  
    cmp cmdLen, 1
    jle noData
    
    lea dx, cmdLine
    call fopen
    cmp ax, 1
    je endMain
    
    call countNonEmptyLines
    
    print_str amountStr
    
    mov ax, nonEmptyLines
    call printDecNumber
    print_str endl
    
    call fclose
    print_str procFinStr
    print_str endl
    
    jmp endMain  
    
noData: 
    print_str noDataStr
    print_str endl   
endMain:
    print_str finStr
    print_str endl 
    exit 
    
getComArgs proc 
    
    push ax
    push cx
    
    mov cx, 0
	mov cl, es:[80h]		
	mov cmdLen, cx
	cmp cx, 1
	jle endGCA 		           
    
	cld
	mov di, 81h         
	mov al, ' '
	rep scasb   
	dec di
	
	lea si, cmdLine
skip:
    mov al,es:[di]
    cmp al, 0dh ;/r
    je endSkip
    cmp al, 20h ;space
    je endSkip 
    cmp al, 9h  ;tab
    je endSkip
    mov ds:[si], al 
    inc di
    inc si
    jmp skip  
       	
endSkip:
    inc si
    mov ds:[si], word ptr '$'   
             
endGCA:
    pop cx
    pop ax    
    ret
endp getComArgs                            

fopen proc

    push cx 

    mov ah, 3dh
    mov al, 0h
    int 21h
        
    jc errorHandling
    
    mov fileDescr, ax
    jmp fopenOk
    
errorHandling:

    cmp al, 02h
    jne pathNotFound
    print_str errMessage1
    print_str endl
    jmp fopenError
    
pathNotFound:

    cmp al, 03h
    jne accessDenied 
     print_str errMessage2
    print_str endl
    jmp fopenError
      
accessDenied:

    cmp al, 05h
    jne fopenError 
    print_str errMessage3
    print_str endl
    jmp fopenError
    
fopenOk:
    mov ax, 0 
    jmp fopenEnd
fopenError: 
    mov ax, 1
fopenEnd:
    pop cx    
    ret 

fopen endp                               

fclose proc
    mov bx, fileDescr
    mov ah, 3eh
    int 21h ;  
    
    jnc fcloseOk   
    
    mov ax, 1
    jmp fcloseFin 
    
fcloseOk :
    mov ax, 0 
fcloseFin:
    ret
fclose endp                               


countNonEmptyLines proc 
    pusha
    
    mov nonEmptyLines, 0
    mov chars, 0 
    mov addAmount, 0
    mov cf, 0 
    mov eof, 0
    mov bx, fileDescr
handling:
    call readFromFile 
    cmp ax, 1
    je finCounting
    cmp cx, bufSize   
    jb lastOperation  

    call scanBuf      ; 

    jmp handling

lastOperation:
    mov eof, 1
    call scanBuf
    jmp finCounting
    
finCounting: 
    popa
    ret
countNonEmptyLines endp                  

readFromFile proc  
    mov ax, 0
    mov ah, 3fh
    mov cx, 50
    lea dx, buf 
    int 21h
    
    jc FRRerror 
    
    mov cx, ax
    mov ax, 0
    jmp FRRend

FRRerror:
    print_str errMessage4
    print_str endl
    mov ax, 1

FRRend:
    ret
readFromFile endp                         

scanBuf proc
    lea si, buf
    push ax
    
scan:
    lodsb 
    
        
    cmp al, 13  ;
    je setCF 

    cmp al, 10 
    je handlEndl
    
    cmp al, 0
    je handlEndl
    
    cmp al, 20 
    je nextB
    
    cmp al, ' '
    je nextB
    cmp al, 9
    je nextB
   
    
    inc chars       
    jmp nextB

setCF:
    mov cf, 1
    jmp nextB

handlEndl:       
    cmp cf, 1
    jne nextB
    mov cf, 0
    cmp chars, 0
    je nextB
    mov chars, 0
    inc nonEmptyLines
    jo handleOverflow
    jmp nextB 

handleOverflow:
    inc addAmount
    mov ax, addAmount
    call printDecNumber
    
    print_str addAmountStr
    
    dec nonEmptyLines 
    mov ax, nonEmptyLines
    call printDecNumber
    print_str endl    
    
    mov nonEmptyLines, 0
    inc nonEmptyLines
        
nextB:        
    loop scan
    
    cmp chars, 0
    je endSB
    cmp eof, 0
    je endSB
    mov chars, 0
    inc nonEmptyLines
    jo handleOverflow
     
endSB:                  
    pop ax
    ret
scanBuf endp                                

printDecNumber proc
    pusha
    xor cx, cx
    mov bx, 10
loop1:        
    xor dx, dx
    div bx
    push dx 
    inc cx
    cmp ax, 0
    ja loop1

loop2:
    pop dx
    add dx, 30h
    mov ah, 2
    int 21h
    loop loop2
    popa    
    ret    
printDecNumber endp 
end start
