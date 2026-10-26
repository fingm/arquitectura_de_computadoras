#include <stdio.h>

struct nodo{
    nodo*izq;
    nodo*der;
    short num;
};


short cantidadBifurcaciones(nodo *a){
    if (a == NULL){
        return 0;
    }
       
    short esBifurcacion = 0;
    if(a->izq != NULL && a->der != NULL){
        esBifurcacion = 1;
    }
    short bizq = cantidadBifurcaciones(a->izq);
    short bder = cantidadBifurcaciones(a->der);
    
    return esBifurcacion + bizq + bder; 
    
}