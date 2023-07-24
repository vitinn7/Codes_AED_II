#include <stdio.h>

typedef struct No{
    int valor;
    struct No *proximo;
}No;

typedef struct{
    No *inicio;
    int tam;

}Lista;

void criar_lista(Lista *lista){
    lista->inicio=NULL;
    lista->tam=0;
}


void inserir(Lista *lista, int num){
    No *aux, *novo=malloc(sizeof(No));

    if(novo){
        novo->valor=num;
        novo->proximo=NULL;
        if(lista->inicio==NULL){
            lista->inicio=novo;
        }
        else{
            aux=lista->inicio;
            while(aux->proximo){
                aux=aux->proximo;
            }
            aux->proximo=novo;
        }
        lista->tam++;
    }
    else{
        printf("Erro de alocacao");
    }
}

void imprimir(Lista lista){
    No *no= lista.inicio;
    while(no){
        printf("%d",no->valor);
        no=no->proximo;
    }
    
}
void dividir(No *lista, No **comeco, No **comeco_meio){
    No *no_slow=lista;
    No *no_fast=lista->proximo;
    while(no_fast!=NULL && no_fast->proximo!=NULL){
        no_slow=no_slow->proximo;
        no_fast=no_fast->proximo->proximo;

    }
    *comeco=lista;
    *comeco_meio=no_slow->proximo;
    no_slow->proximo=NULL;
    
    
    
}

No *merge(No *lista1, No *lista2){
    No *resultado=NULL;
    if(lista1==NULL){
        return lista2;
    }
    else if(lista2==NULL){
        return lista1;
    }

    if(lista1->valor<=lista2->valor){
        resultado=lista1;
        resultado->proximo=merge(lista1->proximo,lista2);

    }
    else{
        resultado=lista2;
        resultado->proximo=merge(lista1, lista2->proximo);
    }
    return resultado;




}

void mergeSort(Lista *lista){
    No *atual= lista->inicio;
    No *lista1=NULL;
    No *lista2=NULL;


    if(atual==NULL || atual->proximo==NULL){
        return;
    }
    


    dividir(atual, &lista1,&lista2);
    mergeSort(&lista1);
    mergeSort(&lista2);

    lista->inicio=merge(lista1,lista2);
    


}








int main(){
    int tam;
    int valor;
    int i;
    Lista lista;

    criar_lista(&lista);
    scanf("%d",&tam);
    for(i=0;i<tam;i++){
        scanf("%d",&valor);
        inserir(&lista,valor);
    }

    mergeSort(&lista);
    imprimir(lista);




    


    
}