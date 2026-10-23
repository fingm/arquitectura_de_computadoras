struct nodo{
    short dato;                   //2 bytes
    unsigned char izq;            //1 byte
    unsigned char der;            //1 byte
};

nodo arbol[256];


// Pre: no es vacio arbol
bool pertenece(unsigned char indice  , int dato){
    bool res;

    if(arbol[indice].dato == dato){
        res =  true;
    }else if(dato < arbol[indice].dato){
        if(arbol[indice].izq != 0){
            res = pertenece(arbol[indice].izq,dato);
        }
    }else if (dato > arbol[indice].dato){
        if(arbol[indice].der != 0){
            res = pertenece(arbol[indice].der,dato);
        }
    }

    return res;
}
