#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>


//!------------------Header---------------------
//*Deseja-se cadastrar os clientes, os funcionários e as estadias do hotel. As informações que devem
//ser cadastradas são: Clientes, funconários, estadias, quartos.

struct CLIENTE
{
    int codigo, telefone;
    char nome[30], endereco[50];
    
};

//cargos: recepcionista, auxiliar de limpeza, garçom, gerente.
struct FUNCIONARIO
{
    int codigo, telefone;
    char nome[30], cargo[50];
    float salario;
};


//ESTADIA = codigo da estadia, data de entrada, data de saída, quantidade de diárias, codigo
//do cliente, numero do quarto        
struct ESTADIA
{
    int codigo, quantidade_diarias, codigo_cliente, numero_quarto;
    char data_entrada[10], data_saida[10];
};

struct QUARTO
{
    int numero_do_quarto, quantidade_de_hospedes;
    float valor_diaria;
    int status;
};

//




//!------------------Funções-----------------------


//?Função para cadastrar um cliente
/*Implemente uma função para cadastrar um cliente. Essa função deve garantir que não
haverá mais de um cliente com o mesmo codigo. Se quiser pode gerar o codigo
automaticamente*/
void cadastrar_cliente(struct CLIENTE *cliente, int *quantidade_clientes)
{
    printf("Digite o codigo do cliente: ");
    scanf("%d", &cliente[*quantidade_clientes].codigo);
    getchar(); // Limpa o buffer do stdin

    printf("Digite o nome do cliente: ");
    fgets(cliente[*quantidade_clientes].nome, sizeof(cliente[*quantidade_clientes].nome), stdin);
    cliente[*quantidade_clientes].nome[strcspn(cliente[*quantidade_clientes].nome, "\n")] = 0; // Remove o '\n' do final

    printf("Digite o endereco do cliente: ");
    fgets(cliente[*quantidade_clientes].endereco, sizeof(cliente[*quantidade_clientes].endereco), stdin);
    cliente[*quantidade_clientes].endereco[strcspn(cliente[*quantidade_clientes].endereco, "\n")] = 0; // Remove o '\n' do final

    printf("Digite o telefone do cliente: ");
    scanf("%d", &cliente[*quantidade_clientes].telefone);

    *quantidade_clientes += 1;
}
//?Função para cadastrar um funcionário
/*Implemente uma função para cadastrar um funcionário. Essa função deve garantir que
não haverá mais de um funcionário cadastrado com o mesmo codigo. Se quiser pode
gerar o codigo automaticamente*/

void cadastrar_funcionario(struct FUNCIONARIO *funcionario, int *quantidade_funcionarios)
{
    printf("Digite o codigo do funcionário: ");
    scanf("%d", &funcionario[*quantidade_funcionarios].codigo);
    printf("Digite o nome do funcionário: ");
    scanf("%s", funcionario[*quantidade_funcionarios].nome);
    printf("Digite o cargo do funcionário: ");
    scanf("%s", funcionario[*quantidade_funcionarios].cargo);
    printf("Digite o salario do funcionário: ");
    scanf("%f", &funcionario[*quantidade_funcionarios].salario);
    printf("Digite o telefone do funcionário: ");
    scanf("%d", &funcionario[*quantidade_funcionarios].telefone);
    *quantidade_funcionarios += 1;
}

//?Função para cadastrar um quarto
/*Implemente uma função para cadastrar um quarto. Essa função deve garantir que não
haverá mais de um quarto cadastrado com o mesmo numero*/
void cadastrar_quarto(struct QUARTO *quarto, int *quantidade_quartos)
{
    printf("Digite o numero do quarto: ");
    scanf("%d", &quarto[*quantidade_quartos].numero_do_quarto);
    printf("Digite a quantidade de hóspedes: ");
    scanf("%d", &quarto[*quantidade_quartos].quantidade_de_hospedes);
    printf("Digite o valor da diária: ");
    scanf("%f", &quarto[*quantidade_quartos].valor_diaria);
    quarto[*quantidade_quartos].status = 0;//0 = disponível, 1 = ocupado
    *quantidade_quartos += 1;
}

//?Função para cadastrar uma estadia
/*Implemente uma função que cadastre uma estadia. Para cadastrar a estadia, o sistema
deve receber do usuário o codigo do cliente que deseja se hospedar, a quantidade de
hóspedes, a data de entrada e a data de saída. A partir disso, o sistema deve encontrar um
quarto que esteja disponível para a quantidade de hóspedes desejada. Além disso, a
quantidade de diárias deverá ser calculada com base nas datas de entrada e saída.*/

#include <time.h>

// Função para converter uma string de data "dd-mm-yyyy" para struct tm
void str_to_tm(const char *str, struct tm *tm) {
    sscanf(str, "%d-%d-%d", &tm->tm_mday, &tm->tm_mon, &tm->tm_year);
    tm->tm_mon -= 1;  // Ajusta o mês (0-11)
    tm->tm_year -= 1900;  // Ajusta o ano (desde 1900)
}

// Função para calcular a diferença em dias entre duas datas
int calcular_dias(const char *data_entrada, const char *data_saida) {
    struct tm tm_entrada = {0};
    struct tm tm_saida = {0};
    time_t t_entrada, t_saida;
    
    str_to_tm(data_entrada, &tm_entrada);
    str_to_tm(data_saida, &tm_saida);

    t_entrada = mktime(&tm_entrada);
    t_saida = mktime(&tm_saida);

    return (int)difftime(t_saida, t_entrada) / (60 * 60 * 24);
}

void cadastrar_estadia(struct ESTADIA *estadia, struct QUARTO *quarto, struct CLIENTE *cliente, int *quantidade_estadias, int *quantidade_quartos, int *quantidade_clientes)
{
    int *codigo, codigo_cliente, quantidade_hospedes, i, j;
    char data_entrada[11], data_saida[11];
     printf("Digite o codigo da estadia: ");
    scanf("%d", &codigo);
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo_cliente);
    printf("Digite a quantidade de hóspedes: ");
    scanf("%d", &quantidade_hospedes);
    printf("Digite a data de entrada (dd-mm-yyyy): ");
    scanf("%s", data_entrada);
    printf("Digite a data de saída (dd-mm-yyyy): ");
    scanf("%s", data_saida);

    for (i = 0; i < *quantidade_clientes; i++)
    {
        if (cliente[i].codigo == codigo_cliente)
        {
            for (j = 0; j < *quantidade_quartos; j++)
            {
                if (quarto[j].quantidade_de_hospedes >= quantidade_hospedes && quarto[j].status == 0)
                {
                    estadia[*quantidade_estadias].codigo = *quantidade_estadias;
                    strcpy(estadia[*quantidade_estadias].data_entrada, data_entrada);
                    strcpy(estadia[*quantidade_estadias].data_saida, data_saida);
                    estadia[*quantidade_estadias].quantidade_diarias = calcular_dias(data_entrada, data_saida);
                    estadia[*quantidade_estadias].codigo_cliente = cliente[i].codigo;
                    estadia[*quantidade_estadias].numero_quarto = quarto[j].numero_do_quarto;
                    quarto[j].status = 1;
                    *quantidade_estadias += 1;
                    break;
                }
            }
            break;
        }
    }
}

// Funções para salvar e carregar dados de arquivos
void salvar_dados(const char* filename, void* dados, size_t size, int quantidade) {
    FILE* file = fopen(filename, "wb");//wb = write binary, indica a abertura de um arquivo binário para escrita
    if (file) {
        fwrite(dados, size, quantidade, file);
        fclose(file);   
    } else {
        perror("Erro ao abrir arquivo para escrita");
    }
}

int carregar_dados(const char* filename, void* dados, size_t size) {
    FILE* file = fopen(filename, "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        int quantidade = ftell(file) / size;
        fseek(file, 0, SEEK_SET);
        fread(dados, size, quantidade, file);
        fclose(file);
        return quantidade;
    } else {
        return 0;
    }
}




//?Função que dê baixa em uma estadia
/*Implemente uma função que dê baixa em uma determinada estadia, calcule e mostre o
valor total a ser pago por um determinado cliente. Lembre-se de alterar o status do quarto
para desocupado.*/
void baixa_estadia(struct ESTADIA *estadia, struct QUARTO *quarto, int *quantidade_estadias, int *quantidade_quartos)
{
    int codigo_estadia, i, j;
    float valor_total;
    printf("Digite o codigo da estadia: ");
    scanf("%d", &codigo_estadia);
    for (i = 0; i < *quantidade_estadias; i++)
    {
        if (estadia[i].codigo == codigo_estadia)
        {
            for (j = 0; j < *quantidade_quartos; j++)
            {
                if (quarto[j].numero_do_quarto == estadia[i].numero_quarto)
                {
                    quarto[j].status = 0;
                    valor_total = estadia[i].quantidade_diarias * quarto[j].valor_diaria;
                    printf("O valor total a ser pago é: %.2f\n", valor_total);
                    break;
                }
            }
            break;
        }
    }
}

//?Função para pesquisar clientes ou funcionários
/*Implemente funções para realizar pesquisas tanto por clientes quanto por funcionários, ou
seja, digitando o nome ou codigo apresenta na tela todas as informações do cliente ou
funcionário correspondente.*/

void pesquisar_cliente_funcionario(struct CLIENTE *cliente, int quantidade_clientes, struct FUNCIONARIO *funcionario, int quantidade_funcionarios)
{
    int i, codigo;
    char nome[30];
    printf("Digite o codigo do cliente ou funcionário: ");
    scanf("%d", &codigo);
    for (i = 0; i < quantidade_clientes; i++)
    {
        if (cliente[i].codigo == codigo)
        {
            printf("\ncodigo: %d\n", cliente[i].codigo);
            printf("Nome: %s\n", cliente[i].nome);
            printf("endereco: %s\n", cliente[i].endereco);
            printf("Telefone: %d\n\n", cliente[i].telefone);
            break;
        }
    }
    for (i = 0; i < quantidade_funcionarios; i++)
    {
        if (funcionario[i].codigo == codigo)
        {
            printf("codigo: %d\n", funcionario[i].codigo);
            printf("Nome: %s\n", funcionario[i].nome);
            printf("Cargo: %s\n", funcionario[i].cargo);
            printf("salario: %.2f\n", funcionario[i].salario);
            printf("Telefone: %d\n", funcionario[i].telefone);
            break;
        }
    }
}

//?Função para mostrar todas as estadias de determinado cliente
/*Implemente uma função que mostre na tela todas as estadias de um determinado cliente
(a pesquisa deve se basear no nome ou codigo do cliente).*/

void mostrar_estadias_cliente(struct ESTADIA *estadia, struct CLIENTE *cliente, int quantidade_estadias, int quantidade_clientes)
{
    int i, j, codigo;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);
    for (i = 0; i < quantidade_clientes; i++)
    {
        if (cliente[i].codigo == codigo)
        {
            for (j = 0; j < quantidade_estadias; j++)
            {
                if (estadia[j].codigo_cliente == codigo)
                {
                    printf("codigo da estadia: %d\n", estadia[j].codigo);
                    printf("Data de entrada: %s\n", estadia[j].data_entrada);
                    printf("Data de saída: %s\n", estadia[j].data_saida);
                    printf("Quantidade de diárias: %d\n", estadia[j].quantidade_diarias);
                    printf("numero do quarto: %d\n", estadia[j].numero_quarto);
                }
            }
            break;
        }
    }
}

//?Função para calcular pontos de fidelidade
/*Implemente uma função que calcule a quantidade de pontos de fidelidade de um cliente.
Para cada diária no hotel, o cliente ganhará 10 pontos no programa de fidelidade.
Lembre-se que é possível ter mais de uma estadia para um mesmo cliente.*/
void calcular_pontos_fidelidade(struct ESTADIA *estadia, struct CLIENTE *cliente, int quantidade_estadias, int quantidade_clientes)
{
    int i, j, codigo, pontos = 0;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);
    for (i = 0; i < quantidade_clientes; i++)
    {
        if (cliente[i].codigo == codigo)
        {
            for (j = 0; j < quantidade_estadias; j++)
            {
                if (estadia[j].codigo_cliente == codigo)
                {
                    pontos += estadia[j].quantidade_diarias * 10;
                }
            }
            printf("O cliente %s tem %d pontos de fidelidade\n", cliente[i].nome, pontos);
            break;
        }
    }
}

//!------------------Main---------------------
/*implemente uma função main() que teste o sistema acima. A função main() deve
exibir um menu na tela com as opções de cadastrar um cliente, um funcionário, um quarto ou
uma estadia. Além disso, permitir realizar as pesquisas e dar baixa em estadias. Este menu deve ficar em loop até o usuário selecionar a opção SAIR. Além disso, todas as informações deverão
ser persistidas/armazenadas em arquivos binários (em estruturas heterogêneas). Portanto,
deverá ser feita leitura e escrita em arquivos. Utilize bibliotecas para organizar os módulos
(funções e procedimentos) do software.
*/


int main() {

   setlocale(LC_ALL, "Portuguese_Brazil.1252");


    struct CLIENTE clientes[100];
    struct FUNCIONARIO funcionarios[100];
    struct ESTADIA estadias[100];
    struct QUARTO quartos[100];

    int quantidade_clientes = carregar_dados("clientes.dat", clientes, sizeof(struct CLIENTE));
    int quantidade_funcionarios = carregar_dados("funcionarios.dat", funcionarios, sizeof(struct FUNCIONARIO));
    int quantidade_estadias = carregar_dados("estadias.dat", estadias, sizeof(struct ESTADIA));
    int quantidade_quartos = carregar_dados("quartos.dat", quartos, sizeof(struct QUARTO));

    int opcao;

    do {
        printf("Menu:\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionário\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia\n");
        printf("5. Dar Baixa em Estadia\n");
        printf("6. Pesquisar Cliente/Funcionário\n");
        printf("7. Mostrar Estadias de Cliente\n");
        printf("8. Calcular Pontos de Fidelidade\n");
        printf("9. Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cliente(clientes, &quantidade_clientes);
                salvar_dados("clientes.dat", clientes, sizeof(struct CLIENTE), quantidade_clientes);
                break;
            case 2:
                cadastrar_funcionario(funcionarios, &quantidade_funcionarios);
                salvar_dados("funcionarios.dat", funcionarios, sizeof(struct FUNCIONARIO), quantidade_funcionarios);
                break;
            case 3:
                cadastrar_quarto(quartos, &quantidade_quartos);
                salvar_dados("quartos.dat", quartos, sizeof(struct QUARTO), quantidade_quartos);
                break;
            case 4:
                cadastrar_estadia(estadias, quartos, clientes, &quantidade_estadias, &quantidade_quartos, &quantidade_clientes);
                salvar_dados("estadias.dat", estadias, sizeof(struct ESTADIA), quantidade_estadias);
                salvar_dados("quartos.dat", quartos, sizeof(struct QUARTO), quantidade_quartos);
                break;
            case 5:
                baixa_estadia(estadias, quartos, &quantidade_estadias, &quantidade_quartos);
                salvar_dados("estadias.dat", estadias, sizeof(struct ESTADIA), quantidade_estadias);
                salvar_dados("quartos.dat", quartos, sizeof(struct QUARTO), quantidade_quartos);
                break;
            case 6:
                pesquisar_cliente_funcionario(clientes, quantidade_clientes, funcionarios, quantidade_funcionarios);
                break;
            case 7:
                mostrar_estadias_cliente(estadias, clientes, quantidade_estadias, quantidade_clientes);
                break;
            case 8:
                calcular_pontos_fidelidade(estadias, clientes, quantidade_estadias, quantidade_clientes);
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 9);

    return 0;
}

