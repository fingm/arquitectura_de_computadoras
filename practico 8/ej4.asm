; Parámetros de entrada por Stack:
; [BP+6] = segmento del nodo actual
; [BP+4] = offset del nodo actual
; Retorno:
; AX = profundidad del subárbol

PROC PROFUNDIDAD
    PUSH BP
    MOV BP, SP

    PUSH BX
    PUSH CX
    PUSH DX
    PUSH ES

    ; 1. Cargar segmento y offset del nodo recibido
    MOV AX, [BP+6]      ; AX = Segmento
    MOV BX, [BP+4]      ; BX = Offset
    MOV ES, AX          ; ES apunta al segmento del nodo

    ; 2. Caso Base: Verificar si nodo == NULL (Segmento == 0 y Offset == 0)
    OR AX, BX
    JZ NODO_NULL        ; Si ambos son 0, el árbol es NULL

    ; 3. Llamada recursiva al subárbol IZQUIERDO
    PUSH ES:[BX+2]      ; Segmento nodo->izq
    PUSH ES:[BX]        ; Offset nodo->izq
    CALL PROFUNDIDAD
    ADD SP, 4           ; Limpia los 2 parámetros pasados por pila
    MOV CX, AX          ; CX = prof_izq (Resultado devuelto en AX)

    ; 4. Llamada recursiva al subárbol DERECHO
    ; Se deben volver a leer los campos usando ES:BX porque AX y ES pudieron modificarse
    MOV AX, [BP+6]
    MOV BX, [BP+4]
    MOV ES, AX

    PUSH ES:[BX+6]      ; Segmento nodo->der
    PUSH ES:[BX+4]      ; Offset nodo->der
    CALL PROFUNDIDAD
    ADD SP, 4           ; Limpia los 2 parámetros pasados por pila
    MOV DX, AX          ; DX = prof_der (Resultado devuelto en AX)

    ; 5. Comparar cuál profundidad es mayor y retornar 1 + max(prof_izq, prof_der)
    CMP CX, DX
    JGE EVALUAR_IZQ     ; Si prof_izq >= prof_der

EVALUAR_DER:
    MOV AX, DX          ; AX = prof_der
    JMP FIN_EVALUACION

EVALUAR_IZQ:
    MOV AX, CX          ; AX = prof_izq

FIN_EVALUACION:
    ADD AX, 1           ; Retorna 1 + max
    JMP FIN

NODO_NULL:
    MOV AX, 0           ; Caso base: profundidad = 0

FIN:
    POP ES
    POP DX
    POP CX
    POP BX
    POP BP
    RET                 ; Los parámetros los limpia quien llamó (Caller Cleanup)
ENDPROC