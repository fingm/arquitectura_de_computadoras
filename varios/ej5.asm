;REGISTROS R00 , R06

MVINM 0x0100,R00        ; inicio = 0x100  (iterador para ahorra registros)
MVINM 0x0,R01           ; suma = 0
MVINM 0x0100,R02        ; tope = 16
MVINM 0x0001,R04        ; paso iterativo i++


MVINM LEER_MEM1, R05    ; Puerto de Lectura 
OUT R05, R00            ; En el puerto LEER_MEM1, buscamos la direccion 0x0100
MVINM LEER_MEM2, R05    ; Puerto de Lectura
IN R05 , R03            ; max = mem[inicio]
MVREG R03,R01           ; sumo primer elemento
ADD R04,R00             ; Paso al segundo elemento

FOR:

MVINM LEER_MEM1, R05    ; Puerto de Lectura 
OUT R05, R00            ; En el puerto LEER_MEM1, buscamos la direccion 0x0100
MVINM LEER_MEM2, R05    ; Puerto de Lectura
IN R05 , R06            ; palabra = mem[inicio + i]

ADD R06,R01             ; suma += palabra


CMP R06,R03             ; si max< palabra , C=1
JC ACTUALIZAR_MAX

ACTUALIZADO:
ADD R04,R00             ; Paso al segundo elemento
CMP R02,R00             ; si  tope< inicio C=1
JC FOR
JMP END

ACTUALIZAR_MAX:
MVREG R06,R03
JMP ACTUALIZADO

END:

MVINM 0x0110,R02        ; posSaveSum = 0x0110
MVINM 0x0111,R04        ; posSaveMax = 0x0111

MVINM ESCRIBIR_MEM1, R05    ; Puerto de Escritura 
OUT R05, R02                ; En el puerto ESCRIBIR_MEM1, buscamos la direccion 0x0110
MVINM ESCRIBIR_MEM2, R05    ; Puerto de Lectura
OUT R05 , R01               ; mem[posSaveSum] = suma

MVINM ESCRIBIR_MEM1, R05    ; Puerto de Escritura 
OUT R05, R04                ; En el puerto ESCRIBIR_MEM1, buscamos la direccion 0x0110
MVINM ESCRIBIR_MEM2, R05    ; Puerto de Lectura
OUT R05 , R03               ; mem[posSaveSum] = suma

