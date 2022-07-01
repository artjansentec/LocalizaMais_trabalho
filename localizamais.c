#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// criando estruturas

struct sEndereco
{
    char rua[100];
    char numero[10];
    char complemento[10];
    char bairro[50];
    char cidade[50];
    char estado[3];
    char cep[15];
};
typedef struct sEndereco tEndereco;

struct sCliente
{
    char codigoCliente[20];
    char nomeCliente[50];
    char telefoneCliente[14];
    tEndereco enderecoCliente;
};

struct sVeiculo
{
    char codigoVeiculo[20];
    char descricao[60];
    char modelo[20];
    char cor[15];
    char placa[10];
    float valorDiaria;
    int quantOcupantes;
    char status[15];
};

struct sLocacao
{
    char codigoLocacao[20];
    char dataRetolucaoirada[26];
    char dataDev[26];
    char seguro[25];
    char quantDias[4];
    char codCliente[25];
    char codVeiculo[25];
};

// declarando tipos para variaveis
typedef struct sCliente tCliente;
typedef struct sVeiculo tVeiculo;
typedef struct sLocacao tLocacao;

void menu()
{
    printf("--------------------------");
    printf("\n|Bem vindo a LocalizaMais!!  |");
    printf("\n|0) Sair                     |");
    printf("\n|1) Incluir cliente          |");
    printf("\n|2) Incluir veiculo          |");
    printf("\n|3) Cadastrar locacao        |");
    printf("\n|5) Mostrar informacoes de um cliente |");
    printf("\n|6) Listar todos os clientes |");
}

int main()
{
    system("color 5f");
    FILE *arquivoClientes;
    FILE *arquivoVeiculos;
    int opcao;
    char encontrarCodCliente[20];

    setlocale(LC_ALL, "portuguese");

    if (((arquivoClientes = fopen("Clientes.dat", "r+b")) == NULL) ||
            ((arquivoVeiculos = fopen("Veiculos.dat", "r+b")) == NULL))
    {
        printf("\n--------------------------");
        printf("\n|    Criando o Arquivo   |");
        printf("\n--------------------------\n");
        if (((arquivoClientes = fopen("Clientes.dat", "w+b")) == NULL) ||
                ((arquivoVeiculos = fopen("Veiculos.dat", "w+b")) == NULL))
        {
            printf("\n\n|| ERRO NA CRIAÇÃO DO ARQUIVO!! ||");
            exit(1);
        }
        else
        {
            printf("\n\n Arquivo Criado!! \n");
        }
    }

    system("pause");

    do
    {
        menu();
        printf("\nDigite a funcao que deseja executar: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            break;
        case 1:
            incluirCliente(arquivoClientes);
            break;
        case 2:
            incluirVeiculo(arquivoVeiculos);
            break;
        case 5:
            printf("Digite o codigo do cliente que deseja encontrar: ");
            scanf(" %[^\n]", &encontrarCodCliente);
            encontreCliente(arquivoClientes, encontrarCodCliente);
            break;
        case 6:
            listarClientes(arquivoClientes);
            break;
        }
    }
    while (opcao != 0);

    fclose(arquivoClientes);
    fclose(arquivoVeiculos);

    return 0;
}

void incluirCliente(FILE *arquivoClientes)
{
    tCliente cliente;
    int indice;

    printf("--------------------------\n");
    printf("|   Inclusão de Cliente  |");
    printf("\n--------------------------");

    printf("\nDigite o código do cliente: ");
    scanf(" %[^\n]", &cliente.codigoCliente);

    indice = localizaCliente(arquivoClientes, cliente.codigoCliente);

    if (indice == -1) // não possuia esse codigoCliente no arquivo
    {
        printf("Nome do Cliente: ");
        scanf(" %[^\n]", &cliente.nomeCliente);
        printf("Telefone: ");
        scanf(" %[^\n]", &cliente.telefoneCliente);
        printf("Endereço:\n");
        printf("Rua:");
        scanf(" %[^\n]", &cliente.enderecoCliente.rua);
        printf("Numero:");
        scanf(" %[^\n]", &cliente.enderecoCliente.numero);
        printf("Complemento:");
        scanf(" %[^\n]", &cliente.enderecoCliente.complemento);
        printf("Bairro:");
        scanf(" %[^\n]", &cliente.enderecoCliente.bairro);
        printf("Cidade:");
        scanf(" %[^\n]", &cliente.enderecoCliente.cidade);
        printf("Estado:");
        scanf(" %[^\n]", &cliente.enderecoCliente.estado);
        printf("CEP:");
        scanf(" %[^\n]", &cliente.enderecoCliente.cep);

        fseek(arquivoClientes, 0, SEEK_END);
        fwrite(&cliente, sizeof(cliente), 1, arquivoClientes);
        fflush(arquivoClientes);
    }
    else
    {
        printf("\n----------ERRO----------");
        printf(
            "\n Não é possível cadastrar mais de um cliente com o mesmo código!");
        printf("\n Já existe um cliente com o código %s no arquivo",
               cliente.codigoCliente);
        printf("\n--------------------------");
    }
}

char codigoVeiculo[20];
char descricao[60];
char modelo[20];
char cor[15];
char placa[8];
float valorDiaria[56];
int quantOcupantes[56];
char status[15];

void incluirVeiculo(FILE *arquivoVeiculos)
{
    tVeiculo veiculo;
    int indice;

    printf("--------------------------\n");
    printf("|   Inclusão de Veículo  |");
    printf("\n--------------------------");

    printf("\nDigite o código do veículo: ");
    scanf(" %[^\n]", &veiculo.codigoVeiculo);

    indice = localizaVeiculo(arquivoVeiculos, veiculo.codigoVeiculo);

    if (indice == -1) // não possuia esse codigoVeiculo no arquivo
    {
        printf("Descrição do veículo: ");
        scanf(" %[^\n]", &veiculo.descricao);
        printf("Modelo: ");
        scanf(" %[^\n]", &veiculo.modelo);
        printf("Cor:");
        scanf(" %[^\n]", &veiculo.cor);
        printf("Placa:");
        scanf(" %[^\n]", &veiculo.placa);
        printf("Valor Diária:");
        fflush(stdin);
        scanf("%f", &veiculo.valorDiaria);
        printf("Quantidade de Ocupantes:");
        fflush(stdin);
        scanf("%d", &veiculo.quantOcupantes);
        printf("Status [ocupado, ..., ...]:");
        scanf(" %[^\n]", &veiculo.status);

        fseek(arquivoVeiculos, 0, SEEK_END);
        fwrite(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);
        fflush(arquivoVeiculos);
    }
    else
    {
        printf("\n----------ERRO----------");
        printf(
            "\n Não é possível cadastrar mais de um veículo com o mesmo código!");
        printf("\n Já existe um veículo com o código %s no arquivo",
               veiculo.codigoVeiculo);
        printf("\n--------------------------");
    }
}

int localizaCliente(FILE *arquivoClientes, char codCliente[20])
{
    int indice, encontrouCliente;

    indice = -1;
    encontrouCliente = 0;
    tCliente cliente;

    fseek(arquivoClientes, 0, SEEK_SET);
    fread(&cliente, sizeof(cliente), 1, arquivoClientes);

    while (!feof(arquivoClientes) && !encontrouCliente)
    {
        indice++;
        if (strcasecmp(cliente.codigoCliente, codCliente) == 0)
        {
            encontrouCliente = 1;
        }
        fread(&cliente, sizeof(cliente), 1, arquivoClientes);
    }

    if (encontrouCliente)
        return indice;
    else
        return -1;
}

int localizaVeiculo(FILE *arquivoVeiculos, char codVeiculo[20])
{
    int indice, encontrouVeiculo;

    indice = -1;
    encontrouVeiculo = 0;
    tVeiculo veiculo;

    fseek(arquivoVeiculos, 0, SEEK_SET);
    fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);

    while (!feof(arquivoVeiculos) && !encontrouVeiculo)
    {
        indice++;
        if (strcasecmp(veiculo.codigoVeiculo, codVeiculo) == 0)
        {
            encontrouVeiculo = 1;
        }
        fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);
    }

    if (encontrouVeiculo)
        return indice;
    else
        return -1;
}

void encontreCliente(FILE *arquivoClientes, char codCliente[20])
{

    tCliente cliente;

    fseek(arquivoClientes, 0, SEEK_SET);
    fread(&cliente, sizeof(cliente), 1, arquivoClientes);

    while (!feof(arquivoClientes))
    {
        if (strcasecmp(codCliente, cliente.codigoCliente) == 0)
        {
            printf("\nCliente encontrado!\n");
            printf("Código do cliente: %s \n", cliente.codigoCliente);
            printf("Nome do cliente: %s\n", cliente.nomeCliente);
            printf("Telefone do cliente: %s\n", cliente.telefoneCliente);
            printf("Endereço:\n");
            printf("Rua: %s\n", cliente.enderecoCliente.rua);
            printf("Numero: %s\n", cliente.enderecoCliente.numero);
            printf("Complemento: %s\n", cliente.enderecoCliente.complemento);
            printf("Bairro: %s\n", cliente.enderecoCliente.bairro);
            printf("Cidade: %s\n", cliente.enderecoCliente.cidade);
            printf("Estado: %s\n", cliente.enderecoCliente.estado);
            printf("CEP: %s\n\n", cliente.enderecoCliente.cep);
        }
        else
        {
            printf("\nCliente não encontrado!\n\n");
        }
        fread(&cliente, sizeof(cliente), 1, arquivoClientes);
    }
}

void listarClientes(FILE *arquivoClientes)
{
    tCliente cliente;

    fseek(arquivoClientes, 0, SEEK_SET);
    fread(&cliente, sizeof(cliente), 1, arquivoClientes);

    while (!feof(arquivoClientes))
    {
        printf("\nCliente cadastrados\n");
        printf("Código do cliente: %s \n", cliente.codigoCliente);
        printf("Nome do cliente: %s\n", cliente.nomeCliente);
        printf("Telefone do cliente: %s\n", cliente.telefoneCliente);
        printf("Endereço:\n");
        printf("Rua: %s\n", cliente.enderecoCliente.rua);
        printf("Numero: %s\n", cliente.enderecoCliente.numero);
        printf("Complemento: %s\n", cliente.enderecoCliente.complemento);
        printf("Bairro: %s\n", cliente.enderecoCliente.bairro);
        printf("Cidade: %s\n", cliente.enderecoCliente.cidade);
        printf("Estado: %s\n", cliente.enderecoCliente.estado);
        printf("CEP: %s\n\n", cliente.enderecoCliente.cep);

        fread(&cliente, sizeof(cliente), 1, arquivoClientes);
    }
}
