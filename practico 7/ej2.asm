;AX := D1 Leer Desde
;BX := D2 Escribir Desde
;CX := N elementos
;ES := Direcciones ES:[]


PROC COPIAR:

    PUSH BP
    MOV BP , SP

    ; guardo contexto

    PUSH SI         ; iterador a
    PUSH DI         ; iterador b
    PUSH DX         ; dato temporal

    MOV SI, 0       ;   inicio iterador origen
    MOV DI, 0       ;   inicio iterador destino

FOR:
    CMP SI,CX
    JE FIN

    MOV DL, ES:[AX + SI]    ; lee 1 byte
    MOV ES:[BX + DI],DL     ; escribe 1 byte

    INC SI
    INC DI
    JMP FOR

FIN:

    POP DX
    POP DI
    POP SI
    POP BP
    RET

ENDPROC







