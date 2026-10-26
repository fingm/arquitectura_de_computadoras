MAIN 

PUSH segmento_arbol         ;
PUSH offset_arbol           ;
CALL CANTBIF                 ;
POP cantidad                ;

PROC CANTBIF

    PUSH BP             ;
    MOV BP,SP           ;

    PUSH BX             ;
    PUSH ES             ;
    PUSH CX             ;
    PUSH DX             ;
    PUSH DI             ;
    PUSH SI             ;


    MOV AX, [BP+6]      ;
    MOV BX, [BP+4]      ; BX = offset

    OR AX,BX            ; vemos si ambas son cero
    JZ  ESNULL          ;

    MOV ES: [BP+6]      ;

    ;-----if(a->izq != NULL && a->der != NULL)

    MOV SI, ES:[BX]     ; off hijo izq 
    MOV DI, ES:[BX + 2] ; segm hijo izq

    OR SI,DI            ; 
    JZ  HIJONULL        ;

    MOV SI, ES:[BX + 4] ; off hijo der 
    MOV DI, ES:[BX + 6] ; segm hijo der

    OR SI,DI            ; 
    JZ  HIJONULL        ;

    MOV DI,1            ; esBifurcacion = 1;
    PUSH DI             ; valor actual

REC:

    ;Llamado recursivo hijo izquierdo

    PUSH ES:[BX+2]      ;
    PUSH ES:[BX]        ;    
    CALL CANTBIF        ;

    POP AX              ;
    ADD SP,2            ; limpio stack

    PUSH AX             ;

    ;llamado recursivo derecho

    PUSH ES:[BX+6]      ;
    PUSH ES:[BX+4]      ;
    CALL CANTBIF        ;

    POP SI              ; bder
    ADD SP,2            ; limpio stack

    ;suma final
    POP AX              ; AX = bizq
    ADD AX,SI           ; AX = bizq + bder
    POP DI              ;
    ADD AX,DI           ; AX = bizq + bder + esBifurcacion


FIN:

    POP SI             ;
    POP DI             ;
    POP DX             ;
    POP CX             ;
    POP ES             ;
    POP BX             ;
    POP BP             ;

    POP CX             ;    retirro el IP de retorno
    PUSH AX            ;    guardo el resultado
    PUSH SI            ;    devuelvo el IP de retorno
 
    RET  

HIJONULL:   
    JMP REC             ;

ESNULL:
    MOV AX,0            ;
    JMP FIN:

ENDPROC