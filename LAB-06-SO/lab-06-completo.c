#include <stdio.h>
#include <stdlib.h>

struct reg {
    int conteudo;
    struct reg *prox;
};
typedef struct reg celula;

// Função para imprimir todos os valores da lista
void imprime_lista(celula *le) {
    celula *p = le;
    printf("Elementos da lista: ");
    while (p != NULL) {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

// Função para remover um elemento da lista baseado em seu valor
void remove_elemento(celula **le, int valor) {
    celula *atual = *le, *anterior = NULL;
    while (atual != NULL && atual->conteudo != valor) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return; // Elemento não encontrado
    if (anterior == NULL) { // Remover o primeiro elemento
        *le = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual); // Libera a memória do elemento removido
}

// Função para calcular e imprimir o tamanho de uma célula em bytes
void calcula_tamanho_celula() {
    printf("Tamanho de uma célula: %zu bytes\n", sizeof(celula));
}

// Função para calcular o número máximo de elementos na lista
void calcula_max_elementos() {
    size_t tamanho_celula = sizeof(celula);
    int64_t memoria_simulada = 1024 * 1024 * 1024; // Simulando 1 GB de memória
    int64_t max_elementos = memoria_simulada / tamanho_celula;
    printf("Número máximo de elementos possíveis na lista (simulação): %lld\n", max_elementos);
}

// Função para liberar toda a memória alocada para a lista
void libera_lista(celula *le) {
    celula *atual = le;
    celula *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int main() {
    // Criação de três instâncias da lista encadeada
    celula *primeira = (celula *)malloc(sizeof(celula));
    celula *segunda = (celula *)malloc(sizeof(celula));
    celula *terceira = (celula *)malloc(sizeof(celula));

    // Inicialização dos valores das células
    primeira->conteudo = 1;
    primeira->prox = segunda;
    segunda->conteudo = 2;
    segunda->prox = terceira;
    terceira->conteudo = 3;
    terceira->prox = NULL;

    // Impressão dos valores da lista
    imprime_lista(primeira);

    // Cálculo do tamanho de uma célula
    calcula_tamanho_celula();

    // Cálculo do número máximo de elementos na lista (com base em uma memória simulada)
    calcula_max_elementos();

    // Remoção de um elemento da lista e reimpressão
    remove_elemento(&primeira, 2);
    printf("Após remover o elemento com valor 2:\n");
    imprime_lista(primeira);

    // Liberação de toda a lista
    libera_lista(primeira);
    return 0;
}
