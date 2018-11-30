//b tree implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <trabalho2.h>
#define MAX_KEYS (3)//numero de chaves por nó

bTree btCreate(void)
{
  bTree b;

  b = malloc(sizeof(*b));
  assert(b);//sai do programa caso b seja NULL ou não aponte para nada => só existe se b não aponta pra nada

  b->isLeaf = 1;//nó é uma folha pois acabou de ser criado
  b->numKeys = 0;//nó não possui nenhuma chave pois acabou de ser criado
  printf("Árvore B Criada!\n");
  return b;
}

void btDestroy(bTree b)
{
  int i;
  if(b->isLeaf != 1)
  {
    for(i = 0; i < b->numKeys + 1; i++)// laço recursivo para destruir a árvore b toda
    {
      btDestroy(b->kids[i]);//destroi os MAX_KEYS+1 filhos de cada nó
    }
  }
    printf("Árvore B Destruida!");
    free(b);

}
//retorna o menor índice do array buscado em que key <= chave[i]
//retorna o índice da chave achada ou o índice da menor chave que é maior que a chave buscada
//caso nao todos as chaves sejam maiores que a chave buscada=> retorna numKeys
static int
searchKey(int numKeys, RegistroCarac chave, char * vetorChaveP)//procura vetorChaveP na árvore no nó com os índices chave[]
{
  int inicio;
  int fim;
  int meio;
  int resultado;

  inicio = -1;
  fim = numKeys;//indicador fim recebe numero de chaves no nó
  while(inicio + 1 < fim)
  {
    meio = (inicio + fim)/2;
    resultado = strcmp(vetorChaveP, chave[meio]->chaveP);

    if(resultado = 0)//chave buscada é igual a chave[meio]
    {
      return meio;//retorna índice do endereço da chave achada
    }
    else if(resultado > 0) //chavebuscada é maior que a chave[meio]
    {
      inicio = meio;
    }
    else{ //chave buscada é menor que a chave[meio]
      fim = meio;
    }
  }

  return fim;
}

int btSearch (bTree b, char * vetorChaveP)//return 1 => key found // return 0 => key not found
{
    int pos;

    if(b->numKeys == 0)//saber se a árvore está vazia => sai da função caso esteja vazia
    {
        return 0;
    }

    pos = searchKey(b->numKeys, b->chave, vetorChaveP);

    if(pos < b->numKeys && b->chave[pos]->chaveP == vetorChaveP)//se pos for igual a b->numKeys a chave buscada é maior que todas as chaves do nó => ir parakids[pos+1]
    {
      printf("Chave %s achada!",b->chave[pos]->chaveP);
      return 1;
    }
    else{
      return(!b->isLeaf && btSearch(b->kids[pos],vetorChaveP));
    }

}


static bTree btInsertInternal(bTree b, char * vetorChaveP,char * vetorRegistro , RegistroCarac * median)
{
    int pos;
    int mid;
    RegistroCarac *mediana;
    bTree b2;

    pos = searchKey(b->numKeys,b->chave,vetorChaveP);

    if(pos < b->numKeys && b->chave[pos]->chaveP == vetorChaveP)
    {
        printf("A chave %s já existe na árvore",b->chave[pos]->chaveP);
        return 0;
    }

    if(b->isLeaf) {
      //todos acima do elemento na posição pos se move um espaço para dar lugar para a chave a ser inserida
      memmove(&b->chave[pos+1], &b->chave[pos],sizeof(*(b->chave)) * (b->numKeys - pos));
      strcpy(b->chave[pos]->chaveP,vetorChaveP);//apos a movimentação de todos as chaves acima de pos, chave[pos]->recebe a nova chave
      strcpy(b->chave[pos]->Registro,vetorRegistro);
      b->numKeys++;//aumento no numero de chaves após inserção

    } else {
      //inserir chave no filho do nó
      b2 = btInsertInternal(b->kids[pos],vetorChaveP,vetorRegistro, &mediana);

      if (b2) {
        //Toda chave acima de pos move um espaço
        memmove(&b->chave[pos+1]), &b->chave[pos] ,sizeof(*(b->chave)) * (b->numKeys - pos);
        //novo filho vai na posição pos + 1
        memmove(&b->chave[pos+2], &b->kids[pos], sizeof(*(b->chave)) * (b->numKeys - pos);

        strcpy(b->chave[pos]->chaveP,mediana->chaveP);
        b->kids[pos+1] = b2;
        b->numKeys++;
      }
    }

      if(b->numKeys >= MAX_KEYS)//Se ocorrer a inserção quando o nó estiver cheio de chaves
      {
          mid = b->numKeys/2;//escolher o índice escolhido para guardar o valor de median

          strcpy(median->chaveP, b->chave[mid]->chaveP);//median recebe a chave para promoção
          strcpy(median->Registro, b->chave[mid]->Registro);//median recebe o registro ligado a chave

          b2 = malloc(sizeof(*b2));//criação do novo nó com chaves maiores que a mediana

          b2->numKeys = b->numKeys - mid - 1;//o novo nó vai receber total - mid - 1 chaves
          b2->isLeaf = b->isLeaf;//b2 recebe a mesma verificação de folha que b1 pois ocorreu o splitting

          memmove(b2->chave, &b->chave[mid+1], sizeof(*(b->chave)) * (b2->numKeys));//move todos os elementos á partir do índice [mid+1] para o novo nó b2
          if(!b->isLeaf) {//caso b não seja uma folha
              memmove(b2->kids, &b->kids[mid+1], sizeof(*(b->kids)) * (b2->numKeys+1));//move todos os elementos do filho á partir do índice [mid+1] para o novo nó b2
          }

          b->numKeys = mid;

          return b2;
      } else {
          return 0;
      }
}


void btInsert(bTree b, char * vetorChaveP, char * vetorRegistro)
{
  bTree b1; // novo filho da esquerda
  bTree b2; // novo filho da direita
  RegistroCarac median;//recebe a chave resultado da mediana do nó b

  b2 = btInsertInternal(b, vetorChaveP, vetorRegistro, &median);//Criar novo nó b2 ao lado de b
  /* nós estamos na raiz. Se houver o split, terá que haver uma nova raiz b */
  /* Para isso vão ser criados b1 e b2 que sejam raiz de b */
  if(b2)
  {
    b1 = malloc(sizeof(*b1));//aloca nó que vai guardar a raiz b
    assert(b1);

    memmove(b1,b,sizeof(*b));//move o conteudo da raiz (b) para b1 => Para que b seja a nova raiz pai de b1 e b2

    //criação da nova raiz apontando para os nós filhos b1 e b2
    b->numKeys = 1;
    b->isLeaf = 0;
    strcpy(b->chave[0]->chaveP,median->chaveP);
    strcpy(b->chave[0]->Registro,median->Registro);
    b->kids[0] = b1;
    b->kids[1] = b2;
  }
}
