
;asumimos que  Comienza en DS:[0]

PROC  CARGARFECHAS
    PUSH BP
    MOV BP,SP

    PUSH BX
    PUSH AX
    PUSH CX
    PUSH DX
    PUSH SI
    PUSH DI

    XOR AX,AX           ; inicio
    MOV BX,10           ; fin
    XOR DI,DI           ; offset

    MOV CX, 2026        ; anio (short)
    MOV DX, 1           ; mes (char)
    MOV SI, 1           ; dia (char)

    FOR:
        CMP AX,BX       ;
        JAE END

        MOV DS:[DI],CX      ;
        MOV DS:[DI+2],DX    ;
        MOV DS:[DI+3],SI    ;

        INC AX              ;
        ADD DI,4            ;
        JMP FOR
    
    END:
        MOV AX, 90          ;
        MOV CX,4            ;
        MUL CX              ;

        MOV BX,AX           ; [AX] da error

        MOV DS:[BX],2026    ;
        MOV DS:[BX+2],9     ;
        MOV DS:[BX+3],25    ;


        POP DI
        POP SI
        POP DX
        POP CX
        POP AX
        POP BX
        POP BP

        RET
ENDPROC