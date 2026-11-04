PUSH arbol
PUSH 0 ; índice
PUSH valor
CALL buscarABB
POP AX ; resultado

PROC BUSCARABB

    PUSH BP
    MOV BP,SP

    PUSH AX             ;
    PUSH CX             ;
    PUSH BX             ;

    MOV BX , [BP+6]     ; BX = indice
    MOV AX , ES:[BX]    ; AX = arbol[indice]
    MOV CX , [BP+4]     ; CX = valor

    ;Caso base 1          
    CMP BX,-1           ;
    JE NOENCONTRADO     ;

    ;Caso base 2        ;
    CMP AX, CX          ;
    JE ENCONTRADO       ;

    JG  RECIZQUIERDA    ;

    ;Recursion derecha

    MOV DI, BX          ;
    ADD DI,DI           ; indice *2
    ADD DI,2            ; (indice*2) + 2

    PUSH [BP+8]         ; arbol
    PUSH DI             ; indice
    PUSH  [BP+4]        ; valor
    CALL BUSCARABB      ;
    ADD SP,6            ; limpio
    JMP FIN             ;

    RECIZQUIERDA:

    MOV DI, BX          ;
    ADD DI,DI           ; indice *2
    ADD DI,1            ; (indice*2) + 1

    PUSH [BP+8]         ; arbol
    PUSH DI             ; indice
    PUSH  [BP+4]        ; valor
    CALL BUSCARABB      ;
    ADD SP,6            ; limpio
    JMP FIN             ;


    NOENCONTRADO:

    MOV DX,0;
    JMP FIN    

    ENCONTRADO:  

    MOV DX,1  

    FIN:

    POP BX
    POP CX
    POP AX
    POP BP
    POP DI
    PUSH DX
    PUSH DI
    RET   

ENDPROC
