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
    int quantDias;
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
    printf("---------------------------------------------------------------------------------------------------");
    printf("\n|Bem vindo a LocalizaMais!!                                                                       |");
    printf("\n|0)   Sair                                                                                        |");
    printf("\n|1)   Incluir cliente                                                                             |");
    printf("\n|2)   Incluir veiculo                                                                             |");
    printf("\n|3)   Cadastrar locacao                                                                           |");
    printf("\n|4)   Dar baixa na loca????o                                                                        |");
    printf("\n|5)   Mostrar informa????es de um cliente                                                           |");
    printf("\n|6)   Listar todos os clientes                                                                    |");
    printf("\n|7)   Mostrar informa????es de um ve??culo                                                           |");
    printf("\n|8)   Listar todos os ve??culos                                                                    |");
    printf("\n|9)   Listar loca????es de um cliente                                                               |");
    printf("\n|10)  Mostrar pontos de fidelidade do cliente                                                     |");
    printf("\n|11)  Pesquisar clientes com mais de 500 pontos de fidelidade que ser??o premiados com um kit!     |");
    printf("\n|12)  Atualizando dados dos clientes                                                              |");
    printf("\n-------------------------------------------------------------------------------------------------");
}

int main()
{
    FILE *arquivoClientes;
    FILE *arquivoVeiculos;
    FILE *arquivoLocacao;

    int opcao, pontosFidelidade;
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
            printf("\n\n|| ERRO NA CRIA????O DO ARQUIVO!! ||");
            exit(1);
        }
        else
        {
            printf("\n\n Arquivo Criado!! \n");
        }
    }
    printf("\n");
    system("pause");

    do
    {
        system("cls");
        menu();
        printf("\nDigite a funcao que deseja executar: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            break;
        case 1:
            system("cls");
            incluirCliente(arquivoClientes);
            break;
        case 2:
            system("cls");
            incluirVeiculo(arquivoVeiculos);
            break;
        case 3:
            system("cls");
            cadastrarLocacao(arquivoLocacao, arquivoClientes, arquivoVeiculos);
            break;
        case 4:
            system("cls");
            darBaixaLocacao(arquivoLocacao, arquivoClientes, arquivoVeiculos);
            break;
        case 5:
            system("cls");
            printf("Digite o codigo do cliente que deseja encontrar: ");
            scanf(" %[^\n]", &encontrarCodCliente);
            encontreCliente(arquivoClientes, encontrarCodCliente);
            break;
        case 6:
            system("cls");
            listarClientes(arquivoClientes);
            break;
        case 7:
            system("cls");
            printf("Digite o c??digo do ve??culo que deseja encontrar: ");
            scanf(" %[^\n]", &encontrarCodVeiculo);
            encontreVeiculo(arquivoVeiculos, encontrarCodVeiculo);
            break;
        case 8:
            system("cls");
            listarVeiculos(arquivoVeiculos);
            break;
        case 9:
            system("cls");
            printf("Digite o codigo de cliente para encontrar a loca????o: ");
            scanf(" %[^\n]", &encontrarCodCliente);
            listarLocacoes(arquivoLocacao, encontrarCodCliente);
            break;
        case 10:
            system("cls");
            printf("\nDigite o c??digo de cliente para exibir os pontos de fidelidade: ");
            scanf(" %[^\n]", &encontrarCodCliente);
            pontosFidelidade = calcularPontosFidelidade(arquivoLocacao, arquivoClientes, encontrarCodCliente);
            printf("\n\nPontos de fidelidade do cliente: %d\n",pontosFidelidade);
            break;
        case 11:
            system("cls");
            buscaClientesAptosAhGanharKit(arquivoClientes, arquivoLocacao);
            break;
        case 12:
            system("cls");
            alterarDadosCLiente(arquivoClientes);
            break;
        }
        printf("\n");
        system("pause");
    }
    while (opcao != 0);

    fclose(arquivoClientes);
    fclose(arquivoVeiculos);
    fclose(arquivoLocacao);

    return 0;
}

/*FUN????ES CLIENTE*/
void incluirCliente(FILE *arquivoClientes)
{
    tCliente cliente;
    int indice;

    printf("--------------------------\n");
    printf("|   Inclus??o de Cliente  |");
    printf("\n--------------------------");

    printf("\nDigite o c??digo do cliente: ");
    scanf(" %[^\n]", &cliente.codigoCliente);

    indice = localizaCliente(arquivoClientes, cliente.codigoCliente);

    if (indice == -1) // n??o possuia esse codigoCliente no arquivo
    {
        printf("Nome do Cliente: ");
        scanf(" %[^\n]", &cliente.nomeCliente);
        printf("Telefone: ");
        scanf(" %[^\n]", &cliente.telefoneCliente);
        printf("Endere??o:\n");
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
            "\n N??o ?? poss??vel cadastrar mais de um cliente com o mesmo c??digo!");
        printf("\n J?? existe um cliente com o c??digo %s no arquivo",
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
            printf("C??digo do cliente: %s \n", cliente.codigoCliente);
            printf("Nome do cliente: %s\n", cliente.nomeCliente);
            printf("Telefone do cliente: %s\n", cliente.telefoneCliente);
            printf("Endere??o:\n");
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
            printf("\nCliente n??o encontrado!\n\n");
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
        printf("C??digo do cliente: %s \n", cliente.codigoCliente);
        printf("Nome do cliente: %s\n", cliente.nomeCliente);
        printf("Telefone do cliente: %s\n", cliente.telefoneCliente);
        printf("Endere??o:\n");
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
/*FIM FUN????ES CLIENTE*/


/*FUN????ES VE??CULO*/
void incluirVeiculo(FILE *arquivoVeiculos)
{
    tVeiculo veiculo;
    int indice;

    printf("--------------------------\n");
    printf("|   Inclus??o de Ve??culo  |");
    printf("\n--------------------------");

    printf("\nDigite o c??digo do ve??culo: ");
    scanf(" %[^\n]", &veiculo.codigoVeiculo);

    indice = localizaVeiculo(arquivoVeiculos, veiculo.codigoVeiculo);

    if (indice == -1) // n??o possuia esse codigoVeiculo no arquivo
    {
        printf("Descri????o do ve??culo: ");
        scanf(" %[^\n]", &veiculo.descricao);
        printf("Modelo: ");
        scanf(" %[^\n]", &veiculo.modelo);
        printf("Cor:");
        scanf(" %[^\n]", &veiculo.cor);

        printf("Placa:");
        scanf(" %[^\n]", &veiculo.placa);

        while(validarPlaca(veiculo.placa)){
            printf("Placa invalida, favor digitar 3 letras e 4 numeros\n");
            printf("Placa:");
            scanf(" %[^\n]", &veiculo.placa);

        }

        printf("Valor Di??ria:");
        fflush(stdin);
        scanf("%f", &veiculo.valorDiaria);
        printf("Quantidade de Ocupantes:");
        fflush(stdin);
        scanf("%d", &veiculo.quantOcupantes);

        printf("Digite o Status do Ve??culo:(Alugado, Dispon??vel, Em Manuten????o)\n");
        scanf(" %[^\n]", &veiculo.status);

        if(strcasecmp(veiculo.status, "Alugado") == 0)
        {
            printf("Foi");
        }

        while(strcasecmp(veiculo.status, "Alugado") != 0 && strcasecmp(veiculo.status, "Disponivel") != 0
                && strcasecmp(veiculo.status, "Em Manutencao") != 0)
        {
            printf("Status inv??lido! Os status poss??veis s??o:(Alugado, Dispon??vel, Em Manuten????o)\n");
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
            "\n N??o ?? poss??vel cadastrar mais de um ve??culo com o mesmo c??digo!");
        printf("\n J?? existe um ve??culo com o c??digo %s no arquivo",
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
            printf("\nVe??culo encontrado!\n");
            printf("C??digo do veiculo: %s\n", veiculo.codigoVeiculo);
            printf("Descri????o do ve??culo: %s\n", veiculo.descricao);
            printf("Modelo do ve??culo: %s\n", veiculo.modelo);
            printf("Cor do ve??culo: %s\n", veiculo.cor);
            printf("Placa do ve??culo: %s\n", veiculo.placa);
            printf("valorDi??ria do ve??culo: %f\n", veiculo.valorDiaria);
            printf("quantOcupantes do ve??culo: %i\n", veiculo.quantOcupantes);
            printf("Status do ve??culo: %s\n\n", veiculo.status);
        }
        else
        {
            printf("\nVe??culo n??o encontrado!\n\n");
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
        printf("\nVe??culos cadastrados\n");
        printf("C??digo do veiculo: %s\n", veiculo.codigoVeiculo);
        printf("Descri????o do ve??culo: %s\n", veiculo.descricao);
        printf("Modelo do ve??culo: %s\n", veiculo.modelo);
        printf("Cor do ve??culo: %s\n", veiculo.cor);
        printf("Placa do ve??culo: %s\n", veiculo.placa);
        printf("valorDi??ria do ve??culo: %f\n", veiculo.valorDiaria);
        printf("quantOcupantes do ve??culo: %i\n", veiculo.quantOcupantes);
        printf("Status do ve??culo: %s\n\n", veiculo.status);

        fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);
    }
}
/*FIM FUN????ES VE??CULO*/


/*FUN????ES LOCA????O*/
void cadastrarLocacao(FILE *arquivoLocacao, FILE *arquivoClientes, FILE *arquivoVeiculos)
{
    system("cls");

    tLocacao locacao;

    int quantidadeOcupantes, qtdVeiculosDisponiveis, indice, quantidadeDiasLocacao, desejaSeguro;

    printf("\nDigite o c??digo da loca????o: ");
    scanf(" %[^\n]", &locacao.codigoLocacao);

    indice = localizaLocacao(arquivoLocacao, locacao.codigoLocacao);

    if(indice == -1)
    {
        printf("Digite o seu c??digo de cliente: ");
        scanf(" %[^\n]", &locacao.codCliente);

        while(localizaCliente(arquivoClientes, locacao.codCliente) == -1)
        {
            printf("\nC??digo de cliente inexistente!");
            printf("\nDigite o c??digo novamente: ");
            scanf(" %[^\n]", &locacao.codCliente);
        }

        int validadorDate = -1;
        while(validadorDate != 1){

        printf("\nData de retirada do ve??culo no formato (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);

        while(validarData(locacao.dataRetirada) == -1)
        {
            printf("\nFormato de data inv??lido, digite novamente!");
            printf("\nData de retirada do ve??culo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);
        }

        printf("\nData de devolu????o do ve??culo no formato (DD/MM/YYYY): ");
        scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);

        while(validarData(locacao.dataDevolucao) == -1)
        {
            printf("\nFormato de data inv??lido, digite novamente!");
            printf("\nData de devolu????o do ve??culo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);
        }

        while(validarIntervaloEntreDatas(locacao.dataRetirada, locacao.dataDevolucao) == -1)
        {
            printf("Aten????o! A data de retirada deve ser anterior a data de devolu????o!\n");

            printf("\nDigite novamente a data de retirada do ve??culo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);

            while(validarData(locacao.dataRetirada) == -1)
            {
                printf("\nFormato de data inv??lido, digite novamente!");
                printf("\nData de retirada do ve??culo no formato (DD/MM/YYYY): ");
                scanf("%i/%i/%i", &locacao.dataRetirada.dia, &locacao.dataRetirada.mes, &locacao.dataRetirada.ano);
            }

            printf("\nDigite novamente a data de devolu????o do ve??culo no formato (DD/MM/YYYY): ");
            scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);

            while(validarData(locacao.dataDevolucao) == -1)
            {
                printf("\nFormato de data inv??lido, digite novamente!");
                printf("\nData de devolu????o do ve??culo no formato (DD/MM/YYYY): ");
                scanf("%i/%i/%i", &locacao.dataDevolucao.dia, &locacao.dataDevolucao.mes, &locacao.dataDevolucao.ano);
            }
            }
            if(validarLocacaoDia(arquivoLocacao, locacao.codVeiculo,locacao.dataRetirada.dia, locacao.dataRetirada.mes, locacao.dataRetirada.ano,locacao.dataDevolucao.dia, locacao.dataDevolucao.mes, locacao.dataDevolucao.ano) == 1)
            {
                printf("\nPeriodo j?? utlizado, escolha outros dias");
                // fazendo a valida????o dar errado;
                validadorDate = -1;
            }else
                printf("\nPeriodo v??lido");
                validadorDate = 1;
        }

        printf("\nDigite a quantidade de ocupantes que necessita: ");
        fflush(stdin);
        scanf("%i", &quantidadeOcupantes);

        if(localizarQtdVeiculosDisponiveis(arquivoVeiculos, quantidadeOcupantes) > 0)
        {
            imprimirVeiculosDisponiveis(arquivoVeiculos, quantidadeOcupantes);

            printf("\nDigite o c??digo do ve??culo desejado: ");
            scanf(" %[^\n]", &locacao.codVeiculo);

            while(localizaVeiculo(arquivoVeiculos, locacao.codVeiculo) == -1)
            {
                printf("\nO c??digo de ve??culo digitado n??o existe, digite novamente!");
                printf("\nDigite o c??digo do ve??culo desejado: ");
                scanf(" %[^\n]", &locacao.codVeiculo);
            }

            mudarStatusVeiculo(arquivoVeiculos, locacao.codVeiculo);

            quantidadeDiasLocacao = calcularQtdDiasLocacao(locacao.dataRetirada, locacao.dataDevolucao);
            printf("\nQuantidade de dias que o ve??culo ser?? alugado: %d", quantidadeDiasLocacao);

            locacao.quantDias = quantidadeDiasLocacao;

            printf("\nDeseja contratar um seguro para o ve??culo alugado?\n1 - Sim\n2- N??o\n");
            scanf("%d", &desejaSeguro);

            while(desejaSeguro != 1 && desejaSeguro != 2)
            {
                printf("Digite uma op????o v??lida!");
                printf("\nDeseja contratar um seguro para o ve??culo alugado?\n1 - Sim\n2- N??o\n");
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
            printf("\nVe??culo Alugado com Sucesso!!!");
            printf("\n-----------------------------");

            fseek(arquivoLocacao, 0, SEEK_END);
            fwrite(&locacao, sizeof(locacao), 1, arquivoLocacao);
            fflush(arquivoLocacao);
        }
        else
        {
            printf("N??o possuimos ve??culos dispon??veis no momento que atendam suas necessidades!\n");

        }

        //FALTA validar se j?? existe uma locacao para o veiculo escolhido no per??odo data de retirada e data de devolu????o
    }
    else
    {
        printf("\n----------ERRO----------");
        printf(
            "\n N??o ?? poss??vel cadastrar mais de uma loca????o com o mesmo c??digo!");
        printf("\n J?? existe uma loca????o com o c??digo %s no arquivo",
               locacao.codigoLocacao);
        printf("\n--------------------------");
    }
}

int validarIntervaloEntreDatas(tData dataRetirada, tData dataDevolucao)
{
    int validador; //0 para datas v??lidas e -1 para inv??lidas

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
    return 0;
}

int verificaAnoBissexto(int ano)
{
    //retorna 1 se for bissexto e 0 se n??o for
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

    if(indiceVeiculo != -1) //SE encontrou o ve??culo
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
        if(veiculo.quantOcupantes >= qtdOcupantesNecessarios && (strcasecmp(veiculo.status, "Dispon??vel") == 0 || strcasecmp(veiculo.status, "Disponivel") == 0))
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
        if(veiculo.quantOcupantes >= qtdOcupantesNecessarios && (strcasecmp(veiculo.status, "Dispon??vel") == 0 || strcasecmp(veiculo.status, "Disponivel") == 0))
        {
            printf("Veiculos Dispon??veis\n");
            printf("C??digo do veiculo: %s\n", veiculo.codigoVeiculo);
            printf("Descri????o do ve??culo: %s\n", veiculo.descricao);
            printf("Modelo do ve??culo: %s\n", veiculo.modelo);
            printf("Cor do ve??culo: %s\n", veiculo.cor);
            printf("Placa do ve??culo: %s\n", veiculo.placa);
            printf("valorDi??ria do ve??culo: %f\n", veiculo.valorDiaria);
            printf("quantOcupantes do ve??culo: %i\n", veiculo.quantOcupantes);
            printf("Status do ve??culo: %s\n\n", veiculo.status);
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

void listarLocacoes(FILE *arquivoLocacao, char codCliente[20])
{
    tLocacao locacao;

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

    while (!feof(arquivoLocacao))
    {
        if (strcasecmp(codCliente, locacao.codCliente) == 0)
        {
            printf("\nLoca????es Cadastradas\n");
            printf("C??digo da locacao: %s\n", locacao.codigoLocacao);
            printf("Data de retirada: %d/%d/%d\n", locacao.dataRetirada.dia, locacao.dataRetirada.mes, locacao.dataRetirada.ano);
            printf("Data de devolu????o: %d/%d/%d\n", locacao.dataDevolucao.dia, locacao.dataDevolucao.mes, locacao.dataDevolucao.ano);
            printf("Valor do seguro: %f\n", locacao.seguro);
            printf("Quantidades de dia que ser??o alugados: %i\n", locacao.quantDias);
            printf("C??digo do cliente: %s\n", locacao.codCliente);
            printf("C??digo do ve??culo: %s\n", locacao.codVeiculo);
        }
        else
        {
            printf("\nN??o existem loca????es com o c??digo de cliente digitado!");
        }
        fread(&locacao, sizeof(locacao), 1, arquivoLocacao);
    }
}

int validarLocacaoDia(FILE *arquivoLocacao, char codVeiculo[20], int retiradaDia, int retiradaMes, int retiradaAno, int devolucaoDia, int devolucaoMes, int devolucaoAno)
{
    int indice, validoD;

    validoD = -1;
    tLocacao locacao;

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

    while (!feof(arquivoLocacao) || (validoD == 1))
    {
        indice++;
        if (strcasecmp(locacao.codVeiculo, codVeiculo) == 0)
        {
            int ArquivoRetirada=0, ArquivoDevolucao=0, devolucao=0, retirada=0;
            ArquivoRetirada = converteDate(locacao.dataRetirada.dia, locacao.dataRetirada.mes, locacao.dataRetirada.ano);
            ArquivoDevolucao = converteDate(locacao.dataDevolucao.dia, locacao.dataDevolucao.mes, locacao.dataDevolucao.ano);
            retirada = converteDate(retiradaDia, retiradaMes, retiradaAno);
            devolucao = converteDate(devolucaoDia, devolucaoMes, devolucaoAno);

            validoD = -1;
            printf("Valor arquivo retirada digitada %d",ArquivoRetirada);
            printf("Valor arquivo devolucao digitada %d",ArquivoDevolucao);
            printf("Valor retirada digitada %d",retirada);
            printf("Valor devolucao digitada %d",devolucao);
            // caso entre em um desses o periodo ta errado
            if (ArquivoRetirada>= retirada || ArquivoDevolucao<= retirada){
                validoD = 1;
            }
            if(ArquivoRetirada>= devolucao || ArquivoDevolucao<= devolucao){
                validoD = 1;
            }
            printf("Valor validoD %d",validoD);

        }
        fread(&locacao, sizeof(locacao), 1, arquivoLocacao);
    }
    return validoD;
}

int converteDate(int dia, int mes, int ano)
{
    int date=0;
    date = ((dia * 1000000) +(mes *1000)+ano);
    return date;
}
/*FIM FUN????ES LOCA????O*/


/*FUN????ES DE DAR BAIXA NA LOCA????O*/
void darBaixaLocacao(FILE *arquivoLocacao, FILE *arquivoClientes, FILE *arquivoVeiculos)
{
    tLocacao locacao;
    tVeiculo veiculo;
    tData dataDevolucaoFeita;
    char codigoLocacao[20];
    int diasAtraso, indiceLocacao, indiceVeiculo;
    float valorLocacao, valDiaria,valorTotalSemMulta;

    printf("Digite seu c??digo de cliente, para ver o c??digo da loca????o que deseja dar baixa: ");
    scanf(" %[^\n]", &locacao.codCliente);

    while(localizaCliente(arquivoClientes, locacao.codCliente) == -1)
    {
        printf("\nC??digo de cliente inexistente!");
        printf("\nDigite o c??digo novamente: ");
        scanf(" %[^\n]", &locacao.codCliente);
    }

    listarLocacoes(arquivoLocacao, locacao.codCliente);

    printf("\nDigite o c??digo da locacao que deseja dar baixa: ");
    scanf(" %[^\n]", &locacao.codigoLocacao);

    indiceLocacao = localizaLocacao(arquivoLocacao, locacao.codigoLocacao);
    if(indiceLocacao != -1)
    {
        fseek(arquivoLocacao, sizeof(locacao)*(indiceLocacao), SEEK_SET);
        fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

        imprimirLocacao(arquivoLocacao, locacao.codigoLocacao);

        indiceVeiculo = localizaVeiculo(arquivoVeiculos, locacao.codVeiculo);
        if(indiceVeiculo != -1)
        {
            fseek(arquivoVeiculos, sizeof(veiculo)*(indiceVeiculo), SEEK_SET);
            fread(&veiculo, sizeof(veiculo), 1, arquivoVeiculos);

            printf("\nDigite a data de devolu????o do carro no formato (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &dataDevolucaoFeita.dia, &dataDevolucaoFeita.mes, &dataDevolucaoFeita.ano);

            while(validarData(dataDevolucaoFeita) == -1)
            {
                printf("\nFormato de data inv??lido, digite novamente!");
                printf("\nData de devolu????o do ve??culo no formato (DD/MM/YYYY): ");
                scanf("%d/%d/%d", &dataDevolucaoFeita.dia, &dataDevolucaoFeita.mes, &dataDevolucaoFeita.ano);
            }

            printf("\n\nDias locacao %d/%d/%d", locacao.dataDevolucao.dia, locacao.dataDevolucao.mes, locacao.dataDevolucao.ano);
            printf("\n\nDias locacao %d/%d/%d\n", dataDevolucaoFeita.dia, dataDevolucaoFeita.mes, dataDevolucaoFeita.ano);

            diasAtraso = calcularDiasAtraso(locacao.dataDevolucao, dataDevolucaoFeita);
            valDiaria = veiculo.valorDiaria;

            if(diasAtraso == 0)
                valorLocacao = (float)(valDiaria*locacao.quantDias) + locacao.seguro;
            else
            {
                valorTotalSemMulta = (float)(valDiaria*locacao.quantDias) + locacao.seguro;
                valorLocacao = (float)(valorTotalSemMulta + (valorTotalSemMulta*0,05)) + 30*diasAtraso;
                printf("\nOps, voc?? entregou o ve??culo com %d dias de atraso! :(", diasAtraso);
            }
            printf("\n\nValor Total da Loca????o: %.2f\n", valorLocacao);

            mudarStatusVeiculoParaDisponivel(arquivoVeiculos, veiculo.codigoVeiculo);

            printf("\n\nStatus do ve??culo alterado para conclu??do! \n");
            printf("\nBaixa realizada com sucesso!!!\n");
        }
    }
    else
        printf("\nC??digo da loca????o inexistente!\nSa??ndo...");
}

void imprimirLocacao(FILE * arquivoLocacao, char codigoLocacao[20])
{
    tLocacao locacao;

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

    while (!feof(arquivoLocacao))
    {
        if (strcasecmp(codigoLocacao, locacao.codigoLocacao) == 0)
        {
            printf("\nDados da Loca????o Que Est?? Dando Baixa\n");
            printf("C??digo da locacao: %s\n", locacao.codigoLocacao);
            printf("Data de retirada: %d/%d/%d\n", locacao.dataRetirada.dia, locacao.dataRetirada.mes, locacao.dataRetirada.ano);
            printf("Data de devolu????o: %d/%d/%d\n", locacao.dataDevolucao.dia, locacao.dataDevolucao.mes, locacao.dataDevolucao.ano);
            printf("Valor do seguro: %f\n", locacao.seguro);
            printf("Quantidades de dia que ser??o alugados: %i\n", locacao.quantDias);
            printf("C??digo do cliente: %s\n", locacao.codCliente);
            printf("C??digo do ve??culo: %s\n", locacao.codVeiculo);
        }
        fread(&locacao, sizeof(locacao), 1, arquivoLocacao);
    }
}

int calcularDiasAtraso(tData dataDevolucaoEsperada, tData dataDevolucaoFeita)
{
    int auxDataDevolucaoEsperada, auxDataDevolucaoFeita, diasAtraso;

    dataDevolucaoEsperada.dia = dataDevolucaoEsperada.dia * 1000000;
    dataDevolucaoEsperada.mes = dataDevolucaoEsperada.mes * 10000;
    auxDataDevolucaoEsperada = dataDevolucaoEsperada.dia + dataDevolucaoEsperada.mes + dataDevolucaoEsperada.ano;

    dataDevolucaoFeita.dia = dataDevolucaoFeita.dia * 1000000;
    dataDevolucaoFeita.mes = dataDevolucaoFeita.mes * 10000;
    auxDataDevolucaoFeita = dataDevolucaoFeita.dia + dataDevolucaoFeita.mes + dataDevolucaoFeita.ano;

    if(auxDataDevolucaoFeita > auxDataDevolucaoEsperada)
        diasAtraso = (auxDataDevolucaoFeita - auxDataDevolucaoEsperada)/1000000;
    else
        diasAtraso = 0;

    return diasAtraso;
}

void mudarStatusVeiculoParaDisponivel(FILE *arquivoVeiculos, char codVeiculo[25])
{
    int indiceVeiculo;
    tVeiculo veiculo;

    indiceVeiculo = localizaVeiculo(arquivoVeiculos, codVeiculo);

    if(indiceVeiculo != -1) //SE encontrou o ve??culo
    {
        fseek(arquivoVeiculos,sizeof(veiculo)*(indiceVeiculo),SEEK_SET);
        fread(&veiculo, sizeof(veiculo),1, arquivoVeiculos);

        veiculo.status[indiceVeiculo] = strcpy(veiculo.status,"Disponivel");

        fseek(arquivoVeiculos,sizeof(veiculo)*(indiceVeiculo),SEEK_SET);
        fwrite(&veiculo, sizeof(veiculo),1, arquivoVeiculos);
        fflush(arquivoVeiculos);
    }
}
/*FIM  FUN????ES DE DAR BAIXA NA LOCA????O*/

/*FUN??OES DE CALCULAR PONTOS DE FIDELIDADE DO CLIENTE*/
int calcularPontosFidelidade(FILE *arquivoLocacao, FILE *arquivoClientes, char codCliente[20])
{
    int pontosFidelidade = 0, indice, diasLocacao;

    tLocacao locacao;
    tCliente cliente;

    indice = localizaCliente(arquivoClientes, codCliente);

    while(localizaCliente(arquivoClientes, locacao.codCliente) == -1)
    {
        printf("\nC??digo de cliente inexistente!");
        printf("\nDigite o c??digo novamente: ");
        scanf(" %[^\n]", &locacao.codCliente);
    }

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

    fseek(arquivoClientes,sizeof(cliente)*(indice),SEEK_SET);
    fread(&cliente, sizeof(cliente),1, arquivoClientes);

    while (!feof(arquivoLocacao))
    {
        if (strcasecmp(codCliente, locacao.codCliente) == 0)
        {
            diasLocacao = calcularQtdDiasLocacao(locacao.dataRetirada, locacao.dataDevolucao);
            pontosFidelidade = pontosFidelidade + (10*diasLocacao);
        }
        fread(&locacao, sizeof(locacao), 1, arquivoLocacao);
    }

    return pontosFidelidade;
}
//Pesquisar clientes que atingiram 500 pontos de fidelidade
void buscaClientesAptosAhGanharKit(FILE *arquivoClientes, FILE *arquivoLocacao)
{
    int pontosFidelidade, diasLocacao;

    tLocacao locacao;
    tCliente cliente;

    fseek(arquivoLocacao, 0, SEEK_SET);
    fread(&locacao, sizeof(locacao), 1, arquivoLocacao);

    fseek(arquivoClientes, 0,SEEK_SET);
    fread(&cliente, sizeof(cliente),1, arquivoClientes);

    while(!feof(arquivoClientes)){
        while (!feof(arquivoLocacao))
        {
            if(strcasecmp(locacao.codCliente, cliente.codigoCliente))
            {
                diasLocacao = calcularQtdDiasLocacao(locacao.dataRetirada, locacao.dataDevolucao);
                pontosFidelidade = calcularPontosFidelidade(arquivoLocacao, arquivoClientes, locacao.codCliente);
            }
            if(pontosFidelidade >= 500)
                printf("\nParab??ns o cliente %s!!!! Atingiu a meta de 500 pontos de fideldade e ganhou o kit da locaMias!!!!\n", cliente.codigoCliente, pontosFidelidade);
            pontosFidelidade = 0;
            fread(&locacao, sizeof(locacao), 1, arquivoLocacao);
            fread(&cliente, sizeof(cliente), 1, arquivoClientes);
        }
        fread(&cliente, sizeof(cliente), 1, arquivoClientes);
    }
}

/*
#######################################################
#--------------     Fun????es extra     ----------------#
#######################################################

*/


void alterarDadosCLiente(FILE *arquivoCliente){

    // declarando variaveis
    int posicao, opcao;
    char codigo[20];

    // declarando cliente
    tCliente cliente;

    printf("Diga qual o codigo do cliente para alterar:");
    scanf(" %[^\n]",&codigo);

    // pegando posi????o
    posicao = localizaCliente(arquivoCliente,codigo);

    if(posicao!=-1)//localizou cliente
    {
        fseek(arquivoCliente,sizeof(cliente)*(posicao),SEEK_SET);
        fread(&cliente, sizeof(cliente),1,arquivoCliente);
        printf("Codigo do cliente atual - %s, nome - %s,", cliente.codigoCliente, cliente.nomeCliente);
        printf("\n----------------------------------------------------------------");
        printf("\nDigite 1 para alterar nome 2 para alterar telefone:");
        scanf("%d", &opcao);
        while(opcao >2 || opcao <0){
            printf("\nValor de entrada errado");
            printf("\nDigite 1 para alterar nome 2 para alterar telefone e 0 para sair. ");
            scanf("%d", &opcao);

        }
         switch (opcao)
        {
            case 1:
                printf("\nNovo Nome:");
                scanf(" %[^\n]",&cliente.nomeCliente);
                break;
            case 2:
                printf("\nNovo telefone cliente:");
                scanf(" %[^\n]",&cliente.telefoneCliente);
                break;

        }
            fseek(arquivoCliente, sizeof(cliente)*(posicao),SEEK_SET);
            fwrite(&cliente, sizeof(cliente),1,arquivoCliente);
            fflush(arquivoCliente);
    }

}

/* Verifica se a placa segue as diretrizes para ela ser v??lida */
int validarPlaca(char placa[]) {
    for(int i = 0; i < 3; i++)
    {
        if(!(placa[i] >= 65 && placa[i] <= 90) && !(placa[i] >= 97 && placa[i] <= 122)) return 1;
    }

    for(int i = 3; i < 7; i++) if(!(placa[i] >= 48 && placa[i] <= 57)) return 1;

    return 0;
}

/*FIM FUN????ES DE CALCULAR PONTOS DE FIDELIDADE DO CLIENTE*/
