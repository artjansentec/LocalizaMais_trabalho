#include <conio.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// criando estruturas

struct sData
{
    int dia;
    int mes;
    int ano;
};

typedef struct sData tData;

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
    tData dataRetirada;
    tData dataDevolucao;
    float seguro;
    int quantDias[4];
    char codCliente[25];
    char codVeiculo[25];
};

// declarando tipos para variaveis
typedef struct sCliente tCliente;
typedef struct sVeiculo tVeiculo;
typedef struct sLocacao tLocacao;
typedef struct sData tData;

int diasPorMes[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, //qtd dias anos normais
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
}; //qtd dias anos bissextos

void menu()
{
    printf("--------------------------------------------");
    printf("\n|Bem vindo a LocalizaMais!!               |");
    printf("\n|0) Sair                                  |");
    printf("\n|1) Incluir cliente                       |");
    printf("\n|2) Incluir veiculo                       |");
    printf("\n|3) Cadastrar locacao                     |");
    printf("\n|5) Mostrar informações de um cliente     |");
    printf("\n|6) Listar todos os clientes              |");
    printf("\n|7) Mostrar informações de um veículo     |");
    printf("\n|8) Listar todos os veículos              |");
    printf("\n|9) Listar locações de um cliente         |");
}

int main()
{
    FILE *arquivoClientes;
    FILE *arquivoVeiculos;
    FILE *arquivoLocacao;

    int opcao;
    char encontrarCodCliente[20], encontrarCodVeiculo[20];

    setlocale(LC_ALL, "portuguese");

    if (((arquivoClientes = fopen("Clientes.dat", "r+b")) == NULL) || ((arquivoVeiculos = fopen("Veiculos.dat", "r+b")) == NULL)
        || ((arquivoLocacao = fopen("Locacoes.dat", "r+b")) == NULL))
    {
        printf("\n--------------------------");
        printf("\n|    Criando o Arquivo   |");
        printf("\n--------------------------\n");
        if (((arquivoClientes = fopen("Clientes.dat", "w+b")) == NULL) || ((arquivoVeiculos = fopen("Veiculos.dat", "w+b")) == NULL)
            || ((arquivoLocacao = fopen("Locacoes.dat", "w+b")) == NULL))
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
        case 3:
            cadastrarLocacao(arquivoLocacao, arquivoClientes, arquivoVeiculos);
            break;
        case 5:
            printf("Digite o codigo do cliente que deseja encontrar: ");
            scanf(" %[^\n]", &encontrarCodCliente);
            encontreCliente(arquivoClientes, encontrarCodCliente);
            break;
        case 6:
            listarClientes(arquivoClientes);
            break;
        case 7:
            printf("Digite o código do veículo que deseja encontrar: ");
            scanf(" %[^\n]", &encontrarCodVeiculo);
            encontreVeiculo(arquivoVeiculos, encontrarCodVeiculo);
            break;
        case 8:
            listarVeiculos(arquivoVeiculos);
            break;
        case 9:
            listarLocacoes(arquivoLocacao);
            break;
        }
    }
    while (opcao != 0);

    fclose(arquivoClientes);
    fclose(arquivoVeiculos);
    fclose(arquivoLocacao);

    return 0;
}

/*FUNÇÕES CLIENTE*/
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
/*FIM FUNÇÕES CLIENTE*/

/*FUNÇÕES VEÍCULO*/
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

        printf("Digite o Status do Veículo:(Alugado, Disponível, Em Manutenção)\n");
        scanf(" %[^\n]", &veiculo.status);

        if(strcasecmp(veiculo.status, "Alugado") == 0)
        {
            printf("Foi");
        }

        while(strcasecmp(veiculo.status, "Alugado") != 0 && strcasecmp(veiculo.status, "Disponível") != 0 && strcasecmp(veiculo.status, "Disponivel") != 0
                && strcasecmp(veiculo.status, "Em Manutenção") != 0 && strcasecmp(veiculo.status, "Em Manutencao") != 0)
        {
            printf("Status inválido! Os status possíveis são:(Alugado, Disponível, Em Manutenção)\n");
            scanf(" %[^\n]", &veiculo.status);
        }
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

void encontreVeiculo(FILE *arquivoVeiculos, char codigoVeiculo[20])
{
    tVeiculo veiculo;

    fseek(arquivoVeiculos, 0, SEEK_SET);
    fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);

    while (!feof(arquivoVeiculos))
    {
        if (strcasecmp(codigoVeiculo, veiculo.codigoVeiculo) == 0)
        {
            printf("\nVeículo encontrado!\n");
            printf("Código do veiculo: %s\n", veiculo.codigoVeiculo);
            printf("Descrição do veículo: %s\n", veiculo.descricao);
            printf("Modelo do veículo: %s\n", veiculo.modelo);
            printf("Cor do veículo: %s\n", veiculo.cor);
            printf("Placa do veículo: %s\n", veiculo.placa);
            printf("valorDiária do veículo: %f\n", veiculo.valorDiaria);
            printf("quantOcupantes do veículo: %i\n", veiculo.quantOcupantes);
            printf("Status do veículo: %s\n\n", veiculo.status);
        }
        else
        {
            printf("\nVeículo não encontrado!\n\n");
        }
        fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);
    }
}

void listarVeiculos(FILE *arquivoVeiculos)
{
    tVeiculo veiculo;

    fseek(arquivoVeiculos, 0, SEEK_SET);
    fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);

    while (!feof(arquivoVeiculos))
    {
        printf("\nVeículos cadastrados\n");
        printf("Código do veiculo: %s\n", veiculo.codigoVeiculo);
        printf("Descrição do veículo: %s\n", veiculo.descricao);
        printf("Modelo do veículo: %s\n", veiculo.modelo);
        printf("Cor do veículo: %s\n", veiculo.cor);
        printf("Placa do veículo: %s\n", veiculo.placa);
        printf("valorDiária do veículo: %f\n", veiculo.valorDiaria);
        printf("quantOcupantes do veículo: %i\n", veiculo.quantOcupantes);
        printf("Status do veículo: %s\n\n", veiculo.status);

        fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);
    }
}
/*FIM FUNÇÕES VEÍCULO*/

/*FUNÇÕES LOCAÇÃO*/
void cadastrarLocacao(FILE *arquivoLocacao, FILE *arquivoClientes, FILE *arquivoVeiculos)
{
    system("cls");

    tLocacao locacao;

    int quantidadeOcupantes, qtdVeiculosDisponiveis, indice, quantidadeDiasLocacao, desejaSeguro;

    printf("\nDigite o código da locação: ");
    scanf(" %[^\n]", &locacao.codigoLocacao);

    indice = localizaLocacao(arquivoLocacao, locacao.codigoLocacao);

    if(indice == -1){
        printf("Digite o seu código de cliente: ");
        scanf(" %[^\n]", &locacao.codCliente);

        while(localizaCliente(arquivoClientes, locacao.codCliente) == -1)
        {
            printf("\nCódigo de cliente inexistente!");
            printf("\nDigite o código novamente: ");
            scanf(" %[^\n]", &locacao.codCliente);
        }

        printf("\nData de retirada do veículo no formato (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);

        while(validarData(locacao.dataRetirada) == -1)
        {
            printf("\nFormato de data inválido, digite novamente!");
            printf("\nData de retirada do veículo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);
        }

        printf("\nData de devolução do veículo no formato (DD/MM/YYYY): ");
        scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);

        while(validarData(locacao.dataDevolucao) == -1)
        {
            printf("\nFormato de data inválido, digite novamente!");
            printf("\nData de devolução do veículo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);
        }

        while(validarIntervaloEntreDatas(locacao.dataRetirada, locacao.dataDevolucao) == -1)
        {
            printf("Atenção! A data de retirada deve ser anterior a data de devolução!\n");

            printf("\nDigite novamente a data de retirada do veículo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);

            while(validarData(locacao.dataRetirada) == -1)
            {
                printf("\nFormato de data inválido, digite novamente!");
                printf("\nData de retirada do veículo no formato (DD/MM/YYYY): ");
                scanf("%i/%i/%i", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);
            }

            printf("\nDigite novamente a data de devolução do veículo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);

            while(validarData(locacao.dataDevolucao) == -1)
            {
                printf("\nFormato de data inválido, digite novamente!");
                printf("\nData de devolução do veículo no formato (DD/MM/YYYY): ");
                scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);
            }
        }

        printf("\nDigite a quantidade de ocupantes que necessita: ");
        fflush(stdin);
        scanf("%i", &quantidadeOcupantes);

        if(localizarQtdVeiculosDisponiveis(arquivoVeiculos, quantidadeOcupantes) > 0)
        {
            imprimirVeiculosDisponiveis(arquivoVeiculos, quantidadeOcupantes);

            printf("\nDigite o código do veículo desejado: ");
            scanf(" %[^\n]", &locacao.codVeiculo);

            while(localizaVeiculo(arquivoVeiculos, locacao.codVeiculo) == -1)
            {
                printf("\nO código de veículo digitado não existe, digite novamente!");
                printf("\nDigite o código do veículo desejado: ");
                scanf(" %[^\n]", &locacao.codVeiculo);
            }

            mudarStatusVeiculo(arquivoVeiculos, locacao.codVeiculo);

            quantidadeDiasLocacao = calcularQtdDiasLocacao(locacao.dataRetirada, locacao.dataDevolucao);
            printf("\nQuantidade de dias que o veículo será alugado: %d", quantidadeDiasLocacao);

            printf("\nDeseja contratar um seguro para o veículo alugado?\n1 - Sim\n2- Não\n");
            scanf("%d", &desejaSeguro);

            while(desejaSeguro != 1 && desejaSeguro != 2)
            {
                printf("Digite uma opção válida!");
                printf("\nDeseja contratar um seguro para o veículo alugado?\n1 - Sim\n2- Não\n");
                scanf("%d", &desejaSeguro);
            }
            if(desejaSeguro == 1)
            {
                locacao.seguro = 50;
            }
            else
            {
                locacao.seguro = 0;
            }

            printf("\n-----------------------------");
            printf("\nVeículo Alugado com Sucesso!!!");
            printf("\n-----------------------------");

            fseek(arquivoLocacao, 0, SEEK_END);
            fwrite(&locacao, sizeof(locacao), 1, arquivoLocacao);
            fflush(arquivoLocacao);
        }
        else
        {
            printf("Não possuimos veículos disponíveis no momento que atendam suas necessidades!\n");

        }

        //FALTA validar se já existe uma locacao para o veiculo escolhido no período data de retirada e data de devolução
    }
    else
    {
        printf("\n----------ERRO----------");
        printf(
            "\n Não é possível cadastrar mais de uma locação com o mesmo código!");
        printf("\n Já existe uma locação com o código %s no arquivo",
               locacao.codigoLocacao);
        printf("\n--------------------------");
    }
}

int validarIntervaloEntreDatas(tData dataRetirada, tData dataDevolucao)
{
    int validador; //0 para datas válidas e -1 para inválidas

    if(dataRetirada.ano < dataDevolucao.ano)
        validador = 0;
    else if(dataRetirada.ano > dataDevolucao.ano)
        validador = -1;
    else
    {
        if(dataRetirada.mes < dataDevolucao.mes)
            validador = 0;
        else if(dataRetirada.mes > dataDevolucao.mes)
            validador = -1;
        else
        {
            if(dataRetirada.dia <= dataDevolucao.dia)
                validador = 0;
            else if(dataRetirada.dia > dataDevolucao.dia)
                validador = -1;
            }
    }
    return validador;
}

int validarData(tData data)
{
    tData dataAtual;

    time_t t = time(NULL);
    struct tm da = *localtime(&t);

    dataAtual.dia = da.tm_mday;
    dataAtual.mes = da.tm_mon + 1;
    dataAtual.ano = da.tm_year + 1900;

    if(data.dia < 1 || data.dia > 31)
        return -1;
    if(data.mes < 1 || data.mes > 12)
        return -1;
    if((data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11) && (data.dia > 30))
        return -1;
    if(verificaAnoBissexto(data.ano) == 1 && data.mes == 2 && data.dia > 29)
        return -1;
    if(verificaAnoBissexto(data.ano) == 0 && data.mes == 2 && data.dia > 28)
        return -1;
    if(data.ano < 1900 || data.ano > 2100)
        return -1;
    if(data.ano < dataAtual.ano)
        return -1;
    if(data.mes < dataAtual.mes && data.ano < dataAtual.ano)
        return -1;
    if(data.dia < dataAtual.dia && data.mes < dataAtual.mes && data.ano < dataAtual.ano)
        return -1;
    return 0;
}

int verificaAnoBissexto(int ano)
{
    //retorna 1 se for bissexto e 0 se não for
    return (ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0));
}

int calcularQtdDiasLocacao(tData dataRetirada, tData dataDevolucao)
{
    int diaInicial, diaFinal, diferencaAnos, i, ehBissexto;

    diferencaAnos = 0;

    diaInicial = dataRetirada.dia;
    ehBissexto = verificaAnoBissexto(dataRetirada.ano);

    for(i = dataRetirada.mes - 1; i > 0; --i)
    {
        diaInicial +=  diasPorMes[ehBissexto][i];
    }

    diaFinal = dataDevolucao.dia;
    ehBissexto = verificaAnoBissexto(dataDevolucao.ano);

    for(i = dataDevolucao.mes - 1; i > 0; --i)
    {
        diaFinal += diasPorMes[ehBissexto][i];
    }

    while(dataRetirada.ano < dataDevolucao.ano)
    {
        diferencaAnos += 365 + verificaAnoBissexto(dataRetirada.ano++);
    }

    return diferencaAnos - diaInicial + diaFinal;
}

void mudarStatusVeiculo(FILE *arquivoVeiculos, char codVeiculo[25])
{
    int indiceVeiculo;
    tVeiculo veiculo;

    indiceVeiculo = localizaVeiculo(arquivoVeiculos, codVeiculo);

    if(indiceVeiculo != -1) //SE encontrou o veículo
    {
        fseek(arquivoVeiculos,sizeof(veiculo)*(indiceVeiculo),SEEK_SET);
        fread(&veiculo, sizeof(veiculo),1, arquivoVeiculos);

        veiculo.status[indiceVeiculo] = strcpy(veiculo.status,"Alugado");

        fseek(arquivoVeiculos,sizeof(veiculo)*(indiceVeiculo),SEEK_SET);
        fwrite(&veiculo, sizeof(veiculo),1, arquivoVeiculos);
        fflush(arquivoVeiculos);
    }
}

int localizarQtdVeiculosDisponiveis(FILE *arquivoVeiculos, int qtdOcupantesNecessarios)
{
    tVeiculo veiculo;

    int qtdVeiculosDisponiveis = 0;

    fseek(arquivoVeiculos, 0, SEEK_SET);
    fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);

    while(!feof(arquivoVeiculos))
    {
        if(veiculo.quantOcupantes >= qtdOcupantesNecessarios && (strcasecmp(veiculo.status, "Disponível") == 0 || strcasecmp(veiculo.status, "Disponivel") == 0))
            qtdVeiculosDisponiveis++;
        fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);
    }
    return qtdVeiculosDisponiveis;
}

void imprimirVeiculosDisponiveis(FILE *arquivoVeiculos, int qtdOcupantesNecessarios)
{
    tVeiculo veiculo;

    fseek(arquivoVeiculos, 0, SEEK_SET);
    fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);

    while(!feof(arquivoVeiculos))
    {
        if(veiculo.quantOcupantes >= qtdOcupantesNecessarios && (strcasecmp(veiculo.status, "Disponível") == 0 || strcasecmp(veiculo.status, "Disponivel") == 0))
        {
            printf("Veiculos Disponíveis\n");
            printf("Código do veiculo: %s\n", veiculo.codigoVeiculo);
            printf("Descrição do veículo: %s\n", veiculo.descricao);
            printf("Modelo do veículo: %s\n", veiculo.modelo);
            printf("Cor do veículo: %s\n", veiculo.cor);
            printf("Placa do veículo: %s\n", veiculo.placa);
            printf("valorDiária do veículo: %f\n", veiculo.valorDiaria);
            printf("quantOcupantes do veículo: %i\n", veiculo.quantOcupantes);
            printf("Status do veículo: %s\n\n", veiculo.status);
        }
        fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);
    }
}

int localizaLocacao(FILE *arquivoLocacao, char codLocacao[20])
{
    int indice, encontrouLocacao;

    indice = -1;
    encontrouLocacao = 0;
    tLocacao locacao;

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

    while (!feof(arquivoLocacao) && !encontrouLocacao)
    {
        indice++;
        if (strcasecmp(locacao.codigoLocacao, codLocacao) == 0)
        {
            encontrouLocacao = 1;
        }
        fread(&locacao, sizeof(locacao), 1, arquivoLocacao);
    }

    if (encontrouLocacao)
        return indice;
    else
        return -1;
}

void listarLocacoes(FILE *arquivoLocacao)
{
    tLocacao locacao;

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

    while (!feof(arquivoLocacao))
    {
        printf("\nLocações Cadastradas\n");
        printf("Código da locacao: %s\n", locacao.codigoLocacao);
        printf("Data de retirada: %d/%d/%d\n", locacao.dataRetirada.dia, locacao.dataRetirada.mes, locacao.dataRetirada.ano);
        printf("Data de devolução: %d/%d/%d\n", locacao.dataDevolucao.dia, locacao.dataDevolucao.mes, locacao.dataDevolucao.ano);
        printf("Valor do seguro: %f\n", locacao.seguro);
        printf("Quantidades de dia que serão alugados: %i\n", locacao.quantDias);
        printf("Código do cliente: %s\n", locacao.codCliente);
        printf("Código do veículo: %s\n", locacao.codVeiculo);

        fread(&locacao, sizeof(locacao), 1, arquivoLocacao);
    }
}
/*FIM FUNÇÕES LOCAÇÃO*/

/*FUNÇÕES DE DAR BAIXA NA LOCAÇÃO*/
/*FIM  FUNÇÕES DE DAR BAIXA NA LOCAÇÃO*/
