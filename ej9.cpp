#include <iostream>
#include <bitset>

/**/
int multiplicarPuntoFlotante(unsigned int numA,unsigned int numB){
    unsigned int Sa = (numA>>31) & 0x1;
    unsigned int Ea = (numA>>23) & 0xFF;
    unsigned int Ma = numA & 0x7FFFFF;

    unsigned int Sb = (numB>>31) & 0x1;
    unsigned int Eb = (numB>>23) & 0xFF;
    unsigned int Mb = numB & 0x7FFFFF;

    //Obtengo el signo
    unsigned int S = Sa ^ Sb; //Xor

    //Obtengo la mantisa, en un número normalizado existe implícitamente un 1 delante =>
    unsigned long mantisaA = (1ULL<<23) | Ma;
    unsigned long mantisaB = (1ULL<<23) | Mb;

    //24x24 bits hasta 48 bits
    unsigned long long producto = mantisaA * mantisaB;

    //Obtengo los exponentes. Ea = ErealA + 127, Eb = ErealB + 127 => E = Ea + Eb - 127
    unsigned int E = Ea + Eb -127;

    //Normalizar Si el producto quedó demasiado grande (10...), desplazalo una posición y aumentá el exponente para conservar el mismo valor.
    if (producto & (1ULL << 47)) {
        producto >>= 1;
        E++;
        
    }

    unsigned int M = (producto >> 23) & 0x7FFFFF;

    return (S<<31) | (E<<23) | M;
}


int main(){

    std::cout<<std::bitset<32>(multiplicarPuntoFlotante(0b01000001111000000000000000000000,0b01000001111000000000000000000000))<<std::endl;

    return 0;
}