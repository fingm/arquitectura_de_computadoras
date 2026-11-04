;----------int paso ---- R32 = 0
CARGARI 0x00000000,R32

;----------int paso ---- R08 = paso for
CARGARI 0x8,R08

;----------int inicio----- R00 = inicio
CARGARI 0x100,R00

;----------int fin-----  R01 = fin
CARGARI 0x128,R01

;----------int tope----- R02 = tope
CARGARI 0x128,R02

;----------int posGuardado----- R03 = posGuardado
CARGARI 0x12E,R03


WHILE:

; R04 =  max
CARGARM R04, R00

; R05 = pos
CARGARI 0x100,R05

FOR:

; R06 = i
CARGARI 0x100,R06

; R07 =  memoria[i]
CARGARM R07, R06

; if(memoria[i] > max)
RESTA R07,R04
JG ACTUALIZAR_MAXIMO

; si i < tope salto al for,sino sigo
RESTA R02,R06
;actualizo iterador del for
SUMA R06,R08
JG FOR


;--actualizo memoria[pos]--
AND R11,R32
OR R11,R02
RESTA R11,R08; tope-4
CARGARM R12,R11; memoria[tope-4]
SALVAR R05,R12; swap
SALVAR R12,R04; swap
RESTA R02,R08; actualizo tope
SALVAR R03, R04

; condicion del while
RESTA R04,R08
RESTA R02,R00
JG WHILE
JMP END


ACTUALIZAR_MAXIMO:

CARGARM R10,R06; max = memoria[i]
AND R01,R32
OR R05,R32;Actualizo pos
JMP FOR

END

