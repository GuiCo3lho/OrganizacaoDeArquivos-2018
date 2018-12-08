#define MAX_KEYS (3)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>
#include <stdbool.h>
#define FALSE 0
#define TRUE 1



void btInicializa(TipoApontador * Dicionario)
{
    *Dicionario = NULL;
}

void btPesquisa(TipoRegistro * x,TipoApontador Ap)
{
    short cmp;
    int i = 1;
    if (Ap == NULL)
    {
      printf("Nao existem paginas na arvore");
      return;
    }
    //cmp = strcmp(x->Chave,Ap->chaves[i-1].Chave);
    while(Ap->numKeys > i && x->Chave > Ap->chaves[i-1].Chave) i++;

    if(x->Chave == Ap->chaves[i-1].Chave)
    {
      *x = Ap->chaves[i-1];
      printf("Chave encontrada na arvore!");
      return;
    }

    if(x->Chave < Ap->chaves[i-1].Chave)
      btPesquisa(x, Ap->kids[i-1]);
      else
      btPesquisa(x,Ap->kids[i]);
  }

void btInsertInNode(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir)
{
    bool PosNotFound;
    int k;
    short cmp;
    k = Ap->numKeys; PosNotFound = (k > 0);
    while (PosNotFound)
    {
      //cmp = strcmp(Reg.Chave,Ap->chaves[k-1].Chave);
      if (Reg.Chave >= Ap->chaves[k-1].Chave) //Reg.Chave maior que chave do No arvores
      {
        PosNotFound = FALSE;
        break;
      }
      Ap->chaves[k] = Ap->chaves[k-1];
      Ap->kids[k+1] = Ap->kids[k];
      k--;
      if (k < 1) PosNotFound = FALSE;
    }
    Ap->chaves[k] = Reg;
    Ap->kids[k+1] = ApDir;
    Ap->numKeys++;
}

void btIns(TipoRegistro Reg, TipoApontador Ap, bool * Cresceu,
          TipoRegistro * RegRetorno, TipoApontador * ApRetorno)
{

    //printf("OI!\n");

    int i = 1;
    int j;
    short cmp;
    TipoApontador ApTemp;
    if (Ap == NULL)
    {
      *Cresceu = TRUE;
      (*RegRetorno) = Reg;
      (*ApRetorno) = NULL;
      return;
    }

    //cmp = strcmp(Reg.Chave,Ap->chaves[i-1].Chave);
    while(i<Ap->numKeys && Reg.Chave > Ap->chaves[i-1].Chave) i++;
    //cmp = strcmp(Reg.Chave,Ap->chaves[i-1].Chave);
    if(Reg.Chave == Ap->chaves[i-1].Chave)
    {
      printf("Erro: Registro ja existe na arvore bTree");
      *Cresceu = FALSE;
      return;
    }
    if(Reg.Chave < Ap->chaves[i-1].Chave) i--;
    btIns(Reg,Ap->kids[i],Cresceu,RegRetorno,ApRetorno);
    if(!*Cresceu) return;
    if(Ap->numKeys < MAX_KEYS) //Pagina com espaço
    {
      btInsertInNode(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = FALSE;
      return;
    }
    //Overflow da pagina => Divisao
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->numKeys = 0; ApTemp->kids[0] = NULL;
    if(i < (MAX_KEYS/2)+1)
    {
      btInsertInNode(ApTemp,Ap->chaves[MAX_KEYS-1], Ap->kids[MAX_KEYS]);
      Ap->numKeys--;
      btInsertInNode(Ap, *RegRetorno, *ApRetorno);//ApTemp
    }
    else btInsertInNode(ApTemp, *RegRetorno, *ApRetorno);
    for(j = (MAX_KEYS/2) + 2; j <= MAX_KEYS; j++)
    {
        btInsertInNode(ApTemp,Ap->chaves[j-1],Ap->kids[j]);
    }
    Ap->numKeys = MAX_KEYS/2;
    ApTemp->kids[0] = Ap->kids[(MAX_KEYS/2) + 1];
    *RegRetorno = Ap->chaves[MAX_KEYS/2];
    *ApRetorno = ApTemp;
}

void btInsere(TipoRegistro Reg, TipoApontador *Ap)
{


    bool Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    btIns(Reg,*Ap,&Cresceu,&RegRetorno,&ApRetorno);
    if(Cresceu) //Arvore cresce na altura pela raiz
    {
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->numKeys = 1;
        ApTemp->chaves[0] = RegRetorno;
        ApTemp->kids[1] = ApRetorno;
        ApTemp->kids[0] = *Ap; *Ap = ApTemp;
    }


}

void btImprimeI(TipoApontador p, int nivel)
{
  int i;
  if(p == NULL)
  {
    return;
  }

  printf("Nivel %d :",nivel);
  for(i = 0; i<p->numKeys; i++)
      printf("%s ", p->chaves[i].chavePrimaria);
  putchar('\n');
  nivel++;
  for(i = 0; i<= p->numKeys; i++)
      btImprimeI(p->kids[i], nivel);
}

void btImprime(TipoApontador p)
{
  int n = 0; btImprimeI(p,n);
}























/*
ApontadorbTree btCreate(int ordem)
{
  ApontadorbTree b;
  b = malloc(sizeof(btNode));
  assert(b);
  b->isLeaf = 1;
  b->numKeys = 0;
  return b;
}
btInsertInNode(ApTemp, *RegRetorno, *ApRetorno);
void btDestroy(bTree b)
{
  int i;
  if(b->isLeaf != 1)
  {
    for(i = 0; i < b->numKeys + 1;i++){
        btDestroy(b->kids[i]);
    }
  }
  free(b);
}

static int searchKey(int n,)

btSearch(bTree b, char * chave)
{
  if(b->numKeys == 0)

    return 0;
  }
  TipoApontador btCreate()
  {
      TipoApontador b;
      b = malloc(sizeof(TipoPagina));
      assert(b);
      b->isLeaf = 1;
      b->numKeys = 0;
      return b;
  }

  */
