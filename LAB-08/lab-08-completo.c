//Aluno: Mihael Rommel B. Xavier
// RA: 10239617
// Link github: https://github.com/MihaelRBX/CC-4S-Sistemas-Operacionais/blob/a46a99567eb66c98881b6b89a4912031639a4088/LAB-08/lab-08-completo.c
#include <stdio.h>
#include <stdbool.h>

// constantes para tamanhos
#define TAMANHO_PAGINA 4  // Tamanho da página em KB
#define NUM_FRAMES 8 // Número de frames na memória física
#define NUM_PAGINAS 16    // Número de páginas na memória virtual

// Estrutura frame
typedef struct {
    int id;
    bool ocupado;
    int pagina; //página alocada (-1 se livre)
} Frame;

// Estrutura página
typedef struct {
    int id;
    int frame; // frame físico (-1 se não alocado)
} Pagina;

// Estrutura tabela
typedef struct {
    int tabela[NUM_PAGINAS]; //mapeia paginas para frames (-1 se não mapeada)
} TabelaDePaginas;

// Iniciando as memórias
Frame memoria_fisica[NUM_FRAMES];
Pagina memoria_virtual[NUM_PAGINAS];
TabelaDePaginas tabela_de_paginas;

// Função para inicializar a memória física
void inicializar_memoria_fisica() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        memoria_fisica[i].id = i;
        memoria_fisica[i].ocupado = false;
        memoria_fisica[i].pagina = -1;
    }
}

// Função para inicializar a memória virtual
void inicializar_memoria_virtual() {
    for (int i = 0; i < NUM_PAGINAS; i++) {
        memoria_virtual[i].id = i;
        memoria_virtual[i].frame = -1;
        tabela_de_paginas.tabela[i] = -1; // Inicialmente, sem mapeamento
    }
}

// Função para alocar uma página na memória física
void alocar_pagina(int id_pagina) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (!memoria_fisica[i].ocupado) { // verifica se o frame está livre
            memoria_fisica[i].ocupado = true;
            memoria_fisica[i].pagina = id_pagina;
            memoria_virtual[id_pagina].frame = i;
            tabela_de_paginas.tabela[id_pagina] = i; // mapeia a página para o frame
            printf("Pagina %d alocada no frame %d\n", id_pagina, i);
            return;
        }
    }
    // Se não existir frame livre
    printf("Falta de frame livre para a página %d\n", id_pagina);
}

// Função para traduzir um endereço virtual para fisico
void traduzir_endereco(int endereco_virtual) {
    int id_pagina = endereco_virtual / TAMANHO_PAGINA; // calcula o número da página
    int offset = endereco_virtual % TAMANHO_PAGINA;    // calcula o offset

    int frame_id = tabela_de_paginas.tabela[id_pagina];
    if (frame_id != -1) { // verifica se a página está mapeada para um frame
        int endereco_fisico = frame_id * TAMANHO_PAGINA + offset;
        printf("Endereço virtual %d traduzido para %d\n", endereco_virtual, endereco_fisico);
    } else {
        // se a página existe na memória física
        printf("Page fault! Página %d não está presente na memória física.\n", id_pagina);
    }
}

// main
int main() {
    // Inicializa
    inicializar_memoria_fisica();
    inicializar_memoria_virtual();

    // Aloca
    alocar_pagina(0);
    alocar_pagina(1);
    alocar_pagina(2);
    alocar_pagina(3);

    // Endereços virtuais
    int enderecos_teste[] = {0, 5, 8, 12, 20, 25, 30, 35};
    int num_enderecos = sizeof(enderecos_teste) / sizeof(enderecos_teste[0]);

    // tradução
    for (int i = 0; i < num_enderecos; i++) {
        traduzir_endereco(enderecos_teste[i]);
    }

    return 0;
}
