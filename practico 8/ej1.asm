; Ejercicio 1 -  Practico 8

; INPUT:    .indiceLista = BX
            .bufferDestino ES:[tope de pila]


MAIN

MOV BX, indiceLista         ;
MOV AX, bufferDestino       ;
PUSH AX                     ;  <---- Segundo elemento de pila
CALL CONSTRUIRCADENA        ;  <---- Tope de Pila
POP AX                      ;



PROC CONSTRUIRCADENA

    POP AX                  ; <- quito  direccion de retorno, para acceder al offset
    POP DI                  ; <- Obtengo el offset
    PUSH DI                 ; <- la letra pide que dejemos todo igual
    PUSH AX                 ; <- Dejo nuevamente en tope de pila la direccion de retorno

    WHILE:
        CMP BX,0
        JGE ELSE
        MOV BYTE PTR ES:[DI] , 0    ; buferDestino = 0
        RET
    
    ELSE:
        MOV AX , BX         ; 
        SHL BX, 1           ;
        ADD BX, AX          ; BX = INDICE x 3
        MOV CL, [BX+SI]     ; temporal
        MOV ES:[DI],CL      ; buferdestino  = lista[indideLista]

        INC DI              ; DI  = DI + 1 
        MOV BX, [BX+SI+1]   ; ES:[SI] = comienzo de lista, BX item que estoy trabajando, quiero el siguiente
        PUSH DI             ; se pasa por stack
        CALL CONSTRUIRCADENA
        POP DI
        RET
        
ENDPROC