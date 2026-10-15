
PROC BYTECUADRADO

PUSH BP
MOV BP, SP

PUSH SI
PUSH DI
PUSH CX
PUSH AX
PUSH DX

MOV DL,0

WHILE:
    
    CMP DL,BL
    JE FIN

    MOV AL,DS:[SI]  ; leo a donde apunta  SI
    MUL AL          ; AL = AL*AL
    MOV DS:[DI],AX  ; escribo en destino
    
    INC SI
    ADD DI,2

    INC DL

    JMP WHILE

FIN:
    POP DX
    POP AX
    POP CX
    POP DI
    POP SI
    POP BP
    RET

ENDPROC    


