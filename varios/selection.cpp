void selectionSort( int memoria[]){
 int inicio = 0x100;
 int fin = 0x100 + (10*4);// 10 elementos de 4 bytes cada uno 0x128
 int tope = fin;
 int posGuardado = 0x10A + 0x24;// 0x10A + 0x24 = 0x12E
    while(tope > inicio){
        int max =memoria[inicio];
        int pos = inicio;
        for (int i = inicio; i < tope; i+=4){
            if(memoria[i] > max){
                max = memoria[i];
                pos = i;
            }
        }
        memoria[pos] = memoria[tope - 4];   
        memoria[tope - 4] = max;
        tope -= 4;
        memoria[posGuardado] = max;
        posGuardado -= 4;
    }   

}