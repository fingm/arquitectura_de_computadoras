




PUSH NUM_A      ;[BP+6]
PUSH NUM_B      ;[BP+4]
CALL SUMA       ;[BP+2]
POP RESULTADO   ;


PROC SUMA
PUSH BP; Respaldo BP
MOV BP, SP ; BP -> SP

PUSH CX
MOV CX,[BP+6]
ADD CX,[BP+4]

MOV [BP+6],CX   ; Coloco el resultado en la pila del stack

MOV CX,[BP+2]   ; 
MOV [BP+4],CX   ; Coloco en la segunda posicion la direccion de retorno

POP CX
POP BP
add SP,2
RET
END PROC

