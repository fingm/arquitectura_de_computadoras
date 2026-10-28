#define MAX_CHAR 1024
#define ESTADO_TECLADO 0xFF
#define DATO_TECLADO  0xFF

bool in(unsigned int dir){
    return false;
}

char out(unsigned int dir){
    return 's';
}

int main(){
    char buffer[MAX_CHAR];
    int tope = 0;

    while (true){
        if(((in(ESTADO_TECLADO)>>7) == 1) && (tope < MAX_CHAR)){
            buffer[tope] = in(DATO_TECLADO);
            tope ++;
        }
    }
}

