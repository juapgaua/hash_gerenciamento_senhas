#ifndef HASH_SENHAS_H
#define HASH_SENHAS_H

/* Tamanho da tabela de espalhamento */
#define TAMANHO_TABELA 10

/* Tamanho maximo das strings de usuario e senha */
#define TAMANHO_TEXTO 50

/* Estrutura que representa um usuario do sistema */
typedef struct {
    char nomeUsuario[TAMANHO_TEXTO];
    char senha[TAMANHO_TEXTO];
} Usuario;

/* No da lista ligada usada no tratamento de colisoes (encadeamento) */
typedef struct No {
    Usuario dado;        /* Usuario armazenado */
    struct No* prox;     /* Ponteiro para o proximo no */
} No;

/* Estrutura da tabela hash
   Cada posicao do vetor e um ponteiro para o inicio de uma lista ligada */
typedef struct {
    No* tabela[TAMANHO_TABELA];
} TabelaHash;

/* Prototipos das funcoes */

/* Limpa o buffer de entrada apos o uso de scanf */
void limparBufferEntrada(void);

/* Inicializa a tabela hash (coloca todos os ponteiros como NULL) */
void inicializarTabela(TabelaHash* th);

/* Funcao de hash que calcula o indice a partir do nome de usuario */
int calcularHash(const char* chave);

/* Insere ou atualiza um usuario na tabela */
void inserirUsuario(TabelaHash* th, const char* nomeUsuario, const char* senha);

/* Busca um usuario pelo nome
   Retorna ponteiro para Usuario dentro da tabela, ou NULL se nao existir */
Usuario* buscarUsuario(TabelaHash* th, const char* nomeUsuario);

/* Lista todos os usuarios da tabela (mostrando colisoes) */
void listarTabela(const TabelaHash* th);

/* Funcao principal do programa (menu interativo) */
void executarPrograma(void);

#endif
