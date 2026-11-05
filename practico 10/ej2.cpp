#define MENSAJE 0x1012
#define STX 0x05
#define ETX 0x06

#define TOPE 1024

#define ESPERANDO_STX 0
#define ESPERANDO_CANAL 1 
#define ESPERANDO_CAR 2

char in(char dir);
void out(char puerto,char dato);

char cola[TOPE];
char cantidad = 0;
char estado = 0;

void nuevochar(){
    char mensaje = in(MENSAJE);
    if(estado == ESPERANDO_STX){
        if(mensaje == STX){
            estado = ESPERANDO_CANAL;
        }
    }else if(estado == ESPERANDO_CANAL){
        if((mensaje >0) && (mensaje<=10) ){
            estado = ESPERANDO_CAR;
        }else{
            estado = ESPERANDO_STX;
        }
    }else if (estado == ESPERANDO_CAR){
        if(mensaje == ETX){
            estado = ESPERANDO_STX;
        }else if(mensaje != STX){
            estado = ESPERANDO_CANAL;
        }else{
            if(cantidad<TOPE){
                cola[cantidad] = mensaje;
                cantidad = (cantidad + 1) % 1024;
            }
        }
    }
}