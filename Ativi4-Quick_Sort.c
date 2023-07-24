// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II
#include <stdio.h>

int particiona(int *vet, int inicio, int fim){
    int pivo, i,j;
    int aux;
    pivo=vet[fim];
    i=inicio-1;
    for(j=inicio;j<=fim-1;j++){
        if(vet[j]<pivo){
            i++;
            aux=vet[i];
            vet[i]=vet[j];
            vet[j]=aux;
        }
        
    }
    aux=vet[i+1];
    vet[i+1]=vet[fim];
    vet[fim]=aux;
    return (i+1);
}
 
void quick_sort(int *vet,int inicio, int fim, int *altura_min, int *altura_max, int altura_atual){
    int pivo;
    int i;
    if(inicio<fim){
        pivo=particiona(vet,inicio,fim);
        quick_sort(vet, inicio,pivo-1, altura_min, altura_max,altura_atual+1);
        quick_sort(vet,pivo+1,fim,altura_min, altura_max,altura_atual+1);
 
    }
    else{
        if(altura_atual<(*altura_min)){
            (*altura_min)=altura_atual;
 
        }
        if(altura_atual> (*altura_max)){
            (*altura_max)=altura_atual;
        }
 
    }
}
int mediana(int *vet, int inicio , int fim){
    int i;
    int meio;
    meio=(inicio+fim)/2;

    if(((vet[inicio]>vet[meio])&&!(vet[inicio]>vet[fim])) || (!(vet[inicio]>vet[meio])&&(vet[inicio]>vet[fim]))){
        return inicio;
    }
    else if(((vet[meio]<vet[inicio])&& !(vet[meio]<vet[fim])) || (!(vet[meio]<vet[inicio])&&(vet[meio]<vet[fim]))){
        return meio;
    }
    else{
        return fim;
    }

    
}
 
int particiona_three(int *vet, int inicio, int fim){
    int media;
    int pivo;
    int i,j;
    int aux;
    media=mediana(vet,inicio,fim);
    aux=vet[media];
    vet[media]=vet[fim];
    vet[fim]=aux;
    pivo=vet[fim];
    i=inicio-1;
    for(j=inicio;j<=fim-1;j++){
        if(vet[j]<pivo){
            i++;
            aux=vet[i];
            vet[i]=vet[j];
            vet[j]=aux;
        }
    }
    aux=vet[i+1];
    vet[i+1]=vet[fim];
    vet[fim]=aux;
    return i+1;

}
void quick_sort_three(int *vet,int inicio, int fim, int *altura_min, int *altura_max, int altura_atual){
    int pivo;
    int i;
    if(inicio<fim){
        pivo=particiona_three(vet,inicio,fim);
        quick_sort_three(vet, inicio,pivo-1, altura_min, altura_max,altura_atual+1);
        quick_sort_three(vet,pivo+1,fim,altura_min, altura_max,altura_atual+1);
 
    }
    else{
        if(altura_atual<(*altura_min)){
            (*altura_min)=altura_atual;
 
        }
        if(altura_atual> (*altura_max)){
            (*altura_max)=altura_atual;
        }
 
    }

}
 
 
 
 
  
 
 
int main(){
    int tam, *vet, *vet1;
    int i;
    int cont=0;
    int altura_min;
    int altura_max=0;
    scanf("%d",&tam);
    vet=(int*)(malloc(tam*sizeof(int))); // alocação dinamica do vetor
    vet1=(int*)(malloc(tam*sizeof(int)));
    for(i=0;i<tam;i++){ // colocando os numeros no vetor
        scanf("%d",&vet[i]);
        vet1[i]=vet[i];
 
    }
    altura_min=tam;
    quick_sort(vet,0,tam-1,&altura_min,&altura_max,0);
 
    printf("%d\n",altura_max-altura_min);
 
 
    altura_min=tam;
    altura_max=0;
    quick_sort_three(vet1,0,tam-1,&altura_min,&altura_max,0);

    printf("%d",altura_max-altura_min);
 
 
    free(vet);
    free(vet1);
}