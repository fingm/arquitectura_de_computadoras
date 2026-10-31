#include <stdio.h>

#define TECLA 0xFF
#define ESC 0xFF
#define RUTINA1 1
#define RUTINA2 2
#define RUTINA3 3

struct rutina{
    char direccion;
};

unsigned char in(unsigned int dir){
    return false;
}

void out(unsigned int dispositivo,unsigned int dir){

}

char radr(char r){

}

void jmp(char  rutina){

}

char padr(){
    return 's';
}

    bool esperandoRutina = false;
    bool esperandoEscape = true;
    bool ejecutando      = false;
    char direccion = NULL;

void teclado(){
    char tecla = in(TECLA);

    if(esperandoEscape && tecla == ESC && !ejecutando){
        esperandoEscape = false;
        esperandoRutina = true;
    }else if(esperandoEscape && tecla == ESC && ejecutando){
        ejecutando = false;
        jmp(direccion);
    }else if(esperandoRutina){
        if(tecla == '1' || tecla == '2' || tecla == '3'){
            direccion = padr();
            esperandoEscape = true;
            esperandoRutina = false;
            ejecutando = true;

            if(tecla == '1'){
                jmp(radr(RUTINA1));
            }else if( tecla == '2'){
                jmp(radr(RUTINA2));
            }else if(tecla == '3'){
                jmp(radr(RUTINA3));
            }

        }else{
            esperandoEscape = true;
            esperandoRutina = false;
        }

    }

}


