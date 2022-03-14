#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Estrutura que armazena dia mes e ano.
typedef struct Data
{
    int dia;
    int mes;
    int ano;
} Data;

// Estrutura que armazena uma observacao e uma data.
typedef struct Consulta
{
    Data data;
    char observacao[999 + 1];
} Consulta;

// Elemento que armazena uma consulta e o endereço do proximo elemento da lista.
typedef struct elemento
{
    Consulta consulta;
    struct elemento *proximo;
} elemento;
typedef elemento* Lista;

// Estrutura que armazena um nome e uma lista de consultas.
typedef struct prontuario
{
    char nome_paciente[99 + 1];
    Lista* historico_consultas;
} prontuario;

// No de uma arvore que armazena os dados de um prontuario e o enderço de seus filhos.
typedef struct No
{
    prontuario dados;
    struct No* esquerda;
    struct No* direita;
} No;
typedef No* Arvore;


int verifica_data(int dia, int mes, int ano);

// FUNCOES RELACIONADAS A LISTAS:
Lista* cria_lista();
int adiciona_consulta_prontuario(Lista* lista, Consulta informacoes);
void mostra_lista(Lista* lista);

// FUNCOES RELACIONADAS A ARVORES E:
Arvore* cria_arvore();
No* cria_no(char nome[], Consulta informacoes);

// FUNCOES PRINCIPAIS:
int consulta_paciente(Arvore* arv);
int consulta_data(Arvore* arv);
int insere_consulta(Arvore* arv);

#endif