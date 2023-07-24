// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_SIZE 20


int maior(char **words, int tam){// busca a maior string antes de adiconar os espaços
    int i;
    int maior=0;
    for(i=0;i<tam;i++){
        if(maior<strlen(words[i])){
            maior=strlen(words[i]);
        }
    }
    return maior;

}



void imprimir(char **words, int tam){
    int i;
    for(i=0;i<tam;i++){
        printf("%s.\n",words[i]);
    }


}
void imprimir2(char **words, int tam){// imprimi sem o ponto final
    int i;
    for(i=0;i<tam;i++){
        printf("%s\n",words[i]);
    }


}

void minuscula(char *word){// tranforma as letras em minuscula
    int i;
    int len=strlen(word);
    for(i=0;i<len;i++){
        word[i]=tolower(word[i]);
    }
}

void preencher(char **words, int tam) { // preenche com espacos ate o tamanho da string dar 20
    int i, j, len;
    int max_len = maior(words, tam);

    for(i = 0; i < tam; i++) {
        len = strlen(words[i]);
        if (len < max_len) {
            for(j = len; j < max_len; j++) {
                words[i][j] = ' ';
            }
            words[i][j] = '\0';
        }
    }
}
void counting_sort(char **words, int tam, int pos, char *alfabeto) {
    int *count = (int*)calloc(strlen(alfabeto), sizeof(int));
    char **temp = (char**)malloc(tam * sizeof(char*));
    int i;
    
    for (i = 0; i < tam; i++) {
        int atual;
        if (pos >= strlen(words[i])) {
            atual = 0;
        } else {
            char* aux = strchr(alfabeto, words[i][pos]);
            if(aux==NULL){
                atual=0;
            }
            else{
                atual=aux-alfabeto;
            }
        }
        count[atual]++;
    }
    
    for (i = 1; i < strlen(alfabeto); i++) {// faz a soma para saber em qual indice colocar
        count[i] += count[i-1];
    }
    for(int i=0;i<strlen(alfabeto);i++){
        printf("%d ",count[i]);
    }
    printf("\n");
    for (i = tam - 1; i >= 0; i--) {
        int atual;
        if (pos >= strlen(words[i])) {
            atual = 0;
        } else {
            char* aux = strchr(alfabeto, words[i][pos]);
            if(aux==NULL){
                atual=0;
            }
            else{
                atual=aux-alfabeto;
            }
        }
        temp[count[atual] - 1] = words[i];
        count[atual]--;
    }
    
    for (i = 0; i < tam; i++) {
        words[i] = temp[i];
    }
    
    free(count);
    free(temp);
}

void radix_sort(char **words, int tam, char *alfabeto) {
    int max_len = maior(words, tam);
    int pos;
    for (pos = max_len - 1; pos >= 0; pos--) {
        counting_sort(words, tam, pos, alfabeto);
    }
}


int main(){
    int tam;
    char **words;
    int i;

    scanf("%d",&tam);
    char *alfabeto = (char*) malloc(26 * sizeof(char));
    scanf("%s",alfabeto);

    char*novo_alfabeto=(char*) malloc((strlen(alfabeto) + 2) * sizeof(char));
    strcpy(&novo_alfabeto[1], alfabeto);
    novo_alfabeto[0] = ' ';
    novo_alfabeto[strlen(alfabeto) + 1] = '\0';// adiciona um espaço no inicio do alfabeto
    free(alfabeto);
    alfabeto = novo_alfabeto;
    words=(char**)malloc(tam *sizeof(char*));
    for(i=0;i<tam;i++){
        words[i]=(char*)malloc(MAX_SIZE*sizeof(char));
        scanf("%s", words[i]);
        minuscula(words[i]);
    }

    imprimir(words,tam);
    int k=maior(words,tam);
    printf("%d\n",k);
    preencher(words,tam);
    radix_sort(words, tam, alfabeto);
    imprimir2(words,tam);
    

     //libera memoria alocada para cada palavra
    for(i=0;i<tam;i++){
        free(words[i]);
    }
    free(alfabeto);
    free(words);


    
}



