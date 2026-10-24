
STR se encuentra en la direcicon absoluta 0x12345




PROC TOUPPER
    PUSH BP         ;
    MOV BP,SP       ;

    PUSH SI         ;
    PUSH BX         ; 
    PUSH DX         ;

    XOR CX,CX       ; contador = 0
    MOV SI, AX      ; SI = actual. string comienza en ES:[SI]

    WHILE:

    MOV BL,ES:[SI]  ; dato = string[actual]

    CMP BL,0        ;
    JE FINWHILE     ;  si es el fin de string '\0'

    CMP BL, 'a'     ;
    JB  MINUSCULA   ; si dato >= a no aplica cambio

    CMP BX, 'z'     ;
    JA  MINUSCULA   ; si dato > z no aplica cambio


    MOV DX, 0x61    ;
    SUB DX,0x7A     ; 'a'-'A'
    SUB BX,DX       ; dato - ('a'-'A')
    MOV ES:[SI],BL  ;

    INC CX          ;  cont++

MINUSCULA:
    INC SI          ; SI-> siguiente elemento 
    JMP WHILE       ; 

FINWHILE:
    POP DX
    POP BX
    POP SI
    POP BP
    RET

ENDPROC
