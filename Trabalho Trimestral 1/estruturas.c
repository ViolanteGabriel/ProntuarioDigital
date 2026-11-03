#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCESSO         (0)
#define ERRO            (1)

int verifica_data(int dia, int mes, int ano)
{
    const int dias_por_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano <= 1900 || mes < 1 || mes > 12)
    {
        return ERRO;
    }

    int limite = dias_por_mes[mes - 1];
    if (mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)))
    {
        limite = 29;
    }
    return dia >= 1 && dia <= limite ? SUCESSO : ERRO;
}


// FUNCOES RELACIONADAS A LISTAS
Lista* cria_lista(void)
{
    Lista* lista =(Lista*)malloc(sizeof(Lista));
    if (lista != NULL)
    {
        *lista = NULL;
    }
    return lista;
}

int adiciona_consulta_prontuario(Lista* lista, Consulta informacoes)
{
    if (lista == NULL)
    {
        return ERRO;
    }
    elemento *elem = malloc(sizeof(elemento));
    if (elem == NULL)
    {
        return ERRO;
    }
    elem->proximo = NULL;

    elem->consulta.data = informacoes.data;
    strcpy(elem->consulta.observacao, informacoes.observacao);
    

    if (*lista == NULL)
    {
        *lista = elem;
        elem->proximo = NULL;
        return SUCESSO;
    }
    
    elemento* aux = *lista;
    while (aux->proximo != NULL)
    {
        aux = aux->proximo;
    }
    aux->proximo = elem;
    return SUCESSO;
}

void mostra_lista(Lista* lista)
{
    elemento* elem = *lista;

    while (elem != NULL)
    {
        printf("Data da Consulta: [%d/%d/%d] Observacao: %s\n", elem->consulta.data.dia, elem->consulta.data.mes, elem->consulta.data.ano, elem->consulta.observacao);
        elem = elem->proximo;
    }
}

// FUNCOES RELACIONADAS A ARVORES E NOS
Arvore* cria_arvore(void)
{
    Arvore* raiz = malloc(sizeof(Arvore));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
}

No* cria_no(char nome[], Consulta informacoes)
{
    No *prontuario = (No*)malloc(sizeof(No));
    if (prontuario == NULL)
    {
        return NULL;
    }

    prontuario->dados.historico_consultas = cria_lista();
    if (prontuario->dados.historico_consultas == NULL)
    {
        free(prontuario);
        return NULL;
    }
    strcpy(prontuario->dados.nome_paciente, nome);

    if (adiciona_consulta_prontuario(prontuario->dados.historico_consultas, informacoes) != SUCESSO)
    {
        libera_lista(prontuario->dados.historico_consultas);
        free(prontuario);
        return NULL;
    }
    prontuario->esquerda = NULL;
    prontuario->direita = NULL;
    return prontuario;
}

int consulta_paciente(Arvore* arv)
{
    printf("\n\n");

    if (arv == NULL || *arv == NULL)
    {
        printf("Arvore Vazia, nenhum prontuario encontrado.\n");
        return ERRO;
    }

    char nome_procurado[99 + 1];

    printf("Insira o nome do paciente, para que as consultas sejam procuradas: \n");
    fgets(nome_procurado, 100, stdin);

    No* atual = *arv;

    while (atual != NULL)
    {
        if (strcmp(atual->dados.nome_paciente, nome_procurado) == 0)
        {
            mostra_lista(atual->dados.historico_consultas);
            return SUCESSO;
        }
        if (strcmp(atual->dados.nome_paciente, nome_procurado) > 0)
        {
            atual = atual->esquerda;
        }
        else
        {
            atual = atual->direita;
        }

    }
    printf("Paciente nao foi encontrado!!\n");
    return SUCESSO;
}

int consulta_data(Arvore* arv)
{
    printf("\n\n");

    if (arv == NULL || *arv == NULL)
    {
        printf("Arvore Vazia, nenhum prontuario encontrado.\n");
        return ERRO;
    }

    Data data;
    printf("Insira a data para procurarmos uma consulta na data e achar a qual paciente ela pertence: dd/mm/aaaa\n");
    scanf("%d/%d/%d", &(data.dia), &(data.mes), &(data.ano));
    return SUCESSO;
}

int insere_consulta(Arvore* arv)
{
    if (arv == NULL)
    {
        return ERRO;
    }
    Consulta informacoes;
    char nome[99 + 1];
    char lixo;

    printf("\n \n");
    printf("Insira a Data da consulta no formato: dd/mm/aaaa\n");
    if (scanf("%d/%d/%d%c", &(informacoes.data.dia), &(informacoes.data.mes), &(informacoes.data.ano), &lixo) != 4)
    {
        return ERRO;
    }

    if (verifica_data(informacoes.data.dia, informacoes.data.mes, informacoes.data.ano) != SUCESSO)
    {
        printf("Voce inseriu uma data invalida.\n");
        return ERRO;
    }

    printf("Insira uma observacao em relacao a consulta do paciente:\n");
    if (fgets(informacoes.observacao, 1000, stdin) == NULL)
    {
        return ERRO;
    }
    printf("Insira o nome do paciente.\n");
    if (fgets(nome, 100, stdin) == NULL)
    {
        return ERRO;
    }

    No* atual = *arv;
    No* pai = NULL;

    while (atual != NULL)
    {
        pai = atual;

        if (strcmp(atual->dados.nome_paciente, nome) == 0)
        {
            if (adiciona_consulta_prontuario(atual->dados.historico_consultas, informacoes) != SUCESSO)
            {
                return ERRO;
            }
            printf("A consulta do paciente foi adicionada!!!!\n");
            return SUCESSO;
        }

        if (strcmp(atual->dados.nome_paciente, nome) > 0)
        {
            atual = atual->esquerda;
        }
        else
        {
            atual = atual->direita;
        }
            
    }

    No* novo_prontuario = cria_no(nome, informacoes);
    if (novo_prontuario == NULL)
    {
        return ERRO;
    }

    if (*arv == NULL) 
    {
        printf("A consulta do paciente foi adicionada!!!!\n");
        *arv = novo_prontuario;
        return SUCESSO;
    }
    
    if (strcmp(pai->dados.nome_paciente, nome) > 0)
    {
        pai->esquerda = novo_prontuario;
    }
    else
    {
        pai->direita = novo_prontuario;
    }
    printf("A consulta do paciente foi adicionada!!!!\n");
    return SUCESSO;
}

void libera_lista(Lista* lista)
{
    if (lista == NULL)
    {
        return;
    }
    elemento* atual = *lista;
    while (atual != NULL)
    {
        elemento* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

static void libera_no(No* no)
{
    if (no == NULL)
    {
        return;
    }
    libera_no(no->esquerda);
    libera_no(no->direita);
    libera_lista(no->dados.historico_consultas);
    free(no);
}

void libera_arvore(Arvore* arv)
{
    if (arv != NULL)
    {
        libera_no(*arv);
        free(arv);
    }
}
