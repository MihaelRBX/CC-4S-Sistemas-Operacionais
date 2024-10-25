#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>  /*utilizando macOS tive que usar esse cabecalho e a função sysctl() para acessar informações
do sistema, como o tamanho total de memória RAM (HW_MEMSIZE).*/

struct reg {
    int conteudo;
    struct reg *prox;
};

typedef struct reg celula;


void imprime_lista(celula *le) {
    celula *p = le;
    printf("Elementos da lista: ");
    while (p != NULL) {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

void remove_elemento(celula **le, int valor) {
    celula *atual = *le, *anterior = NULL;

    while (atual != NULL && atual->conteudo != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return;

    if (anterior == NULL) {
        *le = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
}


void calcula_tamanho_celula() {
    printf("Tamanho de uma célula: %zu bytes\n", sizeof(celula));
}

//obtendo a quantidade de memória total no macOS
int64_t calcula_memoria_total() {
    int mib[2];
    int64_t memoria_total;
    size_t len = sizeof(memoria_total);

    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;

    sysctl(mib, 2, &memoria_total, &len, NULL, 0);
    printf("Memória total do sistema: %lld bytes\n", memoria_total);
}

void calcula_max_elementos() {
    int64_t memoria_total = calcula_memoria_total();
    size_t tamanho_celula = sizeof(celula);
    
    int64_t max_elementos = memoria_total / tamanho_celula;
    printf("Número máximo de elementos possíveis na lista: %lld\n", max_elementos);
}


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
    
    celula *primeira = (celula *)malloc(sizeof(celula));
    celula *segunda = (celula *)malloc(sizeof(celula));
    celula *terceira = (celula *)malloc(sizeof(celula));

    primeira->conteudo = 1;
    primeira->prox = segunda;
    
    segunda->conteudo = 2;
    segunda->prox = terceira;
    
    terceira->conteudo = 3;
    terceira->prox = NULL; 

    imprime_lista(primeira);

    calcula_tamanho_celula();

    calcula_memoria_total();

    calcula_max_elementos();
    
    remove_elemento(&primeira, 2);
    printf("Após remover o elemento com valor 2:\n");
    imprime_lista(primeira);

    libera_lista(primeira);

    return 0;
}
