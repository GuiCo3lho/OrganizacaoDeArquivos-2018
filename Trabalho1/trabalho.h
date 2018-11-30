
  typedef struct t_elemento
  {
    int matricula;
    char nome[41];
    char chavePrimaria[31];
    int op;
    char curso[3];
    char turma;
    int pos;
    struct t_elemento * prox;
  } Lista;

  typedef struct Aponta
  {
      Lista * inicio;
      Lista * fim;
      int tamanho;
  }Aponta;


//FUNCOES DO PROGRAMA//
int opcoes(void);
//void InserirPilha(Pilha *, int , int)
//int RemoverPilha(Pilha *);
void OpcaoEscolhida(int opcao, Aponta * , Aponta * ,FILE * , FILE *);
Lista * AlocaLista(int , char * , int , char * ,int , char );
void InserirOrdenado(Aponta *, int, char *, char *, char , int OP, int numArq, int posicao, char * chave_primaria);
void MostraLista(Aponta *,int );
int vazia(Aponta *);
void liberarLista(Lista **p);
Aponta * AlocCriaAPonta();
//Pilha * criarPilha();
void criarindicep(FILE*,char*);
int countregisters(FILE*);
void criarinds(void);
void criarindicesec(void);
