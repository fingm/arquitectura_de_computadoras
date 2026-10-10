; char esta = 0
SETLO 0x00, R01
SETHI 0x00, R01

; inf = 0x101
SETLO 0x01, R02
SETHI 0x01, R02

; sup = 0x165
SETLO 0x65 , R03 
SETHI 0x01 , R03

;dato = memoria[0x100]
SETHI 0x01 , R04
SETLO 0x00 , R04
LOAD R04,R04

;DO WHILE

SETLO 0x00 R00;
SETHI 0x00 R00;

ADD R02,R03,R06; 
SR R06 , 0x1, R06 ; medio = (inf + sup)/2
LOAD R06,R07; R07 = memoria[medio]
CMP R05,R07; dato ==? memoria[medio]
JZ 0x1F
JN 0x23

;else
AND R00,R02,R02; borro inf
SETLO 0x1 R00;
ADD R06,R00,R03; medio 
OR R02,R03,R02;
JMP 0x2A

;dato == memoria
SETLO 0x1 R01; esta = 1
JMP 0x2A

;dato < memoria[medio]
AND R00,R03,R03; borro sup
SETLO 0x1 R00;
SUB R00,R03,R03; medio = medio-1
OR R03,R06,R03; sup = medio-1

;condicion while ? 
SETLO 0x1,R00
CMP R01,R00; esta? fin
JZ 0x32
CMP R03,R02; inf >? sup fin
JN 0x32
JMP xC; repite el bucle

;esta | inf> sup
CMP R01,R00; esta
SETLO 0x66, R03
SETHI 0x01,R03
JN 0x38 ; esta == 0
STORE R00,R03

SETLO 0x00,R03
STORE R00,R03








