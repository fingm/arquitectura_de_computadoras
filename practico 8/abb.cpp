#include <stdio.h>

struct nodo{
    int dato;
    nodo *der,*izq;
};

typedef nodo *arbol;

bool pertenece(arbol a , int dato){
    if(a == NULL){
        return false;
    }
    if(a->dato == dato){
        return true;
    }else if( dato < a->dato){
        return pertenece(a->izq, dato);
    }else if (dato> a->dato){
        return pertenece(a->der,dato);
    }
}


int main(){

    arbol a = new nodo;
    a->dato = 20;


}