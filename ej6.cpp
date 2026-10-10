#include <iostream>
#include <bitset>

int sumar(short a, short b){

    int suma = a + b;//No se pierden datos 
    short ssuma = a + b;

    //Flags
    int Z=0, V=0, C=0, S=0;

    if(ssuma == 0){ //A la bandera Z solo le importa lo que queda guardado
        Z=1;
    }
    if(((ssuma>>15)& 0x0001)==1){
        S = 1;
    }
    if(((suma>>16)& 0x0001)==1){
        C=1;
    }

    if((a*b>0) && (ssuma <0) || (a<0) && (b<0) && (ssuma>0)){
        V=1;
    }
    /*
        if (((a ^ ssumas) & (b ^ ssumas) & 0x8000) != 0){}
            V = 1;
        }
    */
    
    return ((ssuma << 3) | (C<<2) | (V<<1) | Z) & 0x7FFFF;
}


int main(){
    int suma = sumar(30000,10000);

    std::cout<<std::bitset<32>(suma)<<std::endl;
    return 0;
}


/*
Si sumas dos números con el mismo signo y el resultado cambia de signo, 
es la prueba matemática absoluta de que el acarreo entrante y el saliente del MSB fueron diferentes.
*/