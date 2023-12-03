typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

typedef struct Cliente
{
    int cnh;
    char nome[100];
    int telefone;
    struct Cliente *prox;
} Cliente;

typedef struct Veiculo
{
    char placa[100];
    char marca[100];
    char modelo[100];
    int ano;
    int kilometragem;
    float diaria;
    bool disp;
    struct Veiculo *prox;
} Veiculo;

typedef struct Locacao
{
    Veiculo *v;
    Cliente *c;
    Date retirada;
    Date devolucao;
    float valor;
    struct Locacao *prox;
} Locacao;

//Funções relacionadas com o veículo
Veiculo *lst_veiculo_cria(void);
Veiculo *lst_veiculo_insere(Veiculo *l, char placa[], char marca[], char modelo[], int ano, int kilometragem, float diaria);
Veiculo *adicionar_veiculo(Veiculo *l);
Veiculo *busca_veiculo(Veiculo *l, char placa[]);
void listar_veiculos(Veiculo *l);
void devolver_veiculo(Veiculo *veiculo);

//Funcões relacionadas com o cliente
Cliente *lst_cliente_cria(void);
Cliente *lst_cliente_insere(Cliente *l, int cnh, char nome[], int telefone);
Cliente *adicionar_cliente(Cliente *l);
Cliente *busca_cliente(Cliente *l, int cnh);
void listar_clientes(Cliente *l);

//Funções relacionadas com a locação
Locacao *lst_locacao_cria(void);
Locacao *lst_locacao_insere(Locacao *l, Veiculo *v, Cliente *c, Date retirada, Date devolucao, float valor);
Locacao *busca_na_locacao_veiculo(Locacao *locacao, Veiculo *veiculo);
bool verificar_disponibilidade(Locacao *locacao, Veiculo *veiculo, Date retirada, Date devolucao);
Locacao *adicionar_locacao(Locacao *locacao, Cliente *cliente, Veiculo *veiculo);
void listar_locacoes(Locacao *l);

//Funções relacionadas com o relatório
void listar_locacoes_ativas(Locacao *l);
void listar_locacao_cliente(Locacao *l);
void faturamento(Locacao *l);
void listar_mais_rodados(Veiculo *veiculo);
void listar_disponiveis(Veiculo *veiculo);
void relatorios(Locacao *locacao, Cliente *cliente, Veiculo *veiculo);