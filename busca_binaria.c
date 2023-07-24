// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II

#include <stdio.h>


int buscaBinaria(int *vet,int busca, int inicio, int fim, int cont){
    int meio;
    if(inicio<=fim){
        meio=(inicio+fim)/2; // encontra o meio dividindo por 2 a soma do inicio com o fim
        if(busca==vet[meio]){
            return cont;// retorna o contador de quantas recursoes foi feita quando encontra o numero
            
        }
        else{
            cont++;
            if(busca<vet[meio]){ // se o numero que buscamos é menor que o item do meio movemos o fim para o item anterior ao do meio
                return buscaBinaria(vet,busca,inicio,meio-1,cont);
                

            }
            else{
               return buscaBinaria(vet,busca,meio+1,fim,cont);//// se o numero que buscamos é maior que o item do meio movemos o inicio para o item posterior ao do meio
               
            }
        }
    }
    return -1; // retornamos -1 se nao encontramos o número desejado
}

int main(){
    int tam, *vet;
    int i, numero;
    int contador=0;

    scanf("%d",&tam);
    vet=(int*)(malloc(tam*sizeof(int))); // alocação dinamica do vetor
    for(i=0;i<tam;i++){ // colocando os numeros no vetor
        scanf("%d",&vet[i]);

    }
    scanf("%d",&numero); // pesquisa do numero no vetor
    if(buscaBinaria(vet,numero,0,tam-1,contador)==-1){// nao foi encontrado
        printf("%d nao foi encontrado",numero);
    }
    else{
        printf("%d",buscaBinaria(vet,numero,0,tam-1,contador));// foi encontrado e printa o numero de interações 
    }
    free(vet);
    return 0;


}