## Gerenciamento de Senhas com Tabela de Espalhamento (Hash Table em C)

Este projeto implementa um sistema de gerenciamento de senhas utilizando uma tabela de espalhamento (hash table) com tratamento de colisões via encadeamento (listas ligadas).  
Desenvolvido como atividade prática da disciplina Algoritmos, Estrutura de Dados e TAD, aplicando boas práticas de modularização com arquivos .h, .c e main.c.  

## Funcionalidades Implementadas

- Cadastro de usuários com nome e senha
- Tratamento de colisões por encadeamento (listas ligadas)
- Busca de usuários pelo nome
- Listagem completa da tabela hash, permitindo visualizar colisões
- Função auxiliar para limpar buffer
- Código modularizado em:
  - hash_senhas.h
  - hash_senhas.c
  - main.c (apenas 1 linha lógica de execução)

## Conceitos de Estrutura de Dados Aplicados

- Tabela de Espalhamento (Hash Table)
- Estrutura que permite armazenamento e busca eficiente, utilizando uma função de hash para calcular o índice no vetor.
- Função de Hash
- Implementação baseada na soma dos valores ASCII dos caracteres e aplicação de módulo pelo tamanho da tabela.

## Tratamento de Colisões

- Quando dois nomes geram o mesmo índice, utiliza-se encadeamento: cada posição da tabela é o início de uma lista ligada.

## Operações Implementadas
- Inserção
- Busca
- Travessia (listagem)  

Todas operam apenas sobre a lista correspondente ao índice calculado.

## Estrutura do Projeto

```cmd
hash-gerenciamento-senhas
│
├── hash_senhas.h       # Definições, structs, protótipos
├── hash_senhas.c       # Implementação da tabela hash
└── main.c              # Apenas executa o programa
```

## Como Compilar e Executar (VSCode / Windows)

Compilação:
```cmd
gcc main.c hash_senhas.c -o hash
```

Execução:
```cmd
hash.exe
```

## Exemplo de Uso

<img width="700" height="145" alt="image" src="https://github.com/user-attachments/assets/a00d3db6-ab8f-48b3-89c1-d197a716ba6f" />   

Cadastre os seguintes usuários:

admin	root123  
user1	123  
user2	abc  
joao	senha1  
maria	senha2  

Depois execute:

- Listar todos os usuários
- Buscar usuários específicos

## Objetivo da Atividade

- Compreender o funcionamento de tabelas de espalhamento
- Implementar uma função de hash eficiente
- Tratar colisões usando encadeamento
- Modularizar corretamente o código
- Simular um sistema real de armazenamento e autenticação

## Autoria e Licença

Desenvolvido por Juliana Apgaua Sant'Ana Vidigal  
Aluna do Curso de Tecnologia de Sistemas para Internet  
Este projeto pode ser utilizado para fins acadêmicos e estudo.  
