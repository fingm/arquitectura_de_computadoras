
#define SENSOR 0x47 // direccion E/S: SENSOR
#define ACCESORIO 0x49 // direccion E/S: ACCESORIO ( extractor y valvula)

#define SEGURO 0
#define EXTRAYENDO 1
#define CERRADO_EXTRAYENDO 2
#define CERRADO 3

char in(char puerto);
void out(char puerto,char dato);

//Interrumpe  en 10Hz => T = 1/10Hz  0 0.1 s => cada 10 clicks 1 segundo
int clicks = 0;
char estado = 0;

//Extractor controlado por bit 0
void encenderExtractor(){
    char actual = in(ACCESORIO);
    out(ACCESORIO,actual | 0x01);
    estado = EXTRAYENDO;
}

void apagarExtractor(){
    char actual = in(ACCESORIO);
    out(ACCESORIO,actual & 0xFE);
    clicks = 0;
}

void cerrarValvula(){
    char actual = in(ACCESORIO);
    out(ACCESORIO,actual & 0xFD);
    estado = CERRADO_EXTRAYENDO;
    clicks = 0;
}

void tiempo(){
    if(estado == SEGURO){
        char lectura = in(SENSOR) & 0x01;
        if(lectura ==1){
            encenderExtractor();
        }
    }else if(estado == EXTRAYENDO){
        clicks ++ ;
        if(clicks>=300){
            cerrarValvula();
        }else{
            char lectura = in(SENSOR) & 0x01;
            if(lectura == 0){
                apagarExtractor();
                estado = SEGURO;
            }
        }
    }else if(estado == CERRADO_EXTRAYENDO){
        char lectura = in(SENSOR) & 0x01;
        if(lectura == 0){
           apagarExtractor();
           estado = CERRADO;
        }
    }
}



