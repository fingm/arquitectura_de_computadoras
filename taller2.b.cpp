#include <iostream>
#include <bitset>


short valorYSigno(char num){
    char s = ((num>>7) & 0x1);
    return (s<<15 & 0x8000) | (num & 0x007F );
}

int main(){
    char num = 0b10001000;

    std::cout<<"Valor y signo de "<<"Del numero: "<<std::bitset<8>(num)<<std::endl;
    std::cout<<std::bitset<16>(valorYSigno(num))<<std::endl;
    return 0;
}