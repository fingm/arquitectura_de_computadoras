#define ESTADO_1 1
#define ESTADO_2 2
#define ESTADO_3 3

#define disp_1 1
#define disp_2 2
#define disp_3 3

unsigned char in(unsigned int dir){
    return false;
}

void atencionDispositivoN(char disp){

}

void enable();
void disable();




void interrupt(){
    disable();
    if((in(ESTADO_1) & 0x01) == 1){
        atencionDispositivoN(disp_1);
    }else if((in(ESTADO_2) & 0x01)==1){
        atencionDispositivoN(disp_2);
    }else if((in(ESTADO_3) & 0x01)==1){
        atencionDispositivoN(disp_3);
    }
    enable();
}

char pri(char p){

}

struct disp{
    char puerto;
    char disp;
    char prioridad;
};

void establecerPrioridad(disp d[3]){
    for(int i = 1 ; i<3;i++){
        for(int j=i;j<3;j++){
            if(d[i].prioridad>d[j].prioridad){
                disp aux = d[i];
                d[i] = d[j];
                d[j] = aux;
            }
        }
    }
}

void interruptVaariable(){

    disp d1 = {ESTADO_1,disp_1,pri(disp_1)};
    disp d2 = {ESTADO_2,disp_2,pri(disp_2)};
    disp d3 = {ESTADO_3,disp_3,pri(disp_3)};
    disp dispositivo[3] = {d1,d2,d3};
    establecerPrioridad(dispositivo);

    // si previamente los ordene por prioridad siendo 0 el prioritario

    disable();

    if( ((in(dispositivo[0].puerto) & 0x01)==1 ) ){
        atencionDispositivoN(dispositivo[0].disp);
    }else if((in(dispositivo[1].puerto) & 0x01) == 1){
        atencionDispositivoN(dispositivo[1].disp);
    }else if((in(dispositivo[2].puerto) & 0x01) == 1){
        atencionDispositivoN(dispositivo[2].disp);
    }

    enable();
}