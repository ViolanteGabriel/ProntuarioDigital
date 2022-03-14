#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCESSO         (0)
#define ERRO            (1)

int verifica_data(int dia, int mes, int ano)
{
    if (ano > 1900)
    {
        if (mes >= 1 && mes <= 12)
        {
            if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
            {
                if (dia >= 1 && dia <= 31)
                {
                    return SUCESSO;
                }
                else
                {
                    printf("Voce inseriu uma data invalida.\n");
                    return ERRO;
                }
            }
            
            else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                if (dia >= 1 && dia <= 30)
                {
                    return SUCESSO;
                }
                else
                {
                    printf("Voce inseriu uma data invalida.\n");
                    return ERRO;
                }
                
            }
            
            else if (mes == 2)
            {
                if (dia >= 1 && dia <= 28)
                {
                    return SUCESSO;
                }
                else
                {
                    return ERRO;
                }
                
            }
            
            else
            {
                printf("Voce inseriu uma data invalida.\n");
                return ERRO;
            }
        }
        else
        {
            printf("Voce inseriu uma data invalida.\n");
            return ERRO;
        }
    }
    else
    {
        printf("Voce inseriu uma data invalida.\n");
        return ERRO;
    }
}


// FUNCOES RELACIONADAS A LISTAS
Lista* cria_lista()
{
    Lista* lista =(Lista*)malloc(sizeof(Lista));
    *lista = NULL;
    return lista;
}

int adiciona_consulta_prontuario(Lista* lista, Consulta informacoes)
{
    if (lista == NULL)
    {
        return ERRO;
    }
    elemento *elem = malloc(sizeof(elemento));

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
Arvore* cria_arvore()
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

    prontuario->dados.historico_consultas = cria_lista();
    strcpy(prontuario->dados.nome_paciente, nome);

    adiciona_consulta_prontuario(prontuario->dados.historico_consultas, informacoes);
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
    No* atual = *arv;

    printf("Insira a data para procurarmos uma consulta na data e achar a qual paciente ela pertence: dd/mm/aaaa\n");
    scanf("%d/%d/%d", &(data.dia), &(data.mes), &(data.ano));
    return SUCESSO;
}

int insere_consulta(Arvore* arv)
{
    Consulta informacoes;
    char nome[99 + 1];
    char lixo;

    printf("\n \n");
    printf("Insira a Data da consulta no formato: dd/mm/aaaa\n");
    scanf("%d/%d/%d%c", &(informacoes.data.dia), &(informacoes.data.mes), &(informacoes.data.ano), &lixo);

    // inserir o verifica data.

    printf("Insira uma observacao em relacao a consulta do paciente:\n");
    fgets(informacoes.observacao, 1000, stdin);
    printf("Insira o nome do paciente.\n");
    fgets(nome, 100, stdin);

    No* atual = *arv;
    No* pai = NULL;

    while (atual != NULL)
    {
        pai = atual;

        if (strcmp(atual->dados.nome_paciente, nome) == 0)
        {
            adiciona_consulta_prontuario(atual->dados.historico_consultas, informacoes);
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



