
PROC SUMATIRA

    PUSH BP
    MOV BP , SP

    PUSH DX
    PUSH SI 
    PUSH CX

    MOV DX , 0      ; acumulador de SUMATIRA
    MOV CX , 0      ; indice
    MOV SI,  BX     ; iterador

WHILE:
    CMP CX , 1024   ; VERIFICAMOS SI ESTAMOS EN EL RANGO
    JA END          ; SI NOS PASAMOS TERMINO
    
    ADD DX , ES:[SI]; SUMAMOS 
    JC NO_CARRY     ; SI HAY CARRY SALTO

    ADD SI,2        ; Siguiente elemento de la tira
    INC AX          ;
    
    JMP WHILE       ;


CARRY:
    MOV AX , CX     ;
    JMP END

NO_CARRY
    MOV AX , 0      ;


END:
    POP CX
    POP SI
    POP DX
    POP BP
    RET

END

