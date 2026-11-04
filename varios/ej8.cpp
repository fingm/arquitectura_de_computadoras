#include <iostream>
#include <bitset>

int mediaASimple(short num){
    unsigned short signo = (num >> 15) & 0x1;
    unsigned short exp = (num >> 10) & 0x1F;
    unsigned short mantisa = (num & 0x03FF);

    unsigned int expNuevo = exp -15 + 127;

    std::cout<<std::bitset<16>(signo)<<std::endl;
    std::cout<<std::bitset<16>(exp)<<std::endl;
    std::cout<<std::bitset<16>(mantisa)<<std::endl; //Comienza desde la izquierda

    return (signo<<31) | (expNuevo<<23) | (mantisa << (23-10));
}


int main(){

    std::cout<<std::bitset<32>(mediaASimple(-30))<<std::endl;

    return 0;
}