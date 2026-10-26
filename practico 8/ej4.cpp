#include <stdio.h>1

struct nodo{
    nodo*izq;
    nodo*der;
    short num;
};


short profundidad(nodo *arbol){
    if(arbol == NULL){
        return 0;
    }else{
        short prof_izq = profundidad(arbol->izq);
        short prof_der = profundidad(arbol->der);

        if(prof_izq>=prof_der){
            return 1 + prof_izq;
        }else{
            return 1+ prof_der;
        }
    }
}