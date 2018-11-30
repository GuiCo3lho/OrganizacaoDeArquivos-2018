#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>


ApontadorbTree btCreate(int ordem)
{
  ApontadorbTree b;
  b = malloc(sizeof(btNode));
  assert(b);
  b->isLeaf = 1;
  b->numKeys = 0;
  return b;
}

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





}
