#include <iostream>
#include <bitset>


short complementoADos(char num){
    char s = ((num>>7) & 0x1);
    short nuevo;
    if(s == 1){
        nuevo = num | 0xFF00;
    }else{
        nuevo = num | 0x0000;
    }
    return nuevo;
}

int main(){
    char num = 0b10001000;

    std::cout<<"Complemento a 2"<<"Del numero: "<<std::bitset<8>(num)<<std::endl;
    std::cout<<std::bitset<16>(complementoADos(num))<<std::endl;
    return 0;
}