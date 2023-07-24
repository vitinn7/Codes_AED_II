// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II



#include <stdio.h>


typedef struct No{
    int valor;
    struct No *proximo;
}No;

typedef struct{
    No *inicio;
    int tam;

}Lista;

void criar_lista(Lista *lista){ // inicia a lista
    lista->inicio=NULL;
    lista->tam=0;
}


void inserir(Lista *lista, int num){ // inseri na lista sempre no final
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
        printf("%d ",no->valor);
        no=no->proximo;
    }
    
}
void dividir(No *lista, No **comeco, No **comeco_meio){ // dividi usando 2 ponteiros, um q anda 1 casa por vez e outro que anda 2 para encontrar a metade
    No *no_slow=lista;
    No *no_fast=lista->proximo;
    while(no_fast!=NULL && no_fast->proximo!=NULL){
        no_slow=no_slow->proximo;
        no_fast=no_fast->proximo->proximo;

    }
    *comeco=lista;
    *comeco_meio=no_slow->proximo;
    no_slow->proximo=NULL;// ajusta os ponteiro para o final da metade
    
    
    
}

No *merge(No *lista1, No *lista2){
    No *resultado=NULL;
    if(lista1==NULL){
        return lista2;// se um No estiver vazio retorna o outro
    }
    else if(lista2==NULL){
        return lista1;
    }

    if(lista1->valor<=lista2->valor){// se o valor da lista1 for menor q o da lista2 eu adiciona na lista de resultado
        resultado=lista1;
        resultado->proximo=merge(lista1->proximo,lista2);// o proximo elemento é uma chamada recursiva 

    }
    else{
        resultado=lista2;// se o valor da lista2 for menor q o da lista1 eu adiciona na lista de resultado
        resultado->proximo=merge(lista1, lista2->proximo);// o proximo elemento é uma chamada recursiva 
    }
    return resultado;




}

void mergeSort(Lista *lista, int cont,int *cont_max){
    No *atual= lista->inicio;
    No *lista1=NULL;
    No *lista2=NULL;


    if(atual==NULL || atual->proximo==NULL){
        return;
    }
    cont++;// contador para verificar a quantidade de recursoes

    dividir(atual, &lista1,&lista2);
    mergeSort(&lista1,cont,cont_max);
    mergeSort(&lista2,cont,cont_max);

    lista->inicio=merge(lista1,lista2);

    if(cont>(*cont_max)){// se cont for > q cont_max eu atualizo ele 
        (*cont_max)=cont;
    }
    


}



int main(){
    int cont=0;
    int cont_max=0;
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

    mergeSort(&lista, cont,&cont_max);
    imprimir(lista);
    printf("\n");
    printf("%d", cont_max);




    


    
}