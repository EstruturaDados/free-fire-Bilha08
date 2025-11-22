#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// ========================================================
// 1. DEFINES
// ========================================================
#define MAX_COMPONENTES 20
#define TAM_STRING 30

// ========================================================
// 2. STRUCTS E VARIÁVEIS GLOBAIS (SE NECESSÁRIO)
// ========================================================
typedef struct Componente
{
    char nome[TAM_STRING];
    char tipo[TAM_STRING];
    int prioridade;
} Componente;

// ========================================================
// 3. PROTÓTIPOS DE FUNÇÕES
// ========================================================
void limparBufferDeEntrada();
void adicionarComponente(Componente *componentes, int *totalComponentes);
void listarComponentes(Componente *componentes, int totalComponentes);
void descartarComponente(Componente *componentes, int *totalComponentes);

typedef void (*FuncaoOrdenacao)(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome); // FuncaoOrdenacao é um ponteiro para funcao

double medirTempo(FuncaoOrdenacao funcao, Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome, const char *nomeMetodo);

void organizarPorNome(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome);
void organizarPorTipo(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome);
void organizarPorPrioridade(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome);

int buscaBinariaPorNome(Componente *componentes, int total, char *nomeBuscado, int *comparacoes);

void menuOrganizarMochila(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome);
void menuPrincipal(Componente *componentes, int *totalComponentes, bool *mochilaOrganizadaNome);

// ========================================================
// 4. FUNÇÃO MAIN
// ========================================================
int main()
{
    int totalComponentes = 0;
    bool mochilaOrganizadaNome = false;
    Componente componentes[MAX_COMPONENTES];

    menuPrincipal(componentes, &totalComponentes, &mochilaOrganizadaNome);
    return 0;
}

// ========================================================
// 5. IMPLEMENTAÇÃO DAS FUNÇÕES
// ========================================================

// --------------------------------------------------------
// Função para limpar buffer do teclado
// --------------------------------------------------------
void limparBufferDeEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// --------------------------------------------------------
// Adicionar novo componente
// --------------------------------------------------------
void adicionarComponente(Componente *componentes, int *totalComponentes)
{
    if (*totalComponentes >= MAX_COMPONENTES)
    {
        printf("\nMochila cheia! Não é possível adicionar mais componentes.\n");
        return;
    }

    printf("\n--- Adicionar Novo Componente ---\n");
    printf("Nome: ");
    fgets(componentes[*totalComponentes].nome, TAM_STRING, stdin);
    componentes[*totalComponentes].nome[strcspn(componentes[*totalComponentes].nome, "\n")] = 0;

    printf("Tipo (Estrutural, Eletrônico, Energia): ");
    fgets(componentes[*totalComponentes].tipo, TAM_STRING, stdin);
    componentes[*totalComponentes].tipo[strcspn(componentes[*totalComponentes].tipo, "\n")] = 0;

    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &componentes[*totalComponentes].prioridade);
    limparBufferDeEntrada();

    (*totalComponentes)++;
}

// --------------------------------------------------------
// Listar componentes
// --------------------------------------------------------
void listarComponentes(Componente *componentes, int totalComponentes)
{
    if (totalComponentes == 0)
    {
        printf("\nNenhum componente na mochila.\n");
        return;
    }

    printf("\n--- Componentes na Mochila (%d/%d) ---\n", totalComponentes, MAX_COMPONENTES);
    printf("----------------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("**********************************************************\n");

    for (int i = 0; i < totalComponentes; i++)
    {
        printf("%-20s | %-15s | %-10d\n", componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }

    printf("----------------------------------------------------------\n");
    printf("Pressione Enter para continuar...\n");
    getchar();
}

// --------------------------------------------------------
// Remover um componente
// --------------------------------------------------------
void descartarComponente(Componente *componentes, int *totalComponentes)
{
    if (*totalComponentes == 0)
    {
        printf("\nNenhum componente para descartar.\n");
        return;
    }

    char nomeDescartar[TAM_STRING];
    printf("\nDigite o nome do componente a ser descartado: ");
    fgets(nomeDescartar, TAM_STRING, stdin);
    nomeDescartar[strcspn(nomeDescartar, "\n")] = 0;

    for (int i = 0; i < *totalComponentes; i++)
    {
        if (strcmp(componentes[i].nome, nomeDescartar) == 0)
        {
            componentes[i] = componentes[*totalComponentes - 1];
            (*totalComponentes)--;
            printf("Componente '%s' descartado com sucesso.\n", nomeDescartar);
            return;
        }
    }

    printf("Componente '%s' não encontrado.\n", nomeDescartar);
}

// -------------------------------------------------------------
// Função para medir tempo de execução das funções de ordenação
// -------------------------------------------------------------
double medirTempo(FuncaoOrdenacao funcao, Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome, const char *nomeMetodo)
{
    clock_t inicio = clock(); // Inicia a contagem do tempo
    funcao(componentes, totalComponentes, mochilaOrganizadaNome);
    clock_t fim = clock(); // Finaliza a contagem do tempo

    double tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC; // Calcula o tempo em milissegundos
    printf("Tempo de execução (%s): %.10f ms\n", nomeMetodo, tempo);

    return tempo;
}

// --------------------------------------------------------
// Ordenações (Bubble, Insertion, Selection)
// --------------------------------------------------------
void organizarPorNome(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome) // Bubble
{
    int comparacoes = 0;

    for (int i = 0; i < totalComponentes - 1; i++)
    {
        for (int j = 0; j < totalComponentes - i - 1; j++)
        {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0)
            {
                Componente tmp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = tmp;
            }
        }
    }

    *mochilaOrganizadaNome = true; // marca a mochila como organizada por nome
    printf("\nMochila organizada por NOME. Comparações: %d\n", comparacoes);
}

void organizarPorTipo(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome) // Insertion
{
    int comparacoes = 0;

    for (int i = 1; i < totalComponentes; i++)
    {
        Componente aux = componentes[i];
        int j = i - 1;

        while (j >= 0)
        {
            comparacoes++;
            if (strcmp(componentes[j].tipo, aux.tipo) > 0)
            {
                componentes[j + 1] = componentes[j];
                j--;
            }
            else
                break;
        }
        componentes[j + 1] = aux;
    }

    *mochilaOrganizadaNome = false;
    printf("\nMochila organizada por TIPO. Comparações: %d\n", comparacoes);
}

void organizarPorPrioridade(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome) // Selection
{
    int comparacoes = 0;

    for (int i = 0; i < totalComponentes - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < totalComponentes; j++)
        {
            comparacoes++;
            if (componentes[j].prioridade > componentes[maxIndex].prioridade)
                maxIndex = j;
        }

        Componente t = componentes[i];
        componentes[i] = componentes[maxIndex];
        componentes[maxIndex] = t;
    }

    *mochilaOrganizadaNome = false;
    printf("\nMochila organizada por PRIORIDADE. Comparações: %d\n", comparacoes);
}

// --------------------------------------------------------
// Busca binária por nome
// --------------------------------------------------------
int buscaBinariaPorNome(Componente *componentes, int total, char *nomeBuscado, int *comparacoes)
{
    int inicio = 0, fim = total - 1;
    *comparacoes = 0;

    while (inicio <= fim)
    {
        (*comparacoes)++;

        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nomeBuscado, componentes[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

// --------------------------------------------------------
// Menu de organização
// --------------------------------------------------------
void menuOrganizarMochila(Componente *componentes, int totalComponentes, bool *mochilaOrganizadaNome)
{
    int opcao;

    printf("\n--- Organizar Mochila ---\n");
    printf("1. Organizar por Nome (Ordem Alfabética) (Bubble Sort)\n");
    printf("2. Organizar por Tipo (Insertion Sort)\n");
    printf("3. Organizar por Prioridade (Selection Sort)\n");
    printf("0. Voltar ao menu principal\n");

    printf("Escolha uma opcao: ");
    int r = scanf("%d", &opcao);
    limparBufferDeEntrada();
    if (r != 1)
    {
        opcao = -1;
    }

    switch (opcao)
    {
    case 1:
        medirTempo(organizarPorNome, componentes, totalComponentes, mochilaOrganizadaNome, "Bubble Sort");
        listarComponentes(componentes, totalComponentes);
        break;
    case 2:
        medirTempo(organizarPorTipo, componentes, totalComponentes, mochilaOrganizadaNome, "Insertion Sort");
        listarComponentes(componentes, totalComponentes);
        break;
    case 3:
        medirTempo(organizarPorPrioridade, componentes, totalComponentes, mochilaOrganizadaNome, "Selection Sort");
        listarComponentes(componentes, totalComponentes);
        break;
    case 0:
        printf("Voltando ao menu principal.\n");
        break;
    default:
        printf("Opcao invalida. Voltando ao menu principal.\n");
    }
}
// --------------------------------------------------------
// Menu principal
// --------------------------------------------------------
void menuPrincipal(Componente *componentes, int *totalComponentes, bool *mochilaOrganizadaNome)
{
    int opcao;

    do
    {
        printf("\n================ TORRE DE RESGATE ================\n");
        printf("Itens na mochila: %d/%d\n", *totalComponentes, MAX_COMPONENTES);
        printf("Status ordenação por nome: %s\n", *mochilaOrganizadaNome ? "ORDENADA" : "NÃO ORDENADA");
        printf("===============================================\n\n");

        printf("===== Menu Principal =====\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila\n");
        printf("5. Busca Binária por Componente-Chave (Por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("==========================\n");

        printf("Escolha uma opção: ");
        int r = scanf("%d", &opcao);
        limparBufferDeEntrada();
        if (r != 1)
            opcao = -1;

        switch (opcao)
        {
        case 1:
            adicionarComponente(componentes, totalComponentes);
            listarComponentes(componentes, *totalComponentes);
            break;
        case 2:
            descartarComponente(componentes, totalComponentes);
            listarComponentes(componentes, *totalComponentes);
            break;
        case 3:
            listarComponentes(componentes, *totalComponentes);
            break;
        case 4:
            menuOrganizarMochila(componentes, *totalComponentes, mochilaOrganizadaNome);
            break;
        case 5:
        {
            if (!*mochilaOrganizadaNome)
            {
                printf("\nOrdene por nome antes de usar busca binária!\n");
                break;
            }

            char busca[TAM_STRING];
            printf("Digite o nome a buscar: ");
            fgets(busca, TAM_STRING, stdin);
            busca[strcspn(busca, "\n")] = 0;

            int comparacoes;
            int pos = buscaBinariaPorNome(componentes, *totalComponentes, busca, &comparacoes);

            if (pos >= 0)
            {
                printf("\nEncontrado!\nNome: %s | Tipo: %s | Prioridade: %d\n", componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
            }
            else
            {
                printf("\nNão encontrado.\n");
            }

            printf("Comparações realizadas: %d\n", comparacoes);
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}