// Vitor Gonçalves Reis da Silva 
// RA: 156670
// AED II

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

No* criaNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void inicializarGrafo(No* grafo[], int totalNo) {
    for (int i = 0; i < totalNo; i++) {
        grafo[i] = NULL;
    }
}

void adicionar_aresta(No* grafo[], int origem, int dest) {
    No* novoNo = criaNo(dest);

    if (grafo[origem] == NULL) {
        grafo[origem] = novoNo;
    } 
    else{
        No* prev = NULL;
        No* curr = grafo[origem];
        while(curr != NULL && curr->valor < dest) {
            prev = curr;
            curr = curr->prox;
        }
        if(prev == NULL) {
            novoNo->prox = grafo[origem];
            grafo[origem] = novoNo;
        } 
        else {
            prev->prox = novoNo;
            novoNo->prox = curr;
        }
    }
}

void BFS(No* grafo[], int NoInicio, int totalNo) {
    int front = 0;
    int rear = 0;
    int* visitado = (int*)malloc(totalNo * sizeof(int));
    if (visitado == NULL) {
        printf("Erro de alocacao");
        return;
    }

    int queue[totalNo];


    for (int i = 0; i < totalNo; i++) {
        visitado[i] = 0;
    }

    visitado[NoInicio] = 1;
    queue[rear++] = NoInicio;

    while (front != rear) {
        int currentNode;
        currentNode= queue[front++];
        printf("%d ", currentNode);

        No* temp = grafo[currentNode];
        while (temp != NULL) {
            int vizinho = temp->valor;
            if (!visitado[vizinho]) {
                visitado[vizinho] = 1;
                queue[rear++] = vizinho;
            }
            temp = temp->prox;
        }
    }

    free(visitado);
}


void DFS_vizinho(No* grafo[], int currentNode, int visitado[]) {
    visitado[currentNode] = 1;
    printf("%d ", currentNode);

    No* temp = grafo[currentNode];
    while (temp != NULL) {
        int vizinho;
        vizinho = temp->valor;
        if (!visitado[vizinho]) {
            DFS_vizinho(grafo, vizinho, visitado);
        }
        temp = temp->prox;
    }
}

void DFS(No* grafo[], int NoInicio, int totalNo) {
    int* visitado = (int*)malloc(totalNo * sizeof(int));
    if (visitado == NULL) {
        printf("Erro de alocacao");
        return;
    }

    for (int i = 0; i < totalNo; i++) {
        visitado[i] = 0;
    }

    DFS_vizinho(grafo, NoInicio, visitado);

    free(visitado);
}




int main() {
    int NoInicio, totalNo, arestas;
    int origem, dest;
    int i;
    scanf("%d", &NoInicio);
    scanf("%d %d", &totalNo, &arestas);

    No* grafo[totalNo];
    inicializarGrafo(grafo,totalNo);

    for (i = 0; i < arestas; i++) {
        scanf("%d %d", &origem, &dest);
        adicionar_aresta(grafo, origem, dest);
    }
    BFS(grafo, NoInicio, totalNo);
    printf("\n");

    DFS(grafo, NoInicio, totalNo);
    printf("\n");

}
