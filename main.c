#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// criando estruturas
struct sCliente {
    char codigoCliente[20];
    char nome[50];
    char endereco[50];
    char telefone[14];

};
struct sLocacao {
    int codigoLocacao;
    int dataRet;
    int dataDev;
    int seguro;
    int quantD;
    int codCliente;
    int codVeiculo;
};
struct sVeiculo {
    int codigoVeiculo;
    char descricao[60];
    char modelo[20];
    char cor[15];
    char placa[8];
    float valDiaria;
    int quantOcupantes;
    char status[15];
};

// declarando tipos para variaveis
typedef struct sCliente tCliente;
typedef struct sLocacao tLocacao;
typedef struct sVeiculo tVeiculo;


// types variaveis

tCliente c[200];
tLocacao l[2000];
tVeiculo v[200];

int main()
{
    int opcao = 0;
    strcpy( c[1].codigoCliente, "EOF");
    scanf("%d", &opcao);
    while(opcao !=9){
    IncluirC();
        scanf("%d", &opcao);
    }
    salvaDadosDoArquivoC();
    return 0;
}

void salvaDadosDoArquivoC()
{
    printf("\n-- Salvando Cliente -------\n");
    FILE *arquivo;
    int i = 1 ;
    arquivo = fopen("Cliente.txt","w");
    if (arquivo != NULL)
    {
        while (strcmp("EOF",c[i].codigoCliente) != 0)
        {
            fprintf(arquivo,"inicio contato \n");
            fprintf(arquivo,"--Nome %s\n",c[i].nome);
            fprintf(arquivo,"--Codigo %s\n",c[i].codigoCliente);
            fprintf(arquivo,"--Endereco %s\n",c[i].endereco);
            fprintf(arquivo,"--Telefone %s\n",c[i].telefone);
            fprintf(arquivo,"fim contato \n");
            i = i + 1;
        }
        fclose(arquivo);
    }
}


void IncluirC()
{
    tCliente cliente;
    int i;
    system("cls");
    printf("\n-- Inclusao de um Cliente -------\n");
    printf("\n\nDigite o codigo cliente: ");
    scanf(" %[^\n]",&cliente.codigoCliente);
    printf("\n\nDigite o nome: ");
    scanf(" %[^\n]",&cliente.nome);
    printf("  endereco:");
    scanf(" %[^\n]",&cliente.endereco);
    printf("  telefone:");
    scanf(" %[^\n]",&cliente.telefone);

    i = proximoIndice();
    c[i] = cliente;
    strcpy( c[i+1].codigoCliente, "EOF");

    printf("\n\nContato %s incluido.",cliente.nome);

}



int proximoIndice()
{
    printf("\n-- Vendo proximo indidice -------\n");
    int i, r;
    r = -1;
    for (i = 1; i<2000; i++)
    {
        if (strcasecmp("EOF",c[i].codigoCliente) == 0)
        {
            r = i;
            i = 2000;

        }
    }
    printf("\n-- Retornando indice -------\n");
    return r;
}


void listarC()
{
    system("cls");
    printf("\n--------- Lista dos amigos ----------\n");
    for (int i=0; i<2000 && strcmp(c[i].codigoCliente,"EOF") != 0; i++)
    {
        printC(c[i]);
    }
}

void printC(tCliente c)
{
    printf("\nAmigo -----------");
    printf("\n  codigo:%s",c.codigoCliente);
    printf("\n  nome:%s",c.nome);
    printf("\n  cel:%s",c.telefone);
    printf("\n  endereco:%s", c);

    printf("\n");
}

