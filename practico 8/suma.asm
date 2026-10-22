
MAIN
; Retorno en CX
AX = N (cte)
CALL  SUMAREC

PROC SUMAREC

    CMP AX,0
    JMP PB

    PUSH AX
    DEC AX
    CALL SUMAREC

    POP BX
    ADD CX,BX
    RET

PB:

    MOV CX,0
    RET

ENDPROC