
void sumar(unsigned short mem[]){

    unsigned short inicio = 0x0100;
    unsigned short suma = 0;
    unsigned short tope = 16;

    unsigned short posSaveSum = 0x0110;
    unsigned short posSaveMax = 0x0111;

    unsigned short max = mem[inicio];

    for(int i = inicio ; i < tope;i++){
        unsigned short palabra = mem[inicio + i];

        suma += palabra;

        if(palabra > max){
            max = palabra;
        }
    }
 
    mem[posSaveSum] = suma;
    mem[posSaveMax] = max;

}