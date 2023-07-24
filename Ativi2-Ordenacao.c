// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II


#include <stdio.h>
#include <stdlib.h>


void ordenacao(int *vet, int tamanho){
    int menor,aux;
    int j,i;
    for(i=0;i<tamanho-1;i++){
        menor=i;
        for(j=i+1;j<tamanho;j++){
            if(vet[j]<vet[menor]){
                menor=j;
            }
        }
        if(i!=menor){
            aux=vet[i];
            vet[i]=vet[menor];
            vet[menor]=aux;

        }

        
    }


}


int main(){

    int tam, *micro, *dose;
    int i;
    int cont=0;

    scanf("%d",&tam);

    micro=(int*)(malloc(tam*sizeof(int)));
    dose=(int*)(malloc(tam*sizeof(int)));

    for(i=0;i<tam;i++){
        scanf("%d",&micro[i]);
    }
    for(i=0;i<tam;i++){
        scanf("%d",&dose[i]);
    }
    
    ordenacao(micro,tam);
    ordenacao(dose,tam);


    for(i=0;i<tam;i++){
        if(micro[i]>=dose[i]){
            cont++;
        }
    }
    if(cont!=0){
        printf("nao");
    }
    else{
        printf("sim");
    }






}