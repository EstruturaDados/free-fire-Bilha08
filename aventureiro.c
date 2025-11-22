#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais
#define TAM_STRING 30
#define MAX_ITENS 10
int comparacoesBuscaBinaria = 0;    // Contador de comparações na busca binária
int comparacoesBuscaSequencial = 0; // Contador de comparações na busca sequencial

// Struct para representar um item na mochila
typedef struct
{
    char nome[TAM_STRING];
    char tipo[TAM_STRING];
    int quantidade;
} ItemMochila;

// Struct para representar um nó na lista encadeada de itens
typedef struct NoMochila
{
    ItemMochila item;
    struct NoMochila *proximo;
} NoMochila;

// Protótipos das funções
// Operações com o vetor de itens
void adicionarItemVetor(ItemMochila *itens, int *quantidadeAtual);
void removerItemVetor(ItemMochila *itens, int *quantidadeAtual);
void exibirMochilaVetor(const ItemMochila *itens, int quantidadeAtual);
void ordenacaoDoVetor(ItemMochila *itens, int quantidadeAtual);
void buscaSequencialItemVetor(const ItemMochila *itens, int quantidadeAtual);
void buscaBinariaItemVetor(const ItemMochila *itens, int quantidadeAtual);

// Operações com a lista encadeada de itens
void adicionarItemListaEncadeada(NoMochila **primeiroNo, int *quantidadeAtual);
void removerItemListaEncadeada(NoMochila **primeiroNo, int *quantidadeAtual);
void buscarItemListaEncadeada(const NoMochila *primeiroNo);
void exibirListaEncadeada(const NoMochila *primeiroNo);
void liberarListaEncadeada(NoMochila **primeiroNo);

// Funçao limpar buffer de entrada
void limparBufferDeEntrada();
// Menus
void menu(ItemMochila *itens, NoMochila **primeiroNo, int *quantidadeAtual);
void menuVetor(ItemMochila *itens, int *quantidadeAtual);
void menuListaEncadeada(NoMochila **primeiroNo, int *quantidadeAtual);

// Função principal
int main()
{
    // Vetor de itens
    ItemMochila itens[MAX_ITENS];
    // Lista encadeada de itens
    NoMochila *primeiroNo = NULL;

    int quantidadeAtual = 0; // Quantidade atual de itens na mochila

    // Chama o menu
    menu(itens, &primeiroNo, &quantidadeAtual);

    // libera memória antes de sair (caso não tenha saído pelo menu)
    liberarListaEncadeada(&primeiroNo);

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
//------------------------------------------------------
// Implementação das funções do vetor de itens
//------------------------------------------------------
void adicionarItemVetor(ItemMochila *itens, int *quantidadeAtual)
{
    // Verifica se a mochila está cheia
    if (*quantidadeAtual >= MAX_ITENS)
    {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    fgets(itens[*quantidadeAtual].nome, TAM_STRING, stdin);
    itens[*quantidadeAtual].nome[strcspn(itens[*quantidadeAtual].nome, "\n")] = 0; // Remove o '\n'

    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    fgets(itens[*quantidadeAtual].tipo, TAM_STRING, stdin);
    itens[*quantidadeAtual].tipo[strcspn(itens[*quantidadeAtual].tipo, "\n")] = 0;

    printf("Digite a quantidade do item: ");
    if (scanf("%d", &itens[*quantidadeAtual].quantidade) != 1)
    {
        printf("Entrada inválida. Abortando adição.\n");
        limparBufferDeEntrada();
        return;
    }
    limparBufferDeEntrada();
    printf("\n");

    (*quantidadeAtual)++;
    printf("Item adicionado a mochila.\n\n");
}

// Função para remover item
void removerItemVetor(ItemMochila *itens, int *quantidadeAtual)
{
    // Verifica se a mochila está vazia
    if (*quantidadeAtual == 0)
    {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }
    // Variável para armazenar o nome do item a ser removido
    char texto[TAM_STRING];

    printf("Digite o nome do item a ser removido: ");
    fgets(texto, TAM_STRING, stdin);
    texto[strcspn(texto, "\n")] = 0;
    printf("\n");

    // Procura o item pelo nome
    for (int i = 0; i < *quantidadeAtual; i++)
    {
        if (strcmp(itens[i].nome, texto) == 0) // Item encontrado
        {
            // Desloca os itens seguintes para preencher o espaço do item removido
            for (int j = i; j < *quantidadeAtual - 1; j++)
            {
                itens[j] = itens[j + 1];
            }
            (*quantidadeAtual)--; // Decrementa a quantidade de itens na mochila
            printf("Item '%s' removido da mochila.\n\n", texto);
            return;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n\n", texto);
}

// Função para exibir a mochila
void exibirMochilaVetor(const ItemMochila *itens, int quantidadeAtual)
{
    if (quantidadeAtual == 0) // Verifica se a mochila está vazia
    {
        printf("Mochila vazia.\n\n");
        return;
    }
    printf("---Mochila---\n\n");
    for (int i = 0; i < quantidadeAtual; i++)
    {
        printf("Item %d:\n", i + 1);
        printf("Nome: %s\n", itens[i].nome);
        printf("Tipo: %s\n", itens[i].tipo);
        printf("Quantidade: %d\n\n", itens[i].quantidade);
    }
}

// Função para buscar item (sequencial)
void buscaSequencialItemVetor(const ItemMochila *itens, int quantidadeAtual)
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
        comparacoesBuscaSequencial++; // Incrementa o contador de comparações

        if (strcmp(itens[i].nome, texto) == 0)
        {
            printf("Item encontrado na mochila na posicao %d\n", i + 1);
            printf("Nome: %s\n", itens[i].nome);
            printf("Tipo: %s\n", itens[i].tipo);
            printf("Quantidade: %d\n\n", itens[i].quantidade);

            printf("Total de comparacoes (busca sequencial): %d\n\n", comparacoesBuscaSequencial);
            comparacoesBuscaSequencial = 0; // Reseta o contador para a próxima busca
            return;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n\n", texto);
    printf("Total de comparacoes (busca sequencial): %d\n\n", comparacoesBuscaSequencial);
    comparacoesBuscaSequencial = 0;
}

// Função para ordenar o vetor de itens por nome (ordem alfabética)
// Ordenação simples usando o algoritmo Bubble Sort
void ordenacaoDoVetor(ItemMochila *itens, int quantidadeAtual)
{
    for (int i = 0; i < quantidadeAtual - 1; i++)
    {
        for (int j = 0; j < quantidadeAtual - i - 1; j++)
        {
            if (strcmp(itens[j].nome, itens[j + 1].nome) > 0)
            {
                // Troca os itens
                ItemMochila temp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = temp;
            }
        }
    }
}

// Função para buscar item usando busca binária
void buscaBinariaItemVetor(const ItemMochila *itens, int quantidadeAtual)
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

    int inicio = 0;
    int fim = quantidadeAtual - 1;
    int meio;

    while (inicio <= fim) // Loop da busca binária
    {
        meio = inicio + (fim - inicio) / 2;

        comparacoesBuscaBinaria++; // Incrementa o contador de comparações

        int comparacao = strcmp(itens[meio].nome, texto);

        if (comparacao == 0)
        {
            printf("Item encontrado na mochila na posicao %d\n", meio + 1);
            printf("Nome: %s\n", itens[meio].nome);
            printf("Tipo: %s\n", itens[meio].tipo);
            printf("Quantidade: %d\n\n", itens[meio].quantidade);

            printf("Total de comparacoes (busca binaria): %d\n\n", comparacoesBuscaBinaria);
            comparacoesBuscaBinaria = 0;
            return;
        }
        else if (comparacao < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n\n", texto);
    printf("Total de comparacoes (busca binaria): %d\n\n", comparacoesBuscaBinaria);
    comparacoesBuscaBinaria = 0; // Reseta o contador para a próxima busca
}

//------------------------------------------------------
// Implementações das funções da lista encadeada de itens
//------------------------------------------------------
// Função para adicionar item à lista encadeada
void adicionarItemListaEncadeada(NoMochila **primeiroNo, int *quantidadeAtual)
{
    // Verifica se a mochila está cheia
    if (*quantidadeAtual >= MAX_ITENS)
    {
        printf("Mochila cheia! Nao eh possivel adicionar mais itens.\n");
        return;
    }
    // Cria um novo nó e aloca memória para ele
    NoMochila *novoNo = (NoMochila *)malloc(sizeof(NoMochila));
    if (novoNo == NULL)
    {
        printf("Erro ao alocar memória para o novo nó.\n");
        return;
    }
    // Solicita os dados do item ao usuário
    printf("Digite o nome do item: ");
    fgets(novoNo->item.nome, TAM_STRING, stdin);
    novoNo->item.nome[strcspn(novoNo->item.nome, "\n")] = 0;

    printf("Digite o tipo do item (arma, municao, cura, etc.): ");
    fgets(novoNo->item.tipo, TAM_STRING, stdin);
    novoNo->item.tipo[strcspn(novoNo->item.tipo, "\n")] = 0;

    printf("Digite a quantidade do item: ");
    if (scanf("%d", &novoNo->item.quantidade) != 1)
    {
        printf("Entrada inválida. Abortando adição.\n");
        limparBufferDeEntrada();
        free(novoNo);
        return;
    }
    limparBufferDeEntrada();
    printf("\n");

    // Insere o novo nó no início da lista
    novoNo->proximo = *primeiroNo;
    *primeiroNo = novoNo; // Atualiza o ponteiro do primeiro nó para o novo nó

    (*quantidadeAtual)++; // Incrementa a quantidade de itens na mochila
    printf("Item adicionado a mochila.\n\n");
}
// Função para exibir os itens da lista encadeada
void exibirListaEncadeada(const NoMochila *primeiroNo)
{
    const NoMochila *atual = primeiroNo; // Ponteiro para percorrer a lista
    if (atual == NULL)                   // Verifica se a mochila está vazia
    {
        printf("Mochila vazia.\n\n");
        return;
    }
    while (atual != NULL) // Percorre a lista até o final
    {
        printf("--------------------------------------\n");
        printf("Nome: %s\n", atual->item.nome);
        printf("Tipo: %s\n", atual->item.tipo);
        printf("Quantidade: %d\n", atual->item.quantidade);
        printf("--------------------------------------\n\n");
        atual = atual->proximo;
    }
}
// Função para remover item da lista encadeada
void removerItemListaEncadeada(NoMochila **primeiroNo, int *quantidadeAtual)
{
    NoMochila *atual = *primeiroNo; // Ponteiro para percorrer a lista
    NoMochila *anterior = NULL;     // Ponteiro para o nó anterior inicializado como NULL
    char texto[TAM_STRING];

    if (atual == NULL) // Verifica se a mochila está vazia
    {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    printf("Digite o nome do item para remover: ");
    fgets(texto, TAM_STRING, stdin);
    texto[strcspn(texto, "\n")] = 0;

    while (atual != NULL) // Percorre a lista
    {
        if (strcmp(atual->item.nome, texto) == 0)
        {
            if (anterior == NULL)
            {
                *primeiroNo = atual->proximo; // Remove o primeiro nó
            }
            else
            {
                anterior->proximo = atual->proximo; // Remove nó do meio ou fim
            }
            free(atual);
            (*quantidadeAtual)--;
            printf("\nItem '%s' removido da mochila.\n\n", texto);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("\nItem '%s' nao encontrado na mochila.\n\n", texto);
}

// Função para buscar item na lista encadeada
void buscarItemListaEncadeada(const NoMochila *primeiroNo)
{
    const NoMochila *atual = primeiroNo; // Ponteiro para percorrer a lista
    char texto[TAM_STRING];

    if (atual == NULL) // Verifica se a mochila está vazia
    {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    printf("Digite o nome do item a ser buscado: ");
    fgets(texto, TAM_STRING, stdin);
    texto[strcspn(texto, "\n")] = 0;

    while (atual != NULL) // Percorre a lista
    {
        if (strcmp(atual->item.nome, texto) == 0)
        {

            printf("\nItem encontrado na mochila.\n");
            printf("-------------------------------------\n");
            printf("Nome: %s\n", atual->item.nome);
            printf("Tipo: %s\n", atual->item.tipo);
            printf("Quantidade: %d\n", atual->item.quantidade);
            printf("-------------------------------------\n\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("\nItem '%s' nao encontrado na mochila.\n\n", texto);
}
// Função para liberar a memória alocada para a lista encadeada
void liberarListaEncadeada(NoMochila **primeiroNo)
{
    NoMochila *atual = *primeiroNo; // Ponteiro para percorrer a lista
    NoMochila *proximoNo;           // Ponteiro para o nó seguinte

    while (atual != NULL) // Percorre a lista e libera cada nó
    {
        proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
    *primeiroNo = NULL; // Define o ponteiro do primeiro nó como NULL após liberar a lista
}

// Função para exibir o menu principal
void menu(ItemMochila *itens, NoMochila **primeiroNo, int *quantidadeAtual)
{
    int opcao;
    // Loop do menu principal
    do
    {
        printf("===== Escolha entre Vetor ou Lista Encadeada =====\n");
        printf("1. Usar Vetor\n");
        printf("2. Usar Lista Encadeada\n");
        printf("0. Sair\n");
        printf("==========================================\n");

        printf("Digite sua opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada inválida.\n");
            limparBufferDeEntrada();
            continue;
        }
        limparBufferDeEntrada();
        printf("\n");

        switch (opcao)
        {
        case 1:
            menuVetor(itens, quantidadeAtual);
            break;
        case 2:
            menuListaEncadeada(primeiroNo, quantidadeAtual);
            break;
        case 0:
            liberarListaEncadeada(primeiroNo);
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

// Função para exibir o menu do vetor
void menuVetor(ItemMochila *itens, int *quantidadeAtual)
{
    int opcao;

    do // Loop do menu do vetor
    {
        printf("===== Menu Vetor =====\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Exibir Mochila\n");
        printf("4. Buscar Item (Busca Sequencial)\n");
        printf("5. Buscar Item (Busca Binaria)\n");
        printf("0. Voltar ao Menu Anterior\n");
        printf("======================\n");

        printf("Digite sua opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada inválida.\n");
            limparBufferDeEntrada();
            continue;
        }
        limparBufferDeEntrada();
        printf("\n");

        switch (opcao)
        {
        case 1:
            adicionarItemVetor(itens, quantidadeAtual);
            exibirMochilaVetor(itens, *quantidadeAtual);
            break;
        case 2:
            removerItemVetor(itens, quantidadeAtual);
            exibirMochilaVetor(itens, *quantidadeAtual);
            break;
        case 3:
            exibirMochilaVetor(itens, *quantidadeAtual);
            break;
        case 4:
            buscaSequencialItemVetor(itens, *quantidadeAtual);
            break;
        case 5:
            ordenacaoDoVetor(itens, *quantidadeAtual); // Ordenando antes da busca binária
            buscaBinariaItemVetor(itens, *quantidadeAtual);
            break;
        case 0:
            printf("Voltando ao menu anterior.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para exibir o menu da lista encadeada
void menuListaEncadeada(NoMochila **primeiroNo, int *quantidadeAtual)
{
    int opcao;

    do // Loop do menu da lista encadeada
    {
        printf("===== Menu Lista Encadeada =====\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Exibir Mochila\n");
        printf("4. Buscar Item\n");
        printf("0. Voltar ao Menu Anterior\n");
        printf("=============================\n");

        printf("Digite sua opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada inválida.\n");
            limparBufferDeEntrada();
            continue;
        }
        limparBufferDeEntrada();
        printf("\n");

        switch (opcao)
        {
        case 1:
            adicionarItemListaEncadeada(primeiroNo, quantidadeAtual);
            break;
        case 2:
            removerItemListaEncadeada(primeiroNo, quantidadeAtual);
            break;
        case 3:
            exibirListaEncadeada(*primeiroNo);
            break;
        case 4:
            buscarItemListaEncadeada(*primeiroNo);
            break;
        case 0:
            printf("Voltando ao menu anterior.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}