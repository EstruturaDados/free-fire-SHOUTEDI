// Bibliotecas necessárias
#include <stdio.h>    // Para entrada e saída (printf, scanf)
#include <stdlib.h>   // Para limpeza do console (system)
#include <string.h>   // Para manipulação de strings (strcmp, strcpy)

// --- Constantes Globais ---
// Usar #define é uma boa prática para evitar "números mágicos" no código.
// Facilita a manutenção.
#define MAX_ITENS 10   // Capacidade máxima da mochila
#define MAX_NOME 50    // Tamanho máximo para o nome do item
#define MAX_TIPO 30    // Tamanho máximo para o tipo do item

/*
 * -----------------------------------------------------------------------------
 * 🎒 Definição da Estrutura (Struct) do Item
 * -----------------------------------------------------------------------------
 * A 'struct' é um tipo de dado composto que agrupa diferentes
 * variáveis sob um mesmo nome. Perfeito para modelar um "Item".
 */
struct Item {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
};

// --- Protótipos das Funções ---
// Declarar os "cabeçalhos" das funções antes do main é uma boa prática
// de organização em C. O compilador sabe que elas existem.
void exibirMenu();
void limparTela();
void limparBuffer();
void pausarSistema();

void adicionarItem(struct Item mochila[], int *contador);
void removerItem(struct Item mochila[], int *contador);
void listarItens(struct Item mochila[], int contador);


/*
 * =============================================================================
 * 👑 FUNÇÃO PRINCIPAL (main)
 * =============================================================================
 * Ponto de entrada do programa. Controla o menu e o loop principal.
 */
int main() {
    // Declaração do nosso vetor estático (mochila)
    struct Item mochila[MAX_ITENS];
    
    // Variável para controlar quantos itens realmente temos na mochila
    int contadorItens = 0;
    int opcao;

    // Loop principal do menu.
    // O 'do-while' garante que o menu seja exibido pelo menos uma vez.
    do {
        limparTela();
        exibirMenu();
        
        // Lê a opção do usuário
        // O espaço antes do %d ajuda a consumir newlines pendentes,
        // mas a função limparBuffer() é mais garantida.
        scanf("%d", &opcao);
        limparBuffer(); // ESSENCIAL após ler números antes de ler strings

        // 'switch' para tratar a escolha do usuário
        switch (opcao) {
            case 1:
                // Passamos a mochila e o ENDEREÇO do contador.
                // Assim, a função 'adicionarItem' pode alterar o valor original
                // do contador (passagem por referência).
                adicionarItem(mochila, &contadorItens);
                break;
            case 2:
                // Mesmo caso para 'removerItem'
                removerItem(mochila, &contadorItens);
                break;
            case 3:
                // Para 'listarItens', não precisamos alterar o contador,
                // então passamos apenas o valor (passagem por valor).
                listarItens(mochila, contadorItens);
                break;
            case 0:
                printf("\nSaindo do sistema... Até a proxima sobrevivente!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            pausarSistema();
        }

    } while (opcao != 0);

    return 0; // Indica que o programa terminou com sucesso
}


/*
 * =============================================================================
 * 🛠️ Funções Auxiliares (Menu e Limpeza)
 * =============================================================================
 */

// Mostra o menu de opções
void exibirMenu() {
    printf("==========================================\n");
    printf(" 🔫🎒 Desafio Codigo da Ilha - Free Fire 🎒🔫\n");
    printf("              (Nivel Novato)\n");
    printf("==========================================\n");
    printf("1. Adicionar item a mochila\n");
    printf("2. Remover item da mochila (por nome)\n");
    printf("3. Listar itens da mochila\n");
    printf("0. Sair (Escapar da ilha)\n");
    printf("------------------------------------------\n");
    printf("Escolha sua acao, sobrevivente: ");
}

// Limpa o buffer de entrada (stdin)
// ESSENCIAL em C ao misturar scanf("%d") e leituras de string (com fgets ou scanf %s).
// O scanf("%d") deixa o '\n' (Enter) no buffer, que é lido pela
// próxima função de string, causando bugs.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Limpa o terminal
void limparTela() {
    // system("cls") para Windows, system("clear") para Linux/Mac
    // É uma chamada de sistema, não é C puro, mas é útil para menus.
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Pausa a execução para o usuário ler a saída
void pausarSistema() {
    printf("\nPressione ENTER para continuar...");
    limparBuffer(); // Usa a mesma lógica para esperar o "Enter"
}


/*
 * =============================================================================
 * 🚀 Funções Principais (Inventário)
 * =============================================================================
 */

/**
 * @brief Adiciona um novo item à mochila.
 * @param mochila O array de struct Item.
 * @param contador Um ponteiro para o contador de itens (para alterá-lo).
 */
void adicionarItem(struct Item mochila[], int *contador) {
    // O 'contador' aqui é um ponteiro.
    // Para acessar/modificar o VALOR da variável original (lá da main),
    // usamos o operador de derreferência '*'
    
    // 1. Verificar se a mochila está cheia
    if (*contador >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return; // Sai da função
    }

    // 2. Se houver espaço, solicita os dados do novo item
    printf("\n--- Adicionando Novo Item ---\n");
    
    // Usamos o índice atual (*contador) para adicionar o novo item
    struct Item *novoItem = &mochila[*contador];

    printf("Nome do item: ");
    // Lê o nome. Usamos %[^\n] para permitir nomes com espaços.
    scanf("%[^\n]", novoItem->nome);
    limparBuffer();

    printf("Tipo do item (Ex: Arma, Municao, Medkit): ");
    scanf("%[^\n]", novoItem->tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &novoItem->quantidade);
    limparBuffer();

    // 3. Incrementa o contador de itens
    (*contador)++; // Incrementa o valor da variável original na main

    printf("\n[SUCESSO] Item '%s' adicionado a mochila!\n", novoItem->nome);
}

/**
 * @brief Remove um item da mochila buscando pelo nome.
 * @param mochila O array de struct Item.
 * @param contador Um ponteiro para o contador de itens.
 */
void removerItem(struct Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("\n[INFO] A mochila ja esta vazia.\n");
        return;
    }

    char nomeParaRemover[MAX_NOME];
    printf("\n--- Removendo Item ---\n");
    printf("Qual item deseja remover (nome exato): ");
    scanf("%[^\n]", nomeParaRemover);
    limparBuffer();

    int indiceEncontrado = -1; // Flag para marcar a posição do item

    // 1. Busca Sequencial (Obrigatória no Nível Novato)
    // Percorre o array comparando os nomes
    for (int i = 0; i < *contador; i++) {
        // strcmp retorna 0 se as strings forem idênticas
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceEncontrado = i;
            break; // Item encontrado, podemos parar o loop
        }
    }

    // 2. Trata o resultado da busca
    if (indiceEncontrado == -1) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeParaRemover);
    } else {
        // 3. Lógica de Remoção (Shift-Left)
        // Para "remover" um item de um array estático, nós "puxamos"
        // todos os itens que vêm DEPOIS dele uma posição para a esquerda,
        // sobrescrevendo o item que queremos remover.
        
        for (int i = indiceEncontrado; i < (*contador - 1); i++) {
            // Copia o item da posição [i+1] para a posição [i]
            mochila[i] = mochila[i+1];
            // Em C, podemos atribuir structs diretamente (copia membro a membro)
        }

        // 4. Decrementa o contador total de itens
        (*contador)--;

        printf("\n[SUCESSO] Item '%s' removido da mochila!\n", nomeParaRemover);
    }
}

/**
 * @brief Lista todos os itens atualmente na mochila.
 * @param mochila O array de struct Item.
 * @param contador O número atual de itens (passado por valor).
 */
void listarItens(struct Item mochila[], int contador) {
    printf("\n===================================================\n");
    printf(" 🎒 ITENS NA MOCHILA (%d / %d) 🎒\n", contador, MAX_ITENS);
    printf("===================================================\n");

    if (contador == 0) {
        printf("\nA mochila esta vazia. Hora de lootear!\n");
        printf("===================================================\n");
        return;
    }

    // 1. Imprime o Cabeçalho da Tabela
    // Usamos %-Ns para formatar o texto alinhado à esquerda
    // Ex: %-20s -> reserva 20 espaços para a string, alinhada à esquerda
    printf("%-20s | %-15s | %s\n", "Item", "Tipo", "Quantidade");
    printf("---------------------------------------------------\n");

    // 2. Loop para imprimir cada item
    for (int i = 0; i < contador; i++) {
        printf("%-20s | %-15s | %d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("===================================================\n");
}