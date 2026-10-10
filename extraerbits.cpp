#include <iostream>
#include <bitset>

int extraerbits(int palabra, int bitalto,int bitbajo){
    int mask = (1<<(bitalto-bitbajo+1))-1;
    return (palabra>>bitbajo) & mask;
}

int main(){

    int tira = 0b01010101010101010101010101010101;

    std::cout<<std::bitset<32>(tira)<<std::endl;
    std::cout<<std::bitset<32>(extraerbits(tira,9,4))<<std::endl;

    return 0;
}