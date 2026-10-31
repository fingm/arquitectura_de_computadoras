void out(char a, char b){

}

char in(char a){

}

#define SENSOR 0x10
#define ACCESORIO 0x20

char captandoEmisiones = true;
char concentracionpeligrosa = false;
char valvulaAbierta = true;
char extractorEncendido = false;

//tics = Hz x segundos
int tics = 0;

void encenderExtractor(){
    captandoEmisiones = false;
    concentracionpeligrosa = true;
    out(ACCESORIO,(in(ACCESORIO) | 0x01));
}

void apagarExtractor(){
    out(ACCESORIO,(in(ACCESORIO) & 0xFE));
}

void cerrarValvula(){
    out(ACCESORIO,(in(ACCESORIO) & 0xFD));
    extractorEncendido = true;
    concentracionpeligrosa = false;
}

//tics = 10*30 => 300 tics = 30 segundos
void  tiempo(){
    if(captandoEmisiones){
        if((in(SENSOR) & 0x01) == 1 ){ // concentracion peligrosa
            encenderExtractor();
        }
    }else if(!captandoEmisiones && concentracionpeligrosa){
        tics++;
        if(tics<300){
            if(((in(SENSOR) & 0x01) == 0)){ // Concentracion adecuada antes de 30 segundos
                apagarExtractor();
                tics = 0;
                captandoEmisiones = true;
                concentracionpeligrosa = false;
            }
        }else{
            cerrarValvula();
        }

    }else if(extractorEncendido){
        if(((in(SENSOR) & 0x01) == 0)){
            apagarExtractor();
            extractorEncendido = false;
        }
    }
}


