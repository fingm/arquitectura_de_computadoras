PROC INCREMENTA

    PUSH BP             ;
    MOV BP, SP          ;

    PUSH AX             ; Auxiliar
    PUSH SI             ;

WHILE
    CMP BL, 0XFF        ; condicion de while
    JE FIN              ;

    MOV AL,BL           ; Guardo el indice en AX
    MOV AH, 0
    MOV SI, AX          ; SI
    ADD SI, AX          ; SI x 2 
    ADD SI, AX          ; SI x 3 direccion fisica de indice  

    MOV AX, ES:[SI]     ;
    INC AX              ;
    MOV ES:[SI],AX      ;

    MOV BL,ES:[SI+2]    ; marco siguiente indice

    JMP WHILE    
 
END:
    POP SI
    POP AX
    POP BP
    RET

ENDPROC        
