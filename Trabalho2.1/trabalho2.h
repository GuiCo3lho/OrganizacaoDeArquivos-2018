#define MAX_KEYS 3
#include <stdbool.h>

typedef struct {
    char chavePrimaria[8];//nome + matricula (8)
    int byteoffset;
    char nome[41];
    char matricula[5];
    char curso[2];
    char turma;
    int teste;
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    int isLeaf;
    int numKeys;
    TipoRegistro chaves[MAX_KEYS];
    TipoApontador kids[MAX_KEYS+1];
} TipoPagina;
/*Funcoes da bTree*/
void btImprime(TipoApontador);
void btImprimeI(TipoApontador, int );
void btInsere(TipoRegistro , TipoApontador *);
void btIns(TipoRegistro , TipoApontador , bool *,
          TipoRegistro *, TipoApontador * );
void btInsertInNode(TipoApontador , TipoRegistro, TipoApontador);
void btPesquisa(TipoRegistro*,TipoApontador);
void btInicializa(TipoApontador *);
/*Funcoes para manipulacoes de arquivos*/
void CriarIndPri(void);
int countregisters(FILE*);



/*
TipoApontador btCreate()
{
    TipoApontador b;
    b = malloc(sizeof(TipoPagina));
    assert(b);
    b->isLeaf = 1;
    b->numKeys = 0;
    return b;
}

void btInicializa(TipoApontador * Dicionario)
{
    *Dicionario = NULL;
}

void Pesquisa(TipoApontador Ap,TipoRegistro * x)
{
    int i;
    if (Ap == NULL)
    {
      printf("Nao existem paginas na arvore");
      return;
    }
    while(Ap->numKeys > i && x->Chave > Ap->r[i-1].Chave) i++;
    if( x->chave == Ap->r[i-1].Chave)
    {
      printf("Chave encontrada na arvore!");
      return;
    }

    if(x->Chave < Ap->r[i-1].Chave)
      Pesquisa(x, Ap->p[i-1]);
      else
      Pesquisa(x,Ap->p[i]);
  }

void InsertInNode(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir)
{
  int

}
*/
