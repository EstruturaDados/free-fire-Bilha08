#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes globais
#define MAX_ITENS 10
#define TAM_STRING 30

// Definição das structs
typedef struct
{
    char nome[TAM_STRING];
    char tipo[TAM_STRING];
    int quantidade;
} ItemMochila;

// Escopo das funções
void adiciornarItem(ItemMochila *itens, int *quantidadeAtual);
void removerItem(ItemMochila *itens, int *quantidadeAtual);
void buscarItem(ItemMochila *itens, int quantidadeAtual);
void exibirMochila(ItemMochila *itens, int quantidadeAtual);
void limparBufferDeEntrada();

// Função principal
int main()
{
    ItemMochila itens[MAX_ITENS];
    int quantidadeAtual = 0;
    int opcao;

    printf("=========================================\n");
    printf("       MOCHILA DE SOBREVIÊNCIA\n");
    printf("=========================================\n");
    printf("Itens na mochila: %d/%d\n", quantidadeAtual, MAX_ITENS);
    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar item (Loot)\n");
        printf("2. Remover item\n");
        printf("3. Buscar item\n");
        printf("4. Listar itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferDeEntrada();
        printf("\n");

        switch (opcao)
        {
        case 1:
            adiciornarItem(itens, &quantidadeAtual);
            exibirMochila(itens, quantidadeAtual);
            break;
        case 2:
            removerItem(itens, &quantidadeAtual);
            exibirMochila(itens, quantidadeAtual);
            break;
        case 3:
            buscarItem(itens, quantidadeAtual);
            break;
        case 4:
            exibirMochila(itens, quantidadeAtual);
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Implementações das funções
// função para limpar o buffer de entrada
void limparBufferDeEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função para adicionar item
void adiciornarItem(ItemMochila *itens, int *quantidadeAtual)
{
    // Verefica se a mochila está cheia
    if (*quantidadeAtual >= MAX_ITENS)
    {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    fgets(itens[*quantidadeAtual].nome, TAM_STRING, stdin);
    itens[*quantidadeAtual].nome[strcspn(itens[*quantidadeAtual].nome, "\n")] = 0; // Remove o caractere de nova linha

    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    fgets(itens[*quantidadeAtual].tipo, TAM_STRING, stdin);
    itens[*quantidadeAtual].tipo[strcspn(itens[*quantidadeAtual].tipo, "\n")] = 0;

    printf("Digite a quantidade do item: ");
    scanf("%d", &itens[*quantidadeAtual].quantidade);
    limparBufferDeEntrada();
    printf("\n");

    (*quantidadeAtual)++;
    printf("Item adicionado a mochila.\n");
    printf("\n");
}
// Função para remover item
void removerItem(ItemMochila *itens, int *quantidadeAtual)
{
    // Verifica se a mochila está vazia
    if (*quantidadeAtual == 0)
    {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }
    // Cria uma variável para armazenar o nome do item a ser removido
    char texto[TAM_STRING];

    printf("Digite o nome do item a ser removido: ");
    fgets(texto, TAM_STRING, stdin);
    texto[strcspn(texto, "\n")] = 0;
    printf("\n");

    // Procura o item pelo nome
    for (int i = 0; i < *quantidadeAtual; i++)
    {
        // Compara o nome do item com o texto fornecido
        if (strcmp(itens[i].nome, texto) == 0)
        {
            // Desloca os itens seguintes para preencher o espaço do item removido
            for (int j = i; j < *quantidadeAtual - 1; j++)
            {
                itens[j] = itens[j + 1];
            }
            (*quantidadeAtual)--; // Decrementa a quantidade de itens na mochila
            printf("Item '%s' removido da mochila.\n", texto);
            printf("\n");
            return;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n", texto);
    printf("\n");
}
// Função para buscar item
void buscarItem(ItemMochila *itens, int quantidadeAtual)
{
    // Verifica se a mochila está vazia
    if (quantidadeAtual == 0)
    {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char texto[TAM_STRING];

    printf("Digite o nome do item a ser buscado: ");
    fgets(texto, TAM_STRING, stdin);
    texto[strcspn(texto, "\n")] = 0;
    printf("\n");

    for (int i = 0; i < quantidadeAtual; i++)
    {
        if (strcmp(itens[i].nome, texto) == 0)
        {
            printf("Item encontrado na mochila na posicao %d\n", i + 1);
            printf("Nome: %s\n", itens[i].nome);
            printf("Tipo: %s\n", itens[i].tipo);
            printf("Quantidade: %d\n", itens[i].quantidade);
            return;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n", texto);
    printf("\n");
}
// Função para listar itens
void exibirMochila(ItemMochila *itens, int quantidadeAtual)
{
    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", quantidadeAtual, MAX_ITENS);
    printf("------------------------------------------------\n");
    printf("%-20s| %-20s| %-20s\n", "NOME", "TIPO", "QUANTIDADE");
    for (int i = 0; i < quantidadeAtual; i++)
    {
        printf("%-20s| %-20s| %-20d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
    }
    printf("------------------------------------------------\n");
    printf("Pressione Enter para continuar...\n");
    getchar();
}