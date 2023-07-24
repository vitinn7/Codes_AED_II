// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct no{
    int valor;
    int removido;

}No;


int h1(int k, int tamanho){
    return k %tamanho;
}

int h2(int k, int tamanho){
    return 1 + (k % (tamanho - 1));
}

int h(int k, int i, int tamanho){
    return (h1(k, tamanho) + i * h2(k, tamanho)) % tamanho;
}
void inicializar(No *L, int tamanho){
    int i;
    for(i=0;i<tamanho; i++){
        L[i].valor=-1;
        L[i].removido=0;
    }
}

int inserir(No *L, int valor, int tamanho){
    int i;
    int new;
    for(i=0;i<tamanho;i++){
        new=h(valor,i,tamanho);
        if(L[new].valor<0){
            L[new].valor=valor;
            L[new].removido=0;
            return 1;
        }
    }
    return 0;

}

void imprimir(No *L, int tamanho){
    int i;

    for(i=0;i<tamanho;i++){
        if(L[i].valor!=-1){
            printf("%d",L[i].valor);

        }
        else{
            if(L[i].removido==1){
                printf("D");
            }
            else{
                printf("\\");

            }
            
        }
        
    }
}

void remover(No *L, int tamanho, int busca, int *flag){
    int i;  
    for(i=0;i<tamanho;i++){
        if(busca==L[i].valor){
            (*flag)++;
            L[i].valor=-1;
            L[i].removido=1;
        }
    }
}





int main(){
    int tamanho;
    int i;
    int valor=0;
    int flag=0;

    scanf("%d",&tamanho);

    No L[tamanho];
    inicializar(L,tamanho);
    for(i=0;valor>=0;i++){
        scanf("%d",&valor);
        if(valor>=0){
            int x=inserir(L,valor,tamanho);
            if(x==0){
            printf("Nao foi possível inserir");
            }
        }

    }
    scanf("%d",&valor);
    remover(L,tamanho,valor,&flag);
    if(flag==0){
        printf("Valor nao encontrado\n");
    }
    imprimir(L,tamanho);
}