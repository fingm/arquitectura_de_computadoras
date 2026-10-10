#include <iostream>
#include <bitset>

// 1 << n   es 2 a la n

char* codificar(char tira[], int largo,int n){

    int alto = 0;
    int bajo = 0;
    int suma = 0;
    int checksum=0;

    if(n==4){
        for(int i =0;i<largo;i++){
            alto += (tira[i]>>4) & 0x0F;
            bajo += tira[i] & 0x0F;
        }
        suma = (alto+bajo) % (1<<n);
        checksum = (~suma + 1) & 0x0F;
    }else{
        for(int i =0;i<largo;i++){
            suma += tira[i];
        }
        suma = suma % (1<<n);
        checksum = (~suma + 1) & 0xFF;
    }

    char* codificado = new char[largo+1];
    for(int j=0;j<largo;j++){
        codificado[j] = tira[j];
    }
    codificado[largo] = checksum;

    return codificado;
}

void mostrarTira(char tira[],int largo){
        for(int i =0;i<largo;i++){
            std::cout<<std::bitset<8>(tira[i])<<std::endl;
        }
}

bool Decodificar(char tira[], int largo,int n){
    int suma=0;
    for(int j=0;j<largo;j++){
        suma+=tira[j];
    }
    return (suma % (1<<n))==0;
}


int main(){
    std::cout<<"Mensaje Original"<<std::endl;
    char mensaje[] = {10, 20, 30};
    mostrarTira(mensaje,3);

    char* resultado = codificar(mensaje, 3, 8);
    //resultado[2] = 51;
    std::cout<<"Mensaje Codificado"<<std::endl;
    mostrarTira(resultado,4);
    if(Decodificar(resultado,4,8)){
        std::cout<<"Mensaje Correcto"<<std::endl;
    }else{
        std::cout<<"Error de transmision"<<std::endl;
    }
    delete[] resultado;

    return 0;
}