#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct no {
    int ordem;          
    int num_chaves;
    int *chaves;
    struct no **filhos;
    bool folha;
} No;

// Função para criar um novo nó

No* criar_no(int ordem, bool folha) {
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->ordem = ordem;
    novo_no->num_chaves = 0;
    novo_no->chaves = (int*)malloc((ordem * 2) * sizeof(int));
    novo_no->filhos = (No**)malloc((ordem * 2 + 1) * sizeof(No*));
    novo_no->folha = folha;
    return novo_no;
}

// Função para inserir uma chave em um nó não cheio
void inserir_chave_nao_cheio(No* no, int chave) {
    int i = no->num_chaves - 1;
    
    if (no->folha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        
        no->chaves[i + 1] = chave;
        no->num_chaves++;
    } 
    else{
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;
        if (no->filhos[i]->num_chaves == no->ordem * 2) {
            dividir_filho(no, i, no->filhos[i]); // Se o filho estiver cheio dividir
            if (chave > no->chaves[i]) {
                i++;
            }
        }
        inserir_chave_nao_cheio(no->filhos[i], chave);
    }
}

// Função para dividir um filho cheio
void dividir_filho(No* pai, int indice_filho, No* filho) {
    int ordem = filho->ordem;
    int chave_mediana = filho->chaves[ordem];
    int i;

    No* novo_filho = criar_no(ordem, filho->folha);
    novo_filho->num_chaves = ordem - 1;

    for (i = 0; i < ordem - 1; i++) {
        novo_filho->chaves[i] = filho->chaves[i + ordem + 1];
    }

    if (!filho->folha) {
        for (i = 0; i < ordem; i++) {
            novo_filho->filhos[i] = filho->filhos[i + ordem + 1];
        }
    }

    filho->num_chaves = ordem;
    for (i = pai->num_chaves; i > indice_filho; i--) {
        pai->filhos[i + 1] = pai->filhos[i];
    }

    pai->filhos[indice_filho + 1] = novo_filho;

    for (i = pai->num_chaves - 1; i >= indice_filho; i--) {
        pai->chaves[i + 1] = pai->chaves[i];
    }

    pai->chaves[indice_filho] = chave_mediana;
    pai->num_chaves++;
}


// Função para inserir 

No* inserir(No* raiz, int ordem, int chave) {
    if (raiz == NULL) {
        No* novo_no = criar_no(ordem, true);
        novo_no->chaves[0] = chave;
        novo_no->num_chaves = 1;
        return novo_no;
    }

    if (raiz->num_chaves == raiz->ordem * 2) {
        No* novo_no = criar_no(raiz->ordem, false);
        novo_no->filhos[0] = raiz;
        dividir_filho(novo_no, 0, raiz);
        inserir_chave_nao_cheio(novo_no, chave);
        return novo_no;
    } else {
        inserir_chave_nao_cheio(raiz, chave);
        return raiz;
    }
}



// Função para liberar a memória 

void liberar_arvore(No* no) {
    int i;
    if (no != NULL) {
        if (!no->folha) {
            for (i = 0; i <= no->num_chaves; i++) {
                liberar_arvore(no->filhos[i]);
            }
        }
        
        free(no->chaves);
        free(no->filhos);
        free(no);
    }
}


void buscar_e_imprimir(No* no, int busca, int raiz_chaves) {
    int i = 0;
    int j;
    while (i < no->num_chaves && busca > no->chaves[i]) {
        i++;
    }
    if (no->chaves[i] == busca) {
        printf("%d\n",raiz_chaves);
        printf("%d\n", no->num_chaves);
        
        for (j = 0; j < no->num_chaves; j++) {
            printf("%d ", no->chaves[j]);
        }
        printf("\n");
    } else if (no->folha) {
        printf("%d\n",raiz_chaves);
        printf("Valor não encontrado");
    } else {
        buscar_e_imprimir(no->filhos[i], busca,raiz_chaves);
    }
}



int main() {
    No* raiz = NULL;
    int valor=0;
    int ordem;
    int i;
    int raiz_chaves;
    scanf("%d",&ordem);
    for(i=0; valor>=0; i++){
        scanf("%d",&valor);
        if(valor>= 0){
            raiz=inserir(raiz,ordem,valor);

        }
        
    }
    scanf("%d",&valor);
    raiz_chaves=raiz->num_chaves;
    buscar_e_imprimir(raiz,valor,raiz_chaves);
    liberar_arvore(raiz);
    
    return 0;
}
