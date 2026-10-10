#include <iostream>
#include <bitset>

int paridad(int palabra){
    int res = 0;

    for(int i=0;i<32;i++){
        if(palabra & 1){
            res++;
        }
        palabra = palabra>>1;

    }
    return res % 2;
}

int main(){
    int test = 0b10101010101010101010101010101011;
    std::cout<<std::bitset<32>(paridad(test))<<std::endl;
    return 0;
}