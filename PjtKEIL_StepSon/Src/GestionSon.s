	PRESERVE8
	THUMB   
		
	export CallbackSon
	export SortieSon
	import LongueurSon
	import Son
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
SortieSon dcw 0
				
position dcw 0
			
				
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


CallbackSon PROC
	push {lr}
	
	ldr r1,=LongueurSon
	ldr r2,=position
	ldr r3,[r2]
	ldr r4,[r1]
	
	cmp r3,r4 
	bge Sortie ; if (position >= LongueurSon)
	
	ldr r5,=Son
	ldrsh r6,[r5,r3,lsl #1] ; chargement de la valeur de Son[position]
	ldr r7,=360
	ldr r8,=37267
	
	
	; on fait : son[position]* (360/37267)+360
	mul r6,r6,r7
	sdiv r6,r6,r8
	add r6,r6,r7
	
	ldr r9,=SortieSon
	strh r6,[r9]
	
	add r3,r3,#1
	strh r3,[r2] ; on incremente position

	
Sortie ; si position >= LongueurSon
	pop {lr}
	bx lr
	
	ENDP


		
		
	END	