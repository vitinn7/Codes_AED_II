// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0


// ARVORE AVP

typedef struct NO1{
    int info;
    struct NO1 *esq, *dir, *parent;
    int cor;
}No1;

void leftRotate(No1 **no, No1 *x,int *contRotAVP){
    No1 *y= x->dir;
    x->dir=y->esq;

    if(x->dir != NULL){
        x->dir->parent=x;
    }
    y->parent=x->parent;

    if(x->parent==NULL){
        *no=y;
    }
    else if(x==x->parent->esq){
        x->parent->esq=y;
    }
    else{
        x->parent->dir=y;
    }
    y->esq=x;
    x->parent=y;
    (*contRotAVP)++;
}

void rightRotate(No1 **no,No1 *y,int *contRotAVP){
    No1 *x=y->esq;
    y->esq=x->dir;
    if(x->dir != NULL){
        x->dir->parent=y;

    }
    x->parent=y->parent;
    if(x->parent==NULL){
        *no=x;
    }
    else if(y==y->parent->esq){
        y->parent->esq=x;
    }
    else{
        y->parent->dir=x;

    }
    x->dir=y;
    y->parent=x;
    (*contRotAVP)++;

}


void balancear(No1** no, No1* aux, int* contMudanca, int* contRotAVP) {
    while (aux != *no && aux->parent->cor == RED) {
        No1* y;

        if (aux->parent == aux->parent->parent->esq) {
            y = aux->parent->parent->dir;
        } else {
            y = aux->parent->parent->esq;
        }

        if (y != NULL && y->cor == RED) {
            y->cor = BLACK;
            aux->parent->cor = BLACK;
            aux->parent->parent->cor = RED;
            aux = aux->parent->parent;
            (*contMudanca) += 3;  
        } else {
            if (aux->parent == aux->parent->parent->esq && aux == aux->parent->esq) {
                aux->parent->cor = BLACK;
                aux->parent->parent->cor = RED;
                rightRotate(no, aux->parent->parent,contRotAVP);
                (*contMudanca)+=2;  
            } else if (aux->parent == aux->parent->parent->esq && aux == aux->parent->dir) {
                aux = aux->parent;
                leftRotate(no, aux,contRotAVP);
                aux->parent->cor = BLACK;
                aux->parent->parent->cor = RED;
                rightRotate(no, aux->parent->parent,contRotAVP);
                (*contMudanca)+=2;  
            } else if (aux->parent == aux->parent->parent->dir && aux == aux->parent->dir) {
                aux->parent->cor = BLACK;
                aux->parent->parent->cor = RED;
                leftRotate(no, aux->parent->parent,contRotAVP);
                (*contMudanca)+=2; 
            } else if (aux->parent == aux->parent->parent->dir && aux == aux->parent->esq) {
                aux = aux->parent;
                rightRotate(no, aux,contRotAVP);
                aux->parent->cor = BLACK;
                aux->parent->parent->cor = RED;
                leftRotate(no, aux->parent->parent,contRotAVP);
                (*contMudanca)+=2; 
            }
        }
    }
    (*no)->cor = BLACK;

  
}






No1 *inserirAVP(No1 **no, int valor, int *contMudanca,int* contRotAVP){
    No1* novo=(No1*)malloc(sizeof(No1));
    novo->info=valor;
    novo->esq=novo->dir=novo->parent=NULL;

    if(*no ==NULL){
        novo->cor=BLACK;
        *no=novo;
    }
    else{
        No1 *y= NULL;
        No1 *x =*no;

        while(x != NULL){
            y=x;
            if(novo->info <x->info){
                x=x->esq;
            }
            else{
                x=x->dir;
            }

        }
        novo->parent=y;
        if(novo->info > y->info){
            y->dir=novo;
        }
        else{
            y->esq=novo;
        }
        novo->cor=RED;
        balancear(no,novo, contMudanca, contRotAVP);
    }

    return *no;

}


int alturaNo(No1* no) {
    if (no == NULL) {
        return -1;
    } else {
        int altura_esq = alturaNo(no->esq);
        int altura_dir = alturaNo(no->dir);  
       
        if (altura_esq > altura_dir) {
            return altura_esq + 1;
        } else {
            return altura_dir + 1;
        }
    }
}

No1* buscarNumero(No1* raiz, int valor) {
    if (raiz == NULL || raiz->info == valor) {
        return raiz;
    }

    if (valor < raiz->info) {
        return buscarNumero(raiz->esq, valor);
    } else {
        return buscarNumero(raiz->dir, valor);
    }
}
int alturaNegra(No1* no) {
    if (no == NULL) {
        return 0;  
    } else {
        int altura_esq = alturaNegra(no->esq);   
        int altura_dir = alturaNegra(no->dir);   

        
        int altura_atual = (no->cor == BLACK) ? 1 : 0;

        
        return (altura_esq > altura_dir) ? altura_esq + altura_atual : altura_dir + altura_atual;
    }
}






// ARVORE AVL

typedef struct NO{
    int valor;
    struct NO *esq, *dir;
    int altura;

}No;

No* novoNo(int valor){
    No *novo=malloc(sizeof(No));

    if(novo){
        novo->valor=valor;
        novo->esq=NULL;
        novo->dir=NULL;
        novo->altura=0;
    }
    else{
        printf("\nERRO ao alocar nó");
    }
    return novo;
}


int maior(int a, int b){
    if(a>b){
        return a;
    } // operador ternário que encontrei na internet
    else{
        return b;
    }
}

int alturaDoNo(No *no){
    if(no==NULL){
        return -1;
    }
    else{
        return no->altura;
    }
}


int fatorDeBalanceamento(No *no){
    if(no){
        return(alturaDoNo(no->esq)-alturaDoNo(no->dir));

    }
    else{
        return 0;
    }
}

No* rotacaoEsq(No *r){
    No *y, *f;

    y=r->dir;
    f=y->esq;

    y->esq=r;
    r->dir=f;

    r->altura=maior(alturaDoNo(r->esq),alturaDoNo(r->dir))+1;
    y->altura=maior(alturaDoNo(y->esq),alturaDoNo(y->dir))+1;


    return y;
}

No *rotacaoDir(No *r){
    No *y, *f;

    y=r->esq;
    f=y->dir;

    y->dir=r;
    r->esq=f;

    r->altura=maior(alturaDoNo(r->esq),alturaDoNo(r->dir))+1;
    y->altura=maior(alturaDoNo(y->esq),alturaDoNo(y->dir))+1;

    return y;
}


No* inserir(No *raiz, int valor, int *contRotAVL) {
    if (raiz == NULL) {
        return novoNo(valor);
    } else {
        if (valor < raiz->valor) {
            raiz->esq = inserir(raiz->esq, valor, contRotAVL);
            raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
            if (fatorDeBalanceamento(raiz) > 1 && valor < raiz->esq->valor) {
                (*contRotAVL)++;
                return rotacaoDir(raiz);
            }
            if (fatorDeBalanceamento(raiz) > 1 && valor > raiz->esq->valor) {
                raiz->esq = rotacaoEsq(raiz->esq);
                (*contRotAVL)++;
                return rotacaoDir(raiz);
            }
        } else if (valor > raiz->valor) {
            raiz->dir = inserir(raiz->dir, valor, contRotAVL);
            raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

            if (fatorDeBalanceamento(raiz) < -1 && valor > raiz->dir->valor) {
                (*contRotAVL)++;
                return rotacaoEsq(raiz);
            }
            if (fatorDeBalanceamento(raiz) < -1 && valor < raiz->dir->valor) {
                raiz->dir = rotacaoDir(raiz->dir);
                (*contRotAVL)++;
                return rotacaoEsq(raiz);
            }
        }

        return raiz;
    }
}


void imprimir(No1 *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->dir, nivel +1);
        printf("\n\n");

        for(i=0; i < nivel; i++){
            printf("\t");
        }
        printf("%d %d", raiz->info,raiz->cor);
        imprimir(raiz->esq, nivel+1);
    }
}



int main(){
    int valor=0;
    No *raiz= NULL;
    No1 *raiz1= NULL;
    int i;
    int contMudanca=0;
    int contRotAVL=0;
    int contRotAVP=0;
    for(i=0; valor>=0; i++){
        scanf("%d",&valor);
        if(valor>= 0){
            raiz=inserir(raiz,valor,&contRotAVL);
            raiz1=inserirAVP(&raiz1,valor,&contMudanca, &contRotAVP);
        }
        
    }
    if(raiz!=NULL){
        if(raiz->dir==NULL && raiz->esq== NULL){
            printf("%d,0,0\n",raiz->altura);

        }
        else if(raiz->dir== NULL && raiz->esq !=NULL){
            printf("%d,%d,%d\n",raiz->altura,raiz->esq->altura+1,0);

        }
        else if(raiz->dir!= NULL && raiz->esq ==NULL){
            printf("%d,%d,%d\n",raiz->altura,0,raiz->dir->altura+1);

        }
        else{
            printf("%d,%d,%d\n",raiz->altura,raiz->esq->altura+1,raiz->dir->altura+1);

        }

    }
    else{
        printf("0,0,0");
    }
    int altura,altura1,altura2,alturaN;
    altura=alturaNo(raiz1);
    No1 *aux=buscarNumero(raiz1,raiz1->esq->info);
    altura1=alturaNo(aux);
    aux=buscarNumero(raiz1,raiz1->dir->info);
    altura2=alturaNo(aux);
    printf("%d,%d,%d\n",altura,altura1+1,altura2+1);
    alturaN=alturaNegra(raiz1);
    printf("%d\n",alturaN);
    printf("%d,%d,%d",contMudanca,contRotAVP,contRotAVL);


    
    

    //imprimir(raiz1,1);
}