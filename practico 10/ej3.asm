; Variables globales

estado DW 0             ;
clicks DW 0             ;

SENSOR EQU 0x47         ;
ACCESORIO EQU 0x49      ;

SEGURO EQU 0            ;
EXTRAYENDO EQU 1        ;
CERRADO_EXT EQU 2       ;
CERRADO EQU 3           ;


PROC ENCENDEREXTRACTOR
    PUSH DX                         ;
    PUSH AX                         ;

    MOV DX, ACCESORIO               ;
    IN AL,DX                        ; char actual = in(ACCESORIO);
    OR AL,0x01                      ; actual | 0x01
    OUT ACCESORIO,AL                ; out(ACCESORIO,actual | 0x01);
    MOV WORD PTR[estado],EXTRAYENDO ; estado = EXTRAYENDO;

    POP AX                          ;
    POP DX                          ;
ENDPROC

PROC APAGAREXTRACTOR
    PUSH DX                         ;
    PUSH AX                         ;

    MOV DX, ACCESORIO               ;
    IN AL,DX                        ; actual
    AND AL, 0xFE                    ; actual & 0xFE
    OUT ACCESORIO, AL               ; out(ACCESORIO,actual & 0xFE);
    MOV word ptr[clicks],0          ; clicks = 0;

    POP AX                          ;
    POP DX                          ;
ENPROC

PROC CERRARVALVULA
    PUSH DX                         ;
    PUSH AX                         ;

    MOV DX, ACCESORIO               ;
    IN AL,DX                        ; actual
    AND AL, 0xFD                    ; actual & 0xFE
    OUT ACCESORIO, AL               ; out(ACCESORIO,actual & 0xFE);

    MOV word ptr[estado],CERRADO_EXT;
    MOV word ptr[clicks],0          ; clicks = 0;

    POP AX                          ;
    POP DX                          ;
ENDPROC

PROC TIEMPO

    MOV DX,SENSOR                   ;
    IN AL,DX                        ;  lectura = in(sensor)

    CMP word ptr[estado],0          ;  if(estado == SEGURO)
    JE  IF                          ;

    CMP word ptr[estado],1          ;  if(estado == EXTRAYENDO)
    JE ELSE

    CMP word ptr[estado],3          ;  if(estado == CERRADO)
    JE FIN                          ; 

    JMP ELSE_IF_DOS                 ;  if(estado == CERRADO_EXTRAYENDO)

IF:

    AND AL,0x01                     ;
    CMP AL,1                        ;
    JNE FIN                         ;
    CALL ENCENDEREXTRACTOR          ;
    JMP FIN                         ;

ELSE_IF:

    IN AL,[clicks]                  ;
    INC AL                          ;
    MOV word ptr[clicks],AL         ; clicks ++

    CMP AL, 300                     ;
    JA CERRAR_VALVULA               ;

    IN AL,DX                        ; leo nuevamente
    AND AL,0x01                     ;
    CMP AL, 0                       ;
    JE APAGAR_EXTRACTOR_SEGURO      ;
    JMP FIN                         ;

ELSE_IF_DOS:

    AND AL, 0x01                    ;
    CMP AL,0                        ; lectura == 0 ?
    JE APAGAR_EXTRACTOR_CERRADO     ;
    JMP FIN                         ;

FIN:

APAGAR_EXTRACTOR_SEGURO:
    CALL APAGAREXTRACTOR            ;
    MOV word ptr[estado], SEGURO    ;
    JMP FIN                         ;

APAGAR_EXTRACTOR_CERRADO:
    CALL APAGAREXTRACTOR            ;
    MOV word ptr[estado], CERRADO   ;
    JMP FIN                         ;

CERRAR_VALVULA:
    CALL CERRARVALVULA              ;
    JMP FIN                         ;

ENDPROC


=====INSTALACION DE INTERRUPCION=========
;Se instala en la posicion 9 del vector de interrupciones, con cada una de 2 bytes, entonces posicion 9 = 2*9 = 18 Bytes = 0x12 Hexa 
;Posicion fisica de memoria: 0x3340A => 0x3000 x 16(base 10) + 0x340A 


CLI                             ;  deshabilita interrupciones
MOV AX,0                        ;  
MOV ES,AX                       ;  ES comienza en la posicion de memoria 0x00
MOV word ptr ES:[0x12] ,0x340A  ; 
MOV word ptr ES:[0x14] ,0x3000  ;
STI                             ; habilita nuevamente las interrupciones
