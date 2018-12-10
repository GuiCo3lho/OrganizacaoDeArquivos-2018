#ifndef TRABALHO2_H_
#define TRABALHO2_H_

#define MAX_KEYS (3)
#include <stdbool.h>
#include <stdio.h>

typedef int TipoChave;

typedef struct 
{
    TipoChave Chave;
    char Registro[55];
    char chavePrimaria[8];//nome + matricula (8)
    int byteoffset;
    char nome[40];
    int matricula;
    char curso[3];
    char turma;
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina 
{
    int isLeaf;
    int numKeys;
    TipoRegistro chaves[MAX_KEYS];
    TipoApontador kids[MAX_KEYS+1];
} TipoPagina;

/*Funcoes da bTree*/
void btInicializa(TipoApontador*);
void btPesquisa(TipoRegistro*,TipoApontador, int*, int*);
void btInsertInNode(TipoApontador , TipoRegistro, TipoApontador);
void btIns(TipoRegistro , TipoApontador , bool*, TipoRegistro*, TipoApontador* );
void btInsere(TipoRegistro , TipoApontador*);
void btImprimeI(TipoApontador, int );
void btImprime(TipoApontador);
void btReconstitui(TipoApontador , TipoApontador , int , short *);
void btAntecessor(TipoApontador , int , TipoApontador , short *);
void btRet(TipoChave , TipoApontador *, short *);
void btRetira(TipoChave , TipoApontador *);
void btGravaI(TipoApontador, int, FILE *);
void btGrava(TipoApontador, FILE*);
void btGravarIndice(TipoApontador);
void btTipoRegistroI(TipoApontador,int);
void btTipoRegistro(TipoApontador);
void btBuscarRegistro(TipoApontador);
void IncluirRegistro(void);
void btRemoverRegistro(TipoApontador);

/*Funcoes para manipulacoes de arquivos*/
void CriarIndPri(TipoRegistro*, TipoApontador*);
int countregisters(FILE*);
void coletaRegistro(TipoRegistro*,FILE*);
void imprimeRegistro(TipoRegistro*);
void imprimirRegistro(TipoRegistro);
void imprimirDados(TipoRegistro);
int ChaveNumerica(char []);
int menu(void);


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
#endif /* TRABALHO2_H_ */