#define PUERTO_LUCES 0x20

void out(char a, char b){

}

char in(char a){

}

// Una vez iniciado, se apagan en 45 segundos

int segundos = 0;
bool lucesPrendidas = false;

//Interrumpe cada 1 segundo
void tiempo(){
    if(lucesPrendidas){
        segundos++;
        if(segundos == 45){
            segundos = 0;
            out(PUERTO_LUCES, in(PUERTO_LUCES) & 0xFE);
            lucesPrendidas = false;
        }
    }
}


//Inicia o reinicia el tiempo
void boton(){
    out(PUERTO_LUCES,in(PUERTO_LUCES) | 0x01);
    segundos = 0;
    lucesPrendidas = true;
}