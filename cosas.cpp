#include <iostream>
#include <bitset>

short sumaBCD(char num1,char num2){
    return 0;
}

int main(){
    /*short a = 0xFFFF;
    short b = (a & 0x8000)>>15;
    std::cout<<std::bitset<16>(a)<<std::endl;
    std::cout<<std::bitset<16>(b)<<std::endl<<std::endl;

    unsigned short c = 0b1011011011010011;
    unsigned short d = c%4;
    std::cout<<std::bitset<16>(c)<<std::endl;
    std::cout<<std::bitset<16>(d)<<std::endl<<std::endl;

    unsigned short e = 0b1001111101010011;
    unsigned short f = e/16;
    std::cout<<std::bitset<16>(e)<<std::endl;
    std::cout<<std::bitset<16>(f)<<std::endl;*/
    
   /* char a = 7;
    char b = 0xF3;
    char c = 5;

    short d = a<<12 | b<<4 | c;

    std::cout<<std::bitset<16>(d)<<std::endl;*/

    char a = 0x80;
    char b = -3;
    std::cout<<std::bitset<16>(a+b)<<std::endl;

    return 0;
}