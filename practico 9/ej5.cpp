#include <stdio.h>

#define MAX_BUFFER 1024

#define EST_CONT_0 0x10
#define EST_CONT_1 0x12
#define EST_CONT_2 0x14
#define EST_CONT_3 0x16

#define DATO_0 0x11
#define DATO_1 0x13
#define DATO_2 0x15
#define DATO_3 0x17

#define DATO_S 0x20


char ocupado = 0;
char enviandoNumero = 0;

unsigned char in(unsigned int dir){
    return false;
}

void out(unsigned int dir,char dato){
 
}

struct dato{
    char data;
    char numero;
};

struct buffer{
    dato datos[MAX_BUFFER];
    int cantidad = 0;
} buf;

void desencolar(buffer b){
    if(b.cantidad>0){
        for(int i=0;i<b.cantidad-1;i++){
            b.datos[i] = b.datos[i+1];
        }
        b.cantidad--; 
    }
}

void intEntrada(){
    if((in(EST_CONT_0) & 0x01) == 1){
        char dato = in(DATO_0);
        if(buf.cantidad<MAX_BUFFER){
            buf.datos[buf.cantidad].data = dato;
            buf.datos[buf.cantidad].numero = 0;
            buf.cantidad++;
        }
    }
    if((in(EST_CONT_1) & 0x01) == 1){
        char dato = in(DATO_1);
        if(buf.cantidad<MAX_BUFFER){
            buf.datos[buf.cantidad].data = dato;
            buf.datos[buf.cantidad].numero = 1;
            buf.cantidad++;
        }
    }
    if((in(EST_CONT_2) & 0x01) == 1){
        char dato = in(DATO_2);
        if(buf.cantidad<MAX_BUFFER){
            buf.datos[buf.cantidad].data = dato;
            buf.datos[buf.cantidad].numero = 2;
            buf.cantidad++;
        }
    }
    if((in(EST_CONT_3) & 0x01) == 1){
        char dato = in(DATO_3);
        if(buf.cantidad<MAX_BUFFER){
            buf.datos[buf.cantidad].data = dato;
            buf.datos[buf.cantidad].numero = 3;
            buf.cantidad++;
        }
    }
    if(!ocupado && buf.cantidad>0){
        ocupado = true;
        enviandoNumero = true;
        out(DATO_S,buf.datos[0].numero);
    }
}


void intSalida(){
    if(enviandoNumero){
        enviandoNumero = false;
        out(DATO_S,buf.datos[0].data);
    }else{
        desencolar(buf);
        if(buf.cantidad>0){
            ocupado = true;
            enviandoNumero = true;
            out(DATO_S,buf.datos[0].numero);
        }else{
            ocupado = false;
        }
    }

}

int main (){


    while(true){
        //
    }

    return 0;
}