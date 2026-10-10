#include <iostream>
#include <bitset>


unsigned short compMagnitud(unsigned short num ){
    if(num & 0x8000){
        num = (~num)|0x8000;
    }

    return num;
}

unsigned short compDesp( short num){
    return num + 128;
}

int main(){
    unsigned short n = compMagnitud(0b1111111111110000);
    std::cout<<std::bitset<16>(n)<<std::endl;

    unsigned short m = compDesp(0b0000000000110010);
    std::cout<<std::bitset<16>(m)<<std::endl;

    return 0;
}