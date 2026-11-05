; --- Variables globales ---
estado   DW 0
cantidad DW 0
cola     DB 1024 DUP(?)

STX      EQU 0x88
ETX      EQU 0x81
MENSAJE  EQU 0x123

PROC NUEVOCHAR
    PUSH BP
    MOV BP, SP

    PUSH AX
    PUSH BX
    PUSH DX

    ; 1. Leer puerto I/O
    MOV DX, MENSAJE
    IN AL, DX

    ; 2. Evaluar máquina de estados
    CMP WORD PTR [estado], 0
    JE ESPERANDO_STX

    CMP WORD PTR [estado], 1
    JE ESPERANDO_CANAL

    CMP WORD PTR [estado], 2
    JE ESPERANDO_CAR
    JMP FIN

; -------------------------------------------------------------
ESPERANDO_STX:
    CMP AL, STX
    JNE FIN
    MOV WORD PTR [estado], 1    ; estado = ESPERANDO_CANAL
    JMP FIN

; -------------------------------------------------------------
ESPERANDO_CANAL:
    CMP AL, 0
    JBE ESTADO_STX             ; Si AL <= 0 (es decir 0), salta a error

    CMP AL, 10
    JA ESTADO_STX              ; Si AL > 10, salta a error

    MOV WORD PTR [estado], 2    ; estado = ESPERANDO_CAR
    JMP FIN

ESTADO_STX:
    MOV WORD PTR [estado], 0    ; estado = ESPERANDO_STX
    JMP FIN

; -------------------------------------------------------------
ESPERANDO_CAR:
    CMP AL, ETX
    JE ESTADO_STX              ; Si mensaje == ETX -> estado = ESPERANDO_STX

    CMP AL, STX
    JNE ESTADO_CANAL           ; Si mensaje != STX -> estado = ESPERANDO_CANAL

    ; --- Guardar carácter en la cola (mensaje == STX) ---
    MOV BX, [cantidad]
    CMP BX, 1024
    JAE FIN                    ; Si cantidad >= 1024, cola llena -> FIN

    ; Guardar elemento: cola[cantidad] = mensaje
    MOV cola[BX], AL

    ; cantidad = (cantidad + 1) % 1024
    INC BX
    AND BX, 0x03FF             ; Máscara equivalente a % 1024 (1023 = 0x03FF)
    MOV [cantidad], BX
    JMP FIN

ESTADO_CANAL:
    MOV WORD PTR [estado], 1    ; estado = ESPERANDO_CANAL
    JMP FIN

; -------------------------------------------------------------
FIN:
    POP DX
    POP BX
    POP AX
    POP BP
    RET
ENDPROC