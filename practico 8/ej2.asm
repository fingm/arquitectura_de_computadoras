MAIN

1CALL FIBO

;AX=n


PROC FIBO
    CMP AX, 0        ; ¿N == 0?
    JE PB_0

    CMP AX, 1        ; ¿N == 1?
    JE PB_1

    ; --- Caso Recursivo ---
    PUSH AX          ; Resguarda N original en la pila
    DEC AX           ; AX = N - 1
    CALL FIBO        ; Calcula F(N-1) -> Resultado en BX

    POP AX           ; Recupera N original
    PUSH BX          ; Resguarda F(N-1) en la pila

    SUB AX, 2        ; AX = N - 2
    CALL FIBO        ; Calcula F(N-2) -> Resultado en BX

    POP CX           ; Recupera F(N-1) en CX
    ADD BX, CX       ; BX = F(N-2) + F(N-1)
    RET

PB_0: 
    MOV BX, 0        ; F(0) = 0
    RET

PB_1:
    MOV BX, 1        ; F(1) = 1
    RET
ENDPROC
