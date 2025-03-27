.model tiny
		        
.code 		
	org 100h  

start:    	
	                                     
   	mov ah,9h 		      
  	mov dx,offset message        
  		
	int 21h
     
    ret
     
    message db 07h, "Lap04k@/[S@sh04K@!]" ,0Dh,0Ah,'$'	
     
end start      