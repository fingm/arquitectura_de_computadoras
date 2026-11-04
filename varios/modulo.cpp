#include <iostream>
#include <bitset>

int main(){
    unsigned int num = 0xFFFFFFFF;
        std::cout<<std::bitset<32>(num)<<std::endl;
         std::cout<<std::bitset<32>(num%16)<<std::endl;
}