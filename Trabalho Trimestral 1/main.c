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

void imprime_menu()
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

int main(int argc, char const *argv[])
{
    int opcao = 1;
    char lixo;
    Arvore* arv = cria_arvore();
    while (opcao != 0)
    {
        imprime_menu();
        scanf("%d%c", &opcao, &lixo);

        switch (opcao)
        {
            case 1 :
            consulta_paciente(arv);
            break;
        
            case 2 :
            // codigo
            break;

            case 3 :
            insere_consulta(arv);
            break;

            case 4 :
            // codigo
            break;

            case 0 :
            return SUCESSO;
            break;

            default:
            printf("Insira uma opcao valida!!\n\n");
            break;
        }
        // APERTAR UMA TECLA PARA VOLTAR AO MENU.
        system("pause");
        // LIMPANDO O TERMINAL.
        system("cls");
    }
}
