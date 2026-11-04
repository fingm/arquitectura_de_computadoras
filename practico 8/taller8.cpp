short buscarABB ( short * arbol , short indice , short valor ) {
    // Paso base
    if ( arbol [ indice ] == -1)
        return false ;
    if ( arbol [ indice ] == valor )
        return true ;
    // Recursión
    else if ( arbol [ indice ] > valor )
        return buscarABB ( arbol , (2* indice )+1 , valor );
    else
        return buscarABB ( arbol , (2* indice )+2 , valor );
}