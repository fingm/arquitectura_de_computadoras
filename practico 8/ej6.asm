MAIN

PUSH  n             ;
PUSH  i             ;
PUSH  j             ;
CALL TORRES         ;

PROC TORRES

    PUSH BP         ;
    MOV BP,SP       ;

    PUSH AX         ;
    PUSH BX         ;
    PUSH CX         ;
    PUSH DX         ;

    MOV AX,[BP + 8]     ; AX = n
    MOV BX,[BP + 6]     ; BX = i
    MOV CX,[BP + 4]     ; CX = j 

    CMP AX,1            ;
    JE CASOBASE         ;

    MOV DX,6            ;
    SUB DX,BX           ;
    SUB DX,CX           ; k = 9-i-j

    ; --- 1. llamada: torres(n-1, i, k) ---

    MOV DI, AX          ;
    DEC DI              ; n-1

    PUSH DI             ;
    PUSH BX             ;
    PUSH DX             ;

    CALL TORRES         ; torres(n-1,i,k)
    ADD SP,6            ; limpio stack

    ; --- 2. llamada: torres(1, i, j) ---

    PUSH 1              ;
    PUSH BX             ;
    PUSH CX             ;

    CALL TORRES
    ADD SP,6            ; limpio stack

; --- 3. llamada: torres(n-1, k, j) ---

    PUSH DI             ; 
    PUSH DX             ;
    PUSH CX             ;

    CALL TORRES         ;
    ADD SP,6            ; limpio stack
    JMP FIN             ;

CASOBASE:
    PUSH BX             ;
    PUSH CX             ;
    CALL MOVERDISCO     ;
    ADD SP,4            ; limpio

END:
    POP DX              ;
    POP CX              ;
    POP BX              ;
    POP AX              ;
    POP BP              ;
    RET

ENDPROC

    
