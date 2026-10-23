MAIN

MOV AX,ENTERO       ; entero buscado
MOV BX, ARBOL       ; puntero al arbol a partir de ES:[BX]
CALL PERTENECE


PROC PERTENECE
    MOV CX , ES:[BX]        ; arbol[indice].dato

    CMP CX,AX               ; 

    JE ENCONTRADO           ; if(arbol[indice].dato == dato)
    JG RECURSION_IZQUIERDA  ; if(dato < arbol[indice].dato)
    JMP RECURSION_DERECHA   ; if(dato > arbol[indice].dato)

RECURSION_IZQUIERDA:
    MOV DL, ES:[BX+2]   ; unsigned char izq
    CMP DL,0            ; si es cero,  
    JE ARBOL_NULL       ; no tiene hijos  

    PUSH BX             ; de lo contrario guardamos el indice actual
    MOV BL, DL          ; colocamos en BX el indice del hijo izquierdo
    MOV BH, 0           ;
    SHL BX,1            ; BX = indice*2
    SHL BX,1            ; BX = indice*4    
    CALL PERTENECE      ;
    POP BX              ; Limipiamos la pila  
    RET                 ; Retorna el resultado (AL) al nivel superior


RECURSION_DERECHA:
    MOV DL, ES:[BX+3]   ; unsigned char der
    CMP DL,0            ; si  es cero
    JE ARBOL_NULL       ; no tiene hijos

    PUSH BX             ;de lo contrario guardamos el indice actual
    MOV BX,DL           ;colocamos en BX el indice del hijo derecho
    MOV BH, 0           ;
    SHL BX,1            ; BX = indice*2
    SHL BX,1            ; BX = indice*4   

    CALL PERTENECE      ;
    POP BX
    RET

ENCONTRADO:
    MOV CL,1         ; marco entontrado
    RET              ;   

ARBOL_NULL:
    MOV AL,0            ;
    RET                 ;

ENDPROC