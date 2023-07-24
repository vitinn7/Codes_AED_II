// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

No* rotacaoDirEsq(No *r){
    r->dir=rotacaoDir(r->dir);
    return rotacaoEsq(r);
}

No* rotacaoEsqDir(No *r){
    r->esq=rotacaoEsq(r->esq);
    return rotacaoDir(r);
}



No* inserir(No *raiz, int valor){
    if(raiz == NULL){
        return novoNo(valor);
    }
    else{
        if(valor < raiz->valor){
            raiz->esq = inserir(raiz->esq, valor);
            raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
            if(fatorDeBalanceamento(raiz) > 1 && valor < raiz->esq->valor){
                return rotacaoDir(raiz);
            }
            if(fatorDeBalanceamento(raiz) > 1 && valor > raiz->esq->valor){
                raiz->esq = rotacaoEsq(raiz->esq);
                return rotacaoDir(raiz);
            }
        }
        else if(valor > raiz->valor){
            raiz->dir = inserir(raiz->dir, valor);
            raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;

            if(fatorDeBalanceamento(raiz) < -1 && valor > raiz->dir->valor){
                return rotacaoEsq(raiz);
            }
            if(fatorDeBalanceamento(raiz) < -1 && valor < raiz->dir->valor){
                raiz->dir = rotacaoDir(raiz->dir);
                return rotacaoEsq(raiz);
            }
        }

        return raiz;
    }
}


No* remover(No *raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    } 
    else{
        if(raiz->valor == chave) {
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            } 
            else{
                // remover nó com 2 filhos
                if (raiz->esq != NULL && raiz->dir != NULL) {
                    No *sucessor = raiz->dir;
                    while (sucessor->esq != NULL) {
                        sucessor = sucessor->esq;
                    }
                    raiz->valor = sucessor->valor;
                    raiz->dir = remover(raiz->dir, sucessor->valor);
                } 
                else {
                    No *aux;
                    if(raiz->esq != NULL) {
                        aux = raiz->esq;
                    } 
                    else{
                        aux = raiz->dir;
                    }
                    free(raiz);
                    return aux;
                }
            }
        } 
        else{
            if(chave < raiz->valor){
                raiz->esq = remover(raiz->esq, chave);
            } 
            else{
                raiz->dir = remover(raiz->dir, chave);
            }
        }

        // atualiza altura do nó atual
        raiz->altura = 1 + maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir));

        // balanceia a árvore
        int fb = fatorDeBalanceamento(raiz);
        if(fb > 1 && fatorDeBalanceamento(raiz->esq) >= 0){
            raiz = rotacaoDir(raiz);
        } 
        else if(fb < -1 && fatorDeBalanceamento(raiz->dir) <= 0){
            raiz = rotacaoEsq(raiz);
        } 
        else if(fb > 1 && fatorDeBalanceamento(raiz->esq) < 0){
            raiz = rotacaoEsqDir(raiz);
        } 
        else if(fb < -1 && fatorDeBalanceamento(raiz->dir) > 0){
            raiz = rotacaoDirEsq(raiz);
        }

        return raiz;
    }
}






void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->dir, nivel +1);
        printf("\n\n");

        for(i=0; i < nivel; i++){
            printf("\t");
        }
        printf("%d", raiz->valor);
        imprimir(raiz->esq, nivel+1);
    }
}


int buscar(No *raiz, int chave) {
    if (raiz == NULL) {
        return -1;  // chave não encontrada, retornar -1
    }
    if (raiz->valor == chave) {
        return 1;  // chave encontrada, retornar 1
    }
    if (chave < raiz->valor) {
        return buscar(raiz->esq, chave);  // continuar busca na subárvore esquerda
    }
    else {
        return buscar(raiz->dir, chave);  // continuar busca na subárvore direita
    }
}

No* buscarNo(No *raiz, int chave) {
    if (raiz == NULL) {
        return NULL;  // chave não encontrada, retornar NULL
    }
    if (raiz->valor == chave) {
        return raiz;  // nó encontrado, retornar o próprio nó
    }
    if (chave < raiz->valor) {
        return buscarNo(raiz->esq, chave);  // continuar busca na subárvore esquerda
    }
    else {
        return buscarNo(raiz->dir, chave);  // continuar busca na subárvore direita
    }
}





int main(){
    int valor=0;
    int teste;
    No *raiz= NULL;
    No *aux= NULL;
    int i;
    for(i=0; valor>=0; i++){
        scanf("%d",&valor);
        if(valor>= 0){
            raiz=inserir(raiz,valor);

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
    valor=0;
    for(i=0; valor>=0; i++){
        scanf("%d",&valor);
        if(valor>= 0){
            teste=buscar(raiz,valor);
            if(teste==1){
                raiz=remover(raiz,valor);

            }
            else{
                raiz=inserir(raiz,valor);

            }
            

        }
        
    }
    scanf("%d",&valor);
    aux=buscarNo(raiz,valor);
    if(aux!=NULL){
        if(aux->dir==NULL && aux->esq== NULL){
            printf("%d,0,0\n",aux->altura);

        }
        else if(aux->dir== NULL && aux->esq !=NULL){
            printf("%d,%d,%d\n",aux->altura,aux->esq->altura+1,0);

        }
        else if(aux->dir!= NULL && aux->esq ==NULL){
            printf("%d,%d,%d\n",aux->altura,0,aux->dir->altura+1);

        }
        else{
            printf("%d,%d,%d\n",aux->altura,aux->esq->altura+1,aux->dir->altura+1);

        }
        

    }
    else{
        printf("Valor nao encontrado");

    }
    


    
    

    
    

    //imprimir(raiz,1);

}