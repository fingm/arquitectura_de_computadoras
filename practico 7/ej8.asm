PROC ENCODING

    PUSH BP
    MOV BP, SP

    PUSH AX
    PUSH SI
    PUSH DI

    XOR AX,AX                   ; AX = 0 , i = 0 
    XOR BX,BX                   ; BX = 0 , lengthOut = 0

    FOR:
        CMP AX , CX             ; i < lengthIn
        JE END                  ;

        PUSH CX                 ; A falta de registros, lo uso para cantIguales = 0, luego lo recuperamos
        MOV DL, ES:[SI]         ; DL = charActual
        XOR CX,CX               ; cantIguales = 0
    
    WHILE:
        PUSH SI                 ;
        MOV SI , AX
        ADD SI,CX               ; SI = i + cantIguales
        
        CMP  SI, AX             ; i+ cantIguales < lengthIn
        JE NEXT                 ;

        MOV DH, ES:[SI]         ;


        CMP DI , DH
        JE INCREMENTAR
        JMP NEXT

    COND_WHILE:
        POP SI

    NEXT: 
        MOV ES:[DI],DL  
        MOV ES:[DI+1], CX
        ADD Si,3
        ADD DI,3
        INC BX
        ADD AX, CX
        POP CX
        JMP FOR   


    INCREMENTAR:

        INC CX
        JMP WHILE

    END:
    DEC BX
    POP DIPOP SI
    POP AX
    POP BP
    RET
    

ENDPROC