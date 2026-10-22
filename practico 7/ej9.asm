
PROC SUMAMATRICES
    PUSH BP
    MOV BP,SP

    PUSH SI                 ; 
    PUSH DI                 ;
    PUSH AX                 ;
    PUSH BX                 ;
    PUSH CX                 ;
    PUSH DX                 ;

    MOV SI,MATRICES         ; SI = inicio  arreglo de matrices
    MOV DI,PESOS_MATRICES   ; DI = inicio arreglo destino
    MOV AX,CANT_MATRICES    ; AX = cantidad de matrices
    XOR BX,BX               ; BX = 0 es i=0
    MOV CX, 16              ; CX = 16 ( elems de matriz)

    FOR:
    
    CMP BX,AX
    JE FINARREGLO
    
    XOR DX,DX               ; acumulador de suam matriz
    PUSH BX                 ; dentro de Matriz es j=0
    XOR BX,BX               ;
    
    MATRIZ:

    CMP BX,CX
    JE FINMATRIZ

    ADD DX, ES:[SI]         ;
    ADD SI,2                ; Si apunta al siguiente elemento
    INC BX                  ;
    JMP MATRIZ 

    FINMATRIZ:

    POP BX
    MOV DS:[DI], DX         ; Guardo el peso de la matriz
    ADD DI,2                ; Apunto al siguiente espacio de destino
    INC BX

    JMP FOR

    FINARREGLO:
    
    POP DX
    POP CX
    POP BX
    POP AX
    POP DI
    POP SI
    POP BP
    RET

    FIN:
