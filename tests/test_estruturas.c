#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Continua verificando em Release, mesmo quando NDEBUG esta definido. */
#define CHECK(condicao) do { \
    if (!(condicao)) { \
        fprintf(stderr, "%s:%d: falhou: %s\n", __FILE__, __LINE__, #condicao); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

static Consulta consulta_exemplo(void)
{
    Consulta consulta = {{15, 6, 2024}, "Consulta de rotina"};
    return consulta;
}

static void data_mes_31_dias(void)
{
    const int meses[] = {1, 3, 5, 7, 8, 10, 12};
    for (size_t i = 0; i < sizeof(meses) / sizeof(meses[0]); ++i)
    {
        CHECK(verifica_data(1, meses[i], 2023) == 0);
        CHECK(verifica_data(31, meses[i], 2023) == 0);
        CHECK(verifica_data(32, meses[i], 2023) == 1);
    }
}

static void data_mes_30_dias(void)
{
    const int meses[] = {4, 6, 9, 11};
    for (size_t i = 0; i < sizeof(meses) / sizeof(meses[0]); ++i)
    {
        CHECK(verifica_data(30, meses[i], 2023) == 0);
        CHECK(verifica_data(31, meses[i], 2023) == 1);
    }
}

static void data_fevereiro(void)
{
    CHECK(verifica_data(28, 2, 2023) == 0);
    CHECK(verifica_data(29, 2, 2023) == 1);
    CHECK(verifica_data(30, 2, 2023) == 1);
}

static void data_bissexto(void)
{
    CHECK(verifica_data(29, 2, 2024) == 0);
    CHECK(verifica_data(30, 2, 2024) == 1);
}

static void data_seculo(void)
{
    CHECK(verifica_data(29, 2, 2000) == 0);
    CHECK(verifica_data(29, 2, 2100) == 1);
}

static void data_dia_invalido(void)
{
    for (int mes = 1; mes <= 12; ++mes)
    {
        CHECK(verifica_data(0, mes, 2024) == 1);
        CHECK(verifica_data(-1, mes, 2024) == 1);
        CHECK(verifica_data(32, mes, 2024) == 1);
    }
}

static void data_mes_invalido(void)
{
    CHECK(verifica_data(1, 0, 2024) == 1);
    CHECK(verifica_data(1, -1, 2024) == 1);
    CHECK(verifica_data(1, 13, 2024) == 1);
}

static void data_ano_invalido(void)
{
    /* Preserva a regra do trabalho original: ano maior que 1900. */
    CHECK(verifica_data(1, 1, 1900) == 1);
    CHECK(verifica_data(1, 1, 1899) == 1);
    CHECK(verifica_data(1, 1, 0) == 1);
    CHECK(verifica_data(1, 1, 1901) == 0);
}

static void lista_vazia(void)
{
    Lista* lista = cria_lista();
    CHECK(lista != NULL);
    CHECK(*lista == NULL);
    libera_lista(lista);
}

static void confere_consulta(const Consulta* obtida, const Consulta* esperada)
{
    CHECK(obtida->data.dia == esperada->data.dia);
    CHECK(obtida->data.mes == esperada->data.mes);
    CHECK(obtida->data.ano == esperada->data.ano);
    CHECK(strcmp(obtida->observacao, esperada->observacao) == 0);
}

static void lista_primeira_consulta(void)
{
    Lista* lista = cria_lista();
    Consulta consulta = consulta_exemplo();
    CHECK(lista != NULL);
    CHECK(adiciona_consulta_prontuario(lista, consulta) == 0);
    CHECK(*lista != NULL);
    confere_consulta(&(*lista)->consulta, &consulta);
    CHECK((*lista)->proximo == NULL);
    libera_lista(lista);
}

static void lista_varias_consultas(void)
{
    Lista* lista = cria_lista();
    Consulta consultas[] = {
        {{20, 6, 2024}, "Primeira consulta inserida"},
        {{10, 6, 2024}, "Segunda consulta inserida"},
        {{25, 6, 2024}, "Terceira consulta inserida"}
    };
    CHECK(lista != NULL);
    for (size_t i = 0; i < 3; ++i)
    {
        CHECK(adiciona_consulta_prontuario(lista, consultas[i]) == 0);
    }
    elemento* atual = *lista;
    for (size_t i = 0; i < 3; ++i)
    {
        CHECK(atual != NULL);
        confere_consulta(&atual->consulta, &consultas[i]);
        atual = atual->proximo;
    }
    CHECK(atual == NULL);
    libera_lista(lista);
}

static void lista_nula(void)
{
    CHECK(adiciona_consulta_prontuario(NULL, consulta_exemplo()) == 1);
}

static void lista_copia_consulta(void)
{
    Lista* lista = cria_lista();
    Consulta consulta = consulta_exemplo();
    Consulta original = consulta;
    CHECK(lista != NULL);
    CHECK(adiciona_consulta_prontuario(lista, consulta) == 0);
    CHECK(*lista != NULL);
    consulta.data.dia = 1;
    strcpy(consulta.observacao, "Alterada");
    confere_consulta(&(*lista)->consulta, &original);
    libera_lista(lista);
}

static void arvore_vazia(void)
{
    Arvore* arv = cria_arvore();
    CHECK(arv != NULL);
    CHECK(*arv == NULL);
    CHECK(consulta_paciente(arv) == 1);
    CHECK(consulta_paciente(NULL) == 1);
    libera_arvore(arv);
}

static void no_com_consulta(void)
{
    Consulta consulta = consulta_exemplo();
    char nome[] = "Maria Silva";
    Arvore* arv = cria_arvore();
    CHECK(arv != NULL);
    *arv = cria_no(nome, consulta);
    CHECK(*arv != NULL);
    nome[0] = 'X';
    CHECK(strcmp((*arv)->dados.nome_paciente, "Maria Silva") == 0);
    CHECK((*arv)->esquerda == NULL);
    CHECK((*arv)->direita == NULL);
    CHECK((*arv)->dados.historico_consultas != NULL);
    Lista historico = *(*arv)->dados.historico_consultas;
    CHECK(historico != NULL);
    confere_consulta(&historico->consulta, &consulta);
    CHECK(historico->proximo == NULL);
    libera_arvore(arv);
}

static void libera_estruturas(void)
{
    Arvore* arv = cria_arvore();
    Consulta consulta = consulta_exemplo();
    CHECK(arv != NULL);
    *arv = cria_no("Maria", consulta);
    CHECK(*arv != NULL);
    (*arv)->esquerda = cria_no("Ana", consulta);
    (*arv)->direita = cria_no("Zelia", consulta);
    CHECK((*arv)->esquerda != NULL);
    CHECK((*arv)->direita != NULL);
    CHECK(adiciona_consulta_prontuario((*arv)->dados.historico_consultas, consulta) == 0);
    libera_arvore(arv);
    libera_lista(NULL);
    libera_arvore(NULL);
}

typedef struct Caso
{
    const char* nome;
    void (*executa)(void);
} Caso;

#define CASO(nome) {#nome, nome}

int main(int argc, char* argv[])
{
    const Caso casos[] = {
        CASO(data_mes_31_dias), CASO(data_mes_30_dias), CASO(data_fevereiro),
        CASO(data_bissexto), CASO(data_seculo), CASO(data_dia_invalido),
        CASO(data_mes_invalido), CASO(data_ano_invalido), CASO(lista_vazia),
        CASO(lista_primeira_consulta), CASO(lista_varias_consultas),
        CASO(lista_nula), CASO(lista_copia_consulta), CASO(arvore_vazia),
        CASO(no_com_consulta), CASO(libera_estruturas)
    };
    if (argc != 2)
    {
        fprintf(stderr, "Uso: test_estruturas <nome_do_teste>\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < sizeof(casos) / sizeof(casos[0]); ++i)
    {
        if (strcmp(argv[1], casos[i].nome) == 0)
        {
            casos[i].executa();
            printf("PASSOU: %s\n", casos[i].nome);
            return EXIT_SUCCESS;
        }
    }
    fprintf(stderr, "Teste desconhecido: %s\n", argv[1]);
    return EXIT_FAILURE;
}
