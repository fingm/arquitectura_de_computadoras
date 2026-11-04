#include <iostream>
#include <bitset>

short sumaBCD(char a,char b){

    unsigned int suma = a+b;
    if( ((a & 0x0F) + (b & 0x0F)) > 0x09){
        suma+=0x06;// Ajusta el nibble bajo y pasa el acarreo al alto
    }

    if((suma & 0xF0)>0x90){
         suma+=0x60;//ajusto  nibble alto
    }


    return (unsigned short)suma;
}



int main(){
        unsigned char a = 99;
        unsigned char b = 11;
        std::cout<<std::bitset<16>(a)<<std::endl;
        std::cout<<std::bitset<16>(b)<<std::endl;
        std::cout<<std::bitset<16>(sumaBCD(a,b))<<std::endl;
    return 0;
}