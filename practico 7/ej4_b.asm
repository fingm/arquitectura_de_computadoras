
PROC DIVIDIRBYTE

    PUSH BP
    MOV BP, SP

    PUSH SI         ; inicia  origen
    PUSH DI         ; inicia destino
    PUSH DX         ; contador (low)
    PUSH AX         ; auxiliar

    MOV BH,0        ; contador = 0

WHILE:
    CMP BL,BH       ; n iteraciones? 
    JE FIN

    MOV AX, DS:[SI]     ; valor [SI]
    MOV DX,0            ; parte alta valga 0 (32 bits)
    DIV CX              ; Elcociente queda en AX y el resto queda en DX

    MOV DS:[DI],AX

    INC BH
    ADD SI,2
    ADD DI,2
    JMP WHILE

    FIN:

    POP BX
    POP AX
    POP DX
    POP DI
    POP SI
    POP BP
    RET

ENDPROC    


