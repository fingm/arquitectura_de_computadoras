#define bomba 0xFF

unsigned char in(unsigned int dir){
    return false;
}

void out(unsigned int dispositivo,unsigned int dir){

}

void activarBomba(){
    char estado = (in(bomba));
    out(bomba,estado | 0x04);

    while(((in(bomba)) & 0x01) == 0){
        // esperamos
    }
    
    estado = (in(bomba));
    out(bomba,estado | 0x10);
}


void desactivarBomba(){
    char estado = (in(bomba)); //Obtengo bit 0. si vale 1 => activada
    out(bomba, estado & ~0x14 );  //~0x14 = 1110 1011b

    while(((in(bomba)) & 0x01) == 0){
        // esperamos
    }

}

main(){

    while(true){
        char encender = (in(bomba) & 0x04)!= 0;  // Obtengo el bit 2, si vale 1 => encender := 1
        char activada = (in(bomba) & 0x01) != 0; // 1 si la bomba está efectivamente activa

        if(encender && !activada){  
            activarBomba();
        }else if(!encender && activada){
            desactivarBomba();
        }        
    }
    return 0;
}