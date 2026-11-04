BOMBA EQU 0xFF

PROC ACTIVARBOMBA
    PUSH BP
    MOV BP,SP

    PUSH DX

    MOV DX, BOMBA   ;  DX = direccion de BOMBA
    IN AL,DX        ;  AL = char estado = (in(bomba));
    
    OR  AL, 0x04    ; estado  | 0x01

    OUT DX   ,AL    ; out(bomba,estado | 0x04);


    WHILE:
        IN AL,DX        ;  AL = char estado = (in(bomba)); 
        AND AL, 0x01    ;  ((in(bomba)) & 0x01)
        CMP AL,0        ;
        JE WHILE        ;

    IN AL,DX            ;
    OR AL,0x10          ;
    OUT DX ,  AL        ;

    POP DX
    POP BP
    RET
ENDPROC
