void moverDisco(short i,short j){

}


void torres(short n, short i,short j){
    short k;
    if(n==1){
        moverDisco(i,j);
    }else{
        k= 6 - i - j;
        torres(n-1,i,k);
        torres(1,i,j);
        torres(n-1,k,j);
    }
}