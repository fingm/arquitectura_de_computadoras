#include <iostream>
#include <bitset>

short rotar(short numero, int cantidad,char sentido){

    for(int i=1;i<=cantidad;i++){

        if(sentido == 0){//derecha
            unsigned short low = numero & 0x1;
            numero = (numero >> 1) | (low << 15);
        }else{
            unsigned short msb = (numero>>15) & 0x1;
            numero = (numero << 1) | msb;
        }
    }

    return numero;
}

int main(){
    std::cout<<std::bitset<16>(0x00F1)<<std::endl;
    std::cout<<std::bitset<16>(rotar(0x00F1,2,1))<<std::endl;
    std::cout<<std::bitset<16>(rotar(0x00F1,3,1))<<std::endl;
    std::cout<<std::bitset<16>(rotar(0x00F1,4,1))<<std::endl;
    std::cout<<std::bitset<16>(rotar(0x00F1,5,1))<<std::endl;
    return 0;
}