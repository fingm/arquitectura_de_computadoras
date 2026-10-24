
PROC RUNLENGTH
    PUSH BP
    MOV BP,SP

    PUSH SI                 ;
    PUSH DI                 ;
    PUSH DX                 ; auxiliar, guarda el valor actual del arreglod e entrada
    PUSH BX                 ; guardamos valor previo
    MOV AX,0                ; iterador i=0 del for
    MOV BX,0                ; lengthOut


FOR:
    CMP AX , CX             ; si i = lengthIn, se termina el for
    JE ENDFOR               ;

    MOV DX, ES:[SI]         ; arreglo[i] ( charActual )

    PUSH SI                 ; guardo valor actual
    MOV SI, 0               ; cantidadIguales = 0
    PUSH DI                 ; guardo valor actual
    MOV DI, 0               ; va a ser i + cantidadIguales

WHILE:  
    ADD DI , AX             ; DI = i
    ADD DI , SI             ; DI = i + cantidadIguales

    CMP DI, CX              ; while i + cantidadIguales < lengthIn
    JE ENDWHILE

    CMP BYTE PTR ES:[DI], DX ; 
    JNE ENDWHILE            ;

    INC SI                  ;
    JMP WHILE               ,

ENDWHILE: 
    POP DI                  ; recupero valor anterior de DI, que apunta a  codif

    MOV ES:[DI], DX         ; Guardo  charActual
    MOV ES:[DI+1], SI       ; Guardo cantidadIguales

    ADD AX, SI              ; i = i + cantidadIguales
    POP SI                  ; restauro valor de SI
    INC BX                  ; lengthOut++
    JMP FOR
 
ENDFOR: 
    DEC BX                  ;
    MOV AX , BX             ;
    POP DI                  ;
    POP SI                  ;
    POP BX                  ;
    POP DX                  ;
    POP DI                  ;
    POP SI                  ;
    POP BP                  ;
    RET                     ;
    
ENDPROC