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
    char codigoLocacao[20];
    int dataRet;
    int dataDev;
    int seguro;
    int quantD;
    int codCliente;
    int codVeiculo;
};
struct sVeiculo {
    char codigoVeiculo[20];
    char descricao[60];
    char modelo[20];
    char cor[15];
    char placa[8];
    char valDiaria[56];
    char quantOcupantes[56];
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
    strcpy( v[1].codigoVeiculo, "EOF");
    scanf("%d", &opcao);
    while(opcao !=9){
    IncluirV();
        scanf("%d", &opcao);
    }

    salvaDadosDoArquivoV();
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

    i = proximoIndiceC();
    c[i] = cliente;
    strcpy( c[i+1].codigoCliente, "EOF");

    printf("\n\nContato %s incluido.",cliente.nome);

}



int proximoIndiceC()
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

int proximoIndiceV()
{
    printf("\n-- Vendo proximo indidice -------\n");
    int i, r;
    r = -1
    ;
    for (i = 1; i<2000; i++)
    {
        if (strcasecmp("EOF",v[i].codigoVeiculo) == 0)
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


void salvaDadosDoArquivoV()
{
    printf("\n-- Salvando Veiculo -------\n");
    FILE *arquivo2;
    int i = 1 ;
    arquivo2 = fopen("Veiculo.txt","w");
    if (arquivo2 != NULL)
    printf("\n-- Verificado o arquivo -------\n");
    {
        while (strcmp("EOF",v[i].codigoVeiculo) != 0)
        {
            printf("\n-- Entrando em loop -------\n");
            fprintf(arquivo2,"inicio contato \n");
            fprintf(arquivo2,"--Codigo %s\n",v[i].codigoVeiculo);
            fprintf(arquivo2,"--descricao %s\n",v[i].descricao);
            fprintf(arquivo2,"--cor %s\n",v[i].cor);
            fprintf(arquivo2,"--placa %s\n",v[i].placa);
            fprintf(arquivo2,"--valDiaria %s\n",v[i].valDiaria);
            fprintf(arquivo2,"--quantOcupantes %s\n",v[i].quantOcupantes);
            fprintf(arquivo2,"--status %s\n",v[i].status);
            fprintf(arquivo2,"fim contato \n");
            i = i + 1;
            printf("\n-- ADD registro -------\n");
        }
        fclose(arquivo2);
    }
}


void IncluirV()
{
    tVeiculo veiculo;
    int i;
    system("cls");
    printf("\n-- Inclusao de um Veiculo -------\n");
    printf("\n\nDigite o codigo veiculo: ");
    scanf(" %[^\n]",&veiculo.codigoVeiculo);
    printf("\n\nDigite a descricao: ");
    scanf(" %[^\n]",&veiculo.descricao);
    printf("  cor:");
    scanf(" %[^\n]",&veiculo.cor);
    printf("  placa:");
    scanf(" %[^\n]",&veiculo.placa);
    printf("  valDiaria:");
    scanf(" %[^\n]",&veiculo.valDiaria);
    printf("  quantOcupantes:");
    scanf(" %[^\n]",&veiculo.quantOcupantes);
    printf("  status:");
    scanf(" %[^\n]",&veiculo.status);


    i = proximoIndiceV();
    v[i] = veiculo;
    strcpy( v[i+1].codigoVeiculo, "EOF");

    printf("\n\nVeiculo %s concluido.",veiculo.descricao);

}








void menu(){
    printf("--------------------------");
    printf("\n|Bem vindo a LocalizaMais!!  |");
    printf("\n|0) Sair                     |");
    printf("\n|1) Incluir cliente          |");
    printf("\n|2) Incluir veiculo          |");
    printf("\n|3) Cadastrar locacao        |");
    printf("\n--------------------------");
}
