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

void btPesquisa(TipoRegistro * x,TipoApontador Ap,int *seek,int * ver)
{

    (*seek)++;
    short cmp;
    int i = 1;
    if (Ap == NULL)
    {
      printf("Nao existem paginas na arvore\n");
      *ver = 0;
      return;
    }
    //cmp = strcmp(x->Chave,Ap->chaves[i-1].Chave);
    while(Ap->numKeys > i && x->Chave > Ap->chaves[i-1].Chave) i++;

    if(x->Chave == Ap->chaves[i-1].Chave)
    {
        *x = Ap->chaves[i-1];
        printf("Chave encontrada na arvore!\n");
        *ver = 1;
        printf("A%d\n",*ver);
        return;
    }

    if(x->Chave < Ap->chaves[i-1].Chave)
    {
        if(Ap->kids[i-1] == NULL)
        {
          printf("Chave nao encontrada\n");
          *ver = 0;
          return;
        }
        else
          btPesquisa(x, Ap->kids[i-1],seek,ver);
    }

    if(x->Chave > Ap->chaves[i-1].Chave)
     {
        if(Ap->kids[i] == NULL)
        {
          printf("Chave nao encontrada\n");
          *ver = 0;
          return;
        }
        else
          btPesquisa(x, Ap->kids[i],seek,ver);
     }

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
      printf("Erro: Registro ja existe na arvore bTree\n");
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

void btReconstitui(TipoApontador ApPag, TipoApontador ApPai,
                 int PosPai, short *Diminuiu)
{
    TipoPagina *Aux;  long DispAux, j;
    if (PosPai < ApPai->numKeys)  /* Aux = TipoPaginumKeysa a direita de ApPag */
    { Aux = ApPai->kids[PosPai+1];  DispAux = (Aux->numKeys - (MAX_KEYS/2)+1) / 2;
      ApPag->chaves[ApPag->numKeys] = ApPai->chaves[PosPai];
      ApPag->kids[ApPag->numKeys + 1] = Aux->kids[0];  ApPag->numKeys++;
      if (DispAux > 0)  /* Existe folga: transfere de Aux para ApPag */
      { for (j = 1; j < DispAux; j++)
          btInsertInNode(ApPag, Aux->chaves[j-1], Aux->kids[j]);
        ApPai->chaves[PosPai] = Aux->chaves[DispAux-1];  Aux->numKeys -= DispAux;
        for (j = 0; j < Aux->numKeys; j++) Aux->chaves[j] = Aux->chaves[j + DispAux];
        for (j = 0; j <= Aux->numKeys; j++) Aux->kids[j] = Aux->kids[j + DispAux];
        *Diminuiu = FALSE;
      }
      else /* Fusao: intercala Aux em ApPag e libera Aux */
        { for (j = 1; j <= (MAX_KEYS/2); j++)
            btInsertInNode(ApPag, Aux->chaves[j-1], Aux->kids[j]);
          free(Aux);
          for (j = PosPai + 1; j < ApPai->numKeys; j++)
            { ApPai->chaves[j-1] = ApPai->chaves[j];
  	    ApPai->kids[j] = ApPai->kids[j+1];
  	  }
          ApPai->numKeys--;
          if (ApPai->numKeys >= (MAX_KEYS/2)) *Diminuiu = FALSE;
        }
    }
    else /* Aux = TipoPagina a esquerda de ApPag */
      { Aux = ApPai->kids[PosPai-1]; DispAux = (Aux->numKeys - (MAX_KEYS/2)+1) / 2;
        for (j = ApPag->numKeys; j >= 1; j--) ApPag->chaves[j] = ApPag->chaves[j-1];
        ApPag->chaves[0] = ApPai->chaves[PosPai-1];
        for (j = ApPag->numKeys; j >= 0; j--) ApPag->kids[j+1] = ApPag->kids[j];
        ApPag->numKeys++;
        if (DispAux > 0) /* Existe folga: transf. de Aux para ApPag */
        { for (j = 1; j < DispAux; j++)
            btInsertInNode(ApPag, Aux->chaves[Aux->numKeys - j],
  	                 Aux->kids[Aux->numKeys - j + 1]);
          ApPag->kids[0] = Aux->kids[Aux->numKeys - DispAux + 1];
          ApPai->chaves[PosPai-1] = Aux->chaves[Aux->numKeys - DispAux];
          Aux->numKeys -= DispAux;  *Diminuiu = FALSE;
        }
        else /* Fusao: intercala ApPag em Aux e libera ApPag */
          { for (j = 1; j <= (MAX_KEYS/2); j++)
              btInsertInNode(Aux, ApPag->chaves[j-1], ApPag->kids[j]);
            free(ApPag);  ApPai->numKeys--;
            if (ApPai->numKeys >= (MAX_KEYS/2))  *Diminuiu = FALSE;
          }
      }
}

void btAntecessor(TipoApontador Ap, int Ind,
                TipoApontador ApPai, short *Diminuiu)
{
   if (ApPai->kids[ApPai->numKeys] != NULL)
  {
    btAntecessor(Ap, Ind, ApPai->kids[ApPai->numKeys], Diminuiu);
    if (*Diminuiu)
      btReconstitui(ApPai->kids[ApPai->numKeys], ApPai, (long)ApPai->numKeys, Diminuiu);
    return;
  }
  Ap->chaves[Ind-1] = ApPai->chaves[ApPai->numKeys - 1];
  ApPai->numKeys--;  *Diminuiu = (ApPai->numKeys < (MAX_KEYS/2));
}

void btRet(TipoChave Ch, TipoApontador *Ap, short *Diminuiu)
{
    long j, Ind = 1;
    TipoApontador Pag;
    if (*Ap == NULL)
    { printf("Erro: registro nao esta na arvore\n"); *Diminuiu = FALSE;
      return;
    }
    Pag = *Ap;
    while (Ind < Pag->numKeys && Ch > Pag->chaves[Ind-1].Chave) Ind++;
    if (Ch == Pag->chaves[Ind-1].Chave)
    { if (Pag->kids[Ind-1] == NULL)   /* TipoPagina folha */
      { Pag->numKeys--;
        *Diminuiu = (Pag->numKeys < (MAX_KEYS/2));
        for (j = Ind; j <= Pag->numKeys; j++)
          { Pag->chaves[j-1] = Pag->chaves[j];  Pag->kids[j] = Pag->kids[j+1]; }
        return;
      }
      /* TipoPagina nao e folha: trocar com antecessor */
      btAntecessor(*Ap, Ind, Pag->kids[Ind-1], Diminuiu);
      if (*Diminuiu)
      btReconstitui(Pag->kids[Ind-1], *Ap, Ind - 1, Diminuiu);
      return;
    }
    if (Ch > Pag->chaves[Ind-1].Chave) Ind++;
    btRet(Ch, &Pag->kids[Ind-1], Diminuiu);
    if (*Diminuiu) btReconstitui(Pag->kids[Ind-1], *Ap, Ind - 1, Diminuiu);
}

void btRetira(TipoChave Ch, TipoApontador *Ap)
{
    short Diminuiu;
    TipoApontador Aux;
    btRet(Ch, Ap, &Diminuiu);
    if (Diminuiu && (*Ap)->numKeys == 0)  /* Arvore diminui na altura */
    { Aux = *Ap;   *Ap = Aux->kids[0];
      free(Aux);
    }
}
/*
void btGravaI(TipoApontador p, int nivel, FILE* file)
{
    long i;
    if (p == NULL) return;
    printf("Acessado o Nivel %d -> ", nivel);
    for (i = 0; i < p->numKeys; i++) {
        fprintf(file, "%s\t",p->chaves[i].chavePrimaria);
        fprintf(file, "%d\n", p->chaves[i].byteoffset);
      if(p->kids[i] == NULL && p->kids[i+1] == NULL)
        {
          return;
        }
          nivel++;
          btGravaI(p->kids[i], nivel, file);
          btGravaI(p->kids[i+1], nivel, file);
          */

void btGravaI(TipoApontador p, int nivel, FILE *file)
{
  long i;
  if (p == NULL) return;
  printf("Acessado nivel %d :\n",nivel);
  for(i = 0; i<p->numKeys; i++)
  {
    fprintf(file, "%s\t",p->chaves[i].chavePrimaria);
    fprintf(file, "%d\n", p->chaves[i].byteoffset);
  }

  nivel++;
  for(i = 0; i<= p->numKeys; i++)
    btGravaI(p->kids[i], nivel,file);
}





      /*
      fprintf(file, "%s",p->chaves[i].chavePrimaria);
      fputs(" ",file);
      fprintf(file,"%d",p->chaves[i].byteoffset);
      fputs("\n",file);
		    btGravaI(p->kids[i], nivel, file);
        */


void btGrava(TipoApontador p, FILE* file)
{
    int  n = 0;
    btGravaI(p, n, file);
}

void btGravarIndice(TipoApontador Pag) {
  	FILE * ArquivoIndice;
  	ArquivoIndice = fopen("indicelista.bt", "w");
  	btGrava(Pag, ArquivoIndice);
  	fclose(ArquivoIndice);
  	return;
}

void btTipoRegistroI(TipoApontador p,int nivel)
{
  long i;
  if(p == NULL)
  {
    return;
  }

  printf("Nivel %d :\n",nivel);
  for(i = 0; i<p->numKeys; i++)
      imprimeRegistro(p->chaves[i]);
  putchar('\n');
  nivel++;
  for(i = 0; i<= p->numKeys; i++)
      btTipoRegistroI(p->kids[i], nivel);
}

void btTipoRegistro(TipoApontador p)
{
  int n = 0; btTipoRegistroI(p,n);
}

void btBuscarRegistro(TipoApontador p) {
      int verifica;
    	TipoRegistro Reg;
    	printf("Chave: "); scanf("%s", Reg.chavePrimaria);
    	Reg.Chave = ChaveNumerica(Reg.chavePrimaria);
    	int seek = 0;
    	btPesquisa(&Reg,p,&seek,&verifica);
      printf("%d\n",verifica);
      if(verifica == 1){
      	printf("\nConteudo do Registro: \n");
      	imprimeRegistro(Reg);
      	printf("Numero de buscas (seeks): %d\n", seek);
      	return;
      }
      else{
        printf("Chave not found\n");
        return;
      }
}


























/*
ApontadorbTree btCreate(int ordem)
{
  ApontadorbTree b;
  b = malloc(sizeof(btNode));
  assert(b);
  b->isLeaf = 1;
  b->numKeysumKeysumKeysumKeys = 0;
  return b;
}
btInsertInNode(ApTemp, *RegbtRetorno, *ApRetorno);
void btDestroy(bTree b)
{
  int i;
  if(b->isLeaf != 1)
  {
    for(i = 0; i < b->numKeysumKeys + 1;i++){
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
