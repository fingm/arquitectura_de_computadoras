#include <stdio.h>

#define BOTONES 0x10
#define MOTOR 0x20

#define BTN1 0x01
#define BTN2 0x02
#define BTN3 0x04    

#define VELOCIDAD_11 (110 << 1) | 0x1
#define VELOCIDAD_5 (50 << 1) | 0x1

#define DISPLAY_HI 0x30
#define DISPLAY_LO 0x31

#define MODO0 0     // Motor apagado
#define MODO1 1     // Motor a velocidad 11
#define MODO2 2     // Motor a velocidad 5

int tics = 0;
int tics_boton = 0;
int tics_velocidad = 0;
char boton_presionado = 0;
char modo = MODO0;
int velocidad_actual = 0;
char alarma = false;

void out(int reg, unsigned int val);
unsigned char in(int reg);

// Rutina de interrupción del Timer (Frecuencia: 1 Hz)
void tiempo(){  
    if(boton_presionado){
        tics_boton++;
    }
    if(modo != MODO0){
        tics++;
        tics_velocidad++;
        actualizarDisplay();
    }

}

void hay_boton(){
    char btn = in(BOTONES) & 0x07; // Enmascarar los 3 bits menos significativos
    if(btn == BTN1){
        out(MOTOR, VELOCIDAD_11);
        modo = MODO1;
        boton_presionado = true;
    }
    else if(btn == BTN2){
        out(MOTOR, VELOCIDAD_5);
        modo = MODO2;
        boton_presionado = true;
    }
    else if(btn == BTN3){
        out(MOTOR, 0);
        modo = MODO0;
        boton_presionado = true;
    }
}

void actualizarDisplay(){
    char alarm = alarma ? 0x1 : 0x0; 
    char funcionando = (modo != MODO0) ? 0x1 : 0x0;
    char velocidad = velocidad_actual & 0xFF; // Tomar solo los 8 bits menos significativos
    char tiempo_transcurrido = tics & 0xFF; // Tomar solo los 8 bits menos significativos
    out(DISPLAY_HI, (alarm << 7) | (funcionando << 6) | velocidad);
    out(DISPLAY_LO, tiempo_transcurrido);
}

void cinta(){
    velocidad_actual = 10/tics_velocidad;
    tics_velocidad = 0;
    
    if(tics_boton >= 30 && boton_presionado){
        if(modo == MODO1 && velocidad_actual < 330){
            alarma = true;
        }else if(modo == MODO2 && velocidad_actual < 55){
            alarma = true;
        }else{
            tics_boton = 0;
            boton_presionado = false;
            alarma = false;
        }
        tics_boton = 0;
        boton_presionado = false;
    }
}