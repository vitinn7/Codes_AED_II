// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

int verifica(char *alfabeto, char *palavra){
    int i=0;
    int j;
    int cont=0;
    while(palavra[i]){
        for(j=0;j<strlen(alfabeto);j++){
            if(alfabeto[j]==palavra[i]){
                cont++;
            }
        }
        i++;
    }
    if(cont==strlen(palavra)){
        return 1;
    }
    else{
        return -1;
    }
}
int compare(char *palavra1, char *palavra2, char *alfabeto){
    int i=0;
    int j;
    int aux1,aux2;
    while(palavra1[i] && palavra2[i]){
        aux1=0;
        aux2=0;
        for(j=0;j<strlen(alfabeto);j++){
            if(alfabeto[j]== palavra1[i]){
                aux1=j;
            }
            if(alfabeto[j]==palavra2[i]){
                aux2=j;
            }
        }
        if(aux1<aux2){
            return -1;
        }
        else if(aux1>aux2){
            return 1;

        }
        i++;
    }

    if(palavra1[i]){
        return 1;
    }
    else if(palavra2[i]){
        return -1;
    }
    return 0;

    


}
void imprimir(char **words, int tam){
    int i;
    for(i=0;i<tam;i++){
        printf("%s ",words[i]);
    }


}


void criarHeap(char **words, int inicio, int fim,char *alfabeto){
    char *aux;
    int j;
    aux= words[inicio];
    j=inicio*2+1;
    while(j<= fim){
        if(j<fim){
            if(compare(words[j],words[j+1],alfabeto)<0){
                j=j+1;
            }

        }
        if(compare(aux,words[j],alfabeto)<0){
            words[inicio]=words[j];
            inicio=j;
            j=2*inicio+1;

        }
        else{
            j=fim+1;
        }

    }

    words[inicio]=aux;
    

}

void heapSort(char **words, int tam, char *alfabeto){
    int i;
    char *aux;
    for(i=(tam-1)/2;i>=0;i--){
        criarHeap(words,i,tam-1,alfabeto);

    } 
    for(i=tam-1;i>=1;i--){
        aux=words[0];
        words[0]=words[i];
        words[i]=aux;
        criarHeap(words,0,i-1,alfabeto);
        
    }
}


int main(){

    char **words;
    int tam;
    int tam2;
    int i;
    char *aux=NULL;
    int flag=0;
    

    scanf("%d %d", &tam,&tam2);
    char *alfabeto = (char*) malloc(tam2+1 * sizeof(char));
    scanf("%s",alfabeto);
    words=(char**)malloc(tam *sizeof(char*));
    for(i=0;i<tam;i++){
        words[i]=(char*)malloc(MAX_SIZE*sizeof(char));
        scanf("%s", words[i]);
    }
    for(i=0; i<tam && flag==0; i++) {
        if(verifica(alfabeto, words[i]) == -1) {
            printf("A palavra %s eh invalida", words[i]);
            flag = 1;
        }
    }
    if(i==tam){
        heapSort(words,tam,alfabeto);
        imprimir(words,tam);

    }



    
   


    


    //libera memoria alocada para cada palavra
    for(i=0;i<tam;i++){
        free(words[i]);
    }
    free(alfabeto);
    free(words);
}