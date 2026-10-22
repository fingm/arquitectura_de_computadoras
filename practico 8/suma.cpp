#include <stdio.h>


int sumaRec(int n){
    if(n == 0){
        return 0;
    }else{
        return n + sumaRec(n-1);
    }
}

int main(){
    printf("%d",sumaRec(5));
}