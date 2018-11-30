#define MAX_KEYS 3

typedef struct {
  char chavePrimaria[8];//nome + matricula (8)
  int byteoffset;
  char nome[41];
  char matricula[5];
  char curso[2];
  char turma;
  int teste;
} Registro;

typedef struct btNode* ApontadorbTree;

typedef struct btNode {
  int isLeaf;
  int numKeys;
  Registro chaves[MAX_KEYS];
  ApontadorbTree *kids[MAX_KEYS-1];
} btNode;

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





void CriarIndPri(void);
int countregisters(FILE*);
