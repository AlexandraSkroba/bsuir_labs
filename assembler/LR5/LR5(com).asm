.model small

org 100h  

.data
    message db 07h, "Lap04k@/[S@sh04K@!]" ,0Dh,0Ah,'$'	    
		        
.code 		

start:    	
    mov bx,@data	    
    mov ds,bx
	                                     
   	mov ah,9h 		      
  	mov dx,offset message        
  		
	int 21h
     
    mov ax,4C00h
    int 21h
              
end start      