#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_senhas.h"

/* ----------------------------------------------------
   Funcao auxiliar para limpar o buffer de entrada
   Util para evitar problemas com scanf e fgets
   ---------------------------------------------------- */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta caracteres restantes */
    }
}

/* ----------------------------------------------------
   Inicializa a tabela hash, colocando todos os ponteiros
   de lista como NULL (ou seja, tabelas vazias)
   ---------------------------------------------------- */
void inicializarTabela(TabelaHash* th) {
    int i;
    for (i = 0; i < TAMANHO_TABELA; i++) {
        th->tabela[i] = NULL;
    }
}

/* ----------------------------------------------------
   Funcao de hash simples:
   - Soma os valores ASCII dos caracteres da chave
   - Aplica modulo pelo tamanho da tabela
   ---------------------------------------------------- */
int calcularHash(const char* chave) {
    int soma = 0;
    int i;

    for (i = 0; chave[i] != '\0'; i++) {
        soma += (unsigned char)chave[i];
    }

    /* Garante que o resultado fique no intervalo 0..TAMANHO_TABELA-1 */
    return soma % TAMANHO_TABELA;
}

/* ----------------------------------------------------
   Cria um novo no de lista encadeada para armazenar
   um usuario (aloca memoria dinamicamente)
   ---------------------------------------------------- */
static No* criarNo(const char* nomeUsuario, const char* senha) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de memoria ao criar novo usuario.\n");
        return NULL;
    }

    /* Copia os dados do usuario para a estrutura */
    strncpy(novo->dado.nomeUsuario, nomeUsuario, TAMANHO_TEXTO - 1);
    novo->dado.nomeUsuario[TAMANHO_TEXTO - 1] = '\0';

    strncpy(novo->dado.senha, senha, TAMANHO_TEXTO - 1);
    novo->dado.senha[TAMANHO_TEXTO - 1] = '\0';

    novo->prox = NULL;

    return novo;
}

/* ----------------------------------------------------
   Insere um usuario na tabela:
   - Calcula o indice pelo hash do nome de usuario
   - Verifica se o usuario ja existe na lista do indice
     - se existir, atualiza a senha
     - senao, insere um novo no no inicio da lista
   ---------------------------------------------------- */
void inserirUsuario(TabelaHash* th, const char* nomeUsuario, const char* senha) {
    int indice = calcularHash(nomeUsuario);
    No* atual = th->tabela[indice];

    /* Verifica se o usuario ja existe nesta lista (colisao) */
    while (atual != NULL) {
        if (strcmp(atual->dado.nomeUsuario, nomeUsuario) == 0) {
            /* Usuario encontrado: atualiza a senha */
            strncpy(atual->dado.senha, senha, TAMANHO_TEXTO - 1);
            atual->dado.senha[TAMANHO_TEXTO - 1] = '\0';
            printf("Senha do usuario '%s' atualizada com sucesso.\n", nomeUsuario);
            return;
        }
        atual = atual->prox;
    }

    /* Nao encontrou o usuario: cria um novo no e insere no inicio da lista */
    No* novo = criarNo(nomeUsuario, senha);
    if (novo == NULL) {
        return; /* erro de memoria ja informado em criarNo */
    }

    novo->prox = th->tabela[indice];
    th->tabela[indice] = novo;

    printf("Usuario '%s' cadastrado com sucesso na posicao %d.\n", nomeUsuario, indice);
}

/* ----------------------------------------------------
   Busca um usuario pelo nome:
   - Calcula o indice usando a funcao de hash
   - Percorre a lista daquela posicao
   - Se encontrar, retorna ponteiro para o Usuario
   - Se nao encontrar, retorna NULL
   ---------------------------------------------------- */
Usuario* buscarUsuario(TabelaHash* th, const char* nomeUsuario) {
    int indice = calcularHash(nomeUsuario);
    No* atual = th->tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->dado.nomeUsuario, nomeUsuario) == 0) {
            return &(atual->dado);
        }
        atual = atual->prox;
    }

    return NULL;
}

/* ----------------------------------------------------
   Lista todos os usuarios da tabela, mostrando o indice
   (assim conseguimos visualizar onde ha colisoes)
   ---------------------------------------------------- */
void listarTabela(const TabelaHash* th) {
    int i;
    printf("\n===== LISTA COMPLETA DE USUARIOS NA TABELA HASH =====\n");

    for (i = 0; i < TAMANHO_TABELA; i++) {
        printf("Indice %d: ", i);

        if (th->tabela[i] == NULL) {
            printf("(vazio)\n");
        } else {
            No* atual = th->tabela[i];
            while (atual != NULL) {
                printf("[usuario: %s | senha: %s] -> ",
                       atual->dado.nomeUsuario,
                       atual->dado.senha);
                atual = atual->prox;
            }
            printf("NULL\n");
        }
    }

    printf("=====================================================\n");
}

/* ----------------------------------------------------
   Funcao principal da aplicacao:
   - Cria e inicializa a tabela hash
   - Apresenta menu para o usuario
   - Permite inserir, buscar e listar usuarios
   ---------------------------------------------------- */
void executarPrograma(void) {
    TabelaHash tabela;
    int opcao;
    char nomeUsuario[TAMANHO_TEXTO];
    char senha[TAMANHO_TEXTO];
    Usuario* usuarioEncontrado = NULL;

    inicializarTabela(&tabela);

    do {
        printf("\n========== GERENCIADOR DE SENHAS (HASH TABLE) ==========\n");
        printf("1 - Cadastrar ou atualizar usuario\n");
        printf("2 - Buscar usuario por nome\n");
        printf("3 - Listar todos os usuarios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }

        limparBufferEntrada(); /* Remove o '\n' deixado pelo scanf */

        switch (opcao) {
            case 1:
                printf("Digite o nome de usuario (sem espacos): ");
                if (scanf("%49s", nomeUsuario) != 1) {
                    printf("Erro ao ler nome de usuario.\n");
                    limparBufferEntrada();
                    break;
                }

                printf("Digite a senha (sem espacos): ");
                if (scanf("%49s", senha) != 1) {
                    printf("Erro ao ler senha.\n");
                    limparBufferEntrada();
                    break;
                }

                limparBufferEntrada();

                inserirUsuario(&tabela, nomeUsuario, senha);
                break;

            case 2:
                printf("Digite o nome de usuario para busca: ");
                if (scanf("%49s", nomeUsuario) != 1) {
                    printf("Erro ao ler nome de usuario.\n");
                    limparBufferEntrada();
                    break;
                }
                limparBufferEntrada();

                usuarioEncontrado = buscarUsuario(&tabela, nomeUsuario);
                if (usuarioEncontrado != NULL) {
                    printf("Usuario encontrado!\n");
                    printf("Nome: %s | Senha: %s\n",
                           usuarioEncontrado->nomeUsuario,
                           usuarioEncontrado->senha);
                } else {
                    printf("Usuario '%s' nao encontrado na tabela.\n", nomeUsuario);
                }
                break;

            case 3:
                listarTabela(&tabela);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    /* Opcional: liberar memoria alocada antes de sair */
    int i;
    for (i = 0; i < TAMANHO_TABELA; i++) {
        No* atual = tabela.tabela[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}
