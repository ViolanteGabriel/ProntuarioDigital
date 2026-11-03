// Trabalho prático 1.
// Nome: Gabriel Machado Violante, Turma 203.
// Data: 14/07/2021

// BIBLIOTECAS E ESTRUTURAS DE DADOS INCLUIDAS.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

// CONSTANTES
#define SUCESSO         (0)
#define ERRO            (1)

void imprime_menu(void)
{
    printf("\n\n---------------------------------\n|              MENU             |\n---------------------------------\n");
    printf("Opcoes:\n");
    printf("(1) Consultar Paciente.\n");
    printf("(2) Consultar Data.\n");
    printf("(3) Inserir Consulta.\n");
    printf("(4) Remover Prontuario.\n");
    printf("(0) Finalizar o programa(sair).\n");
    printf("Insira a opcao desejada(numero): ");
    
}

int main(void)
{
    int opcao = 1;
    char lixo;
    Arvore* arv = cria_arvore();
    if (arv == NULL)
    {
        return ERRO;
    }
    while (opcao != 0)
    {
        imprime_menu();
        if (scanf("%d%c", &opcao, &lixo) != 2)
        {
            libera_arvore(arv);
            return ERRO;
        }

        switch (opcao)
        {
            case 1 :
            consulta_paciente(arv);
            break;
        
            case 2 :
            break;

            case 3 :
            insere_consulta(arv);
            break;

            case 4 :
            break;

            case 0 :
            libera_arvore(arv);
            return SUCESSO;
            break;

            default:
            printf("Insira uma opção valida.\n\n");
            break;
        }
        
    }
    libera_arvore(arv);
    return SUCESSO;
}
