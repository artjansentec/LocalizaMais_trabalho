#include <stdio.h>
#include <stdlib.h>

// criando estruturas
struct sCliente {
    int codigo;
    char nome[50];
    char endereco[50];
    int telefone;

};
struct sLocacao {
    int codigo;
    int dataRet;
    int dataDev;
    int seguro;
    int quantD;
    int codCliente;
    int codVeiculo;
};
struct sVeiculo {
    int codigo;
    char descricao[60];
    char modelo[20];
    char cor[15];
    char [8];
    int valDiaria;
    int quantOcupantes;
    char status[15];
};

// declarando tipos para variaveis
typedef sCliente tCliente;
typedef sLocacao tLocacao;
typedef sVeiculo tVeiculo;


// types variaveis

tCliente c[200];
tLocacao l[2000];
tVeiculo v[200];

int main()
{


    // declarando variaveis para leitura de arquivo
    FILE *pArqVeiculo;

    FILE *pArqLocacao;
    printf("Bem vindo ao sistema da LocaMais!");

    //criando cliente




    return 0;
}

void salvaDadosDoArquivoC(c)
{
    FILE *pArqCliente;
    int i = 0 ;
    arquivo = fopen("Cliete.txt","w");
    if (arquivo != NULL)
    {
        while (strcmp("EOF",c[i].nome) != 0)
        {
            fprintf(arquivo,"inicio contato \n");
            fprintf(arquivo,"--Nome %s\n",c[i].nome);
            fprintf(arquivo,"--Codigo %s\n",c[i].codigo);
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
    tCliente c;
    int i;
    system("cls");
    printf("\n-- Inclusao de um Cliente -------\n");
    printf("\n\nDigite o nome: ");
    scanf(" %[^\n]",&c.nome);
    printf("  endereco:");
    scanf(" %[^\n]",&c.endereco);
    printf("  telefone:");
    scanf(" %[^\n]",&c.telefone);


    i = proximoIndice();
    c[i] = c;
    strcpy( c[i+1].nome, "EOF");
    printf("\n\Cliente %s incluido.",p.nome);


    // salvando dados
    salvaDadosDoArquivoC(c)
}
