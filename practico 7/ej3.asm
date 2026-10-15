
PROC BUSQUEDA

    PUSH BP
    MOV BP,SP

    PUSH BX
    PUSH DI
    PUSH SI
    PUSH DX

    MOV SI,BX
    MOV CX,-1
    MOV DX, 0

WHILE:
    CMP SI,DI
    JA FIN

    MOV BL , ES:[SI]
    CMP BL , AL

    JE ENCONTRADO
    INC DX
    INC SI
    JMP WHILE


ENCONTRADO:
    MOV CL,DX

FIN:    
    POP DX
    POP SI
    POP DI
    POP BX
    RET

ENDPROC    


