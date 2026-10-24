#include <stdio.h>


short toUpper(char *string){
    short cont = 0;
    short actual = 0;
    while(string[actual] != '\0'){
        char dato = string[actual];
        if(dato >= 'a' && dato <= 'z'){
            char mayus = dato - ('a'-'A');
            string[actual] = mayus;
            cont++;
        }
        actual++;
    }
    return cont;
}
