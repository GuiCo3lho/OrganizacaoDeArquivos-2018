#define MAX_KEYS (3)
/* Cabeçalho de Estruturas */

struct RegistroCaracteristicas { //RegistroCarac
    char chaveP[8];//guarda chavePrimaria para busca/inserção/eliminação na árvore
    char Registro[54];//guarda o registro completo da chavePrimaria
};

struct btNode {
    int isLeaf;//é uma folha?
    int numKeys;//numero de chaves no nó
    struct RegistroCaracteristicas *chave[MAX_KEYS];//vetor de struct do tipo RegistroCarac
    struct btNode *kids[MAX_KEYS + 1];//vetor de ponteiros que aponta para o nós filhos => guarda endereço das structs btNode filhos
}; //bTree



typedef struct btNode *bTree;
typedef struct RegistroCaracteristicas *RegistroCarac[MAX_KEYS];
//typedef struct RegistroCaracteristicas RegistroCarac;
/* Cabeçalho de funções */
void criaindpri(FILE *, bTree);
int countregisters(FILE *);
void haha(void);
bTree btCreate(void);
void btDestroy(bTree);
static int searchKey(int,RegistroCarac, char*);
int btSearch (bTree b, char*);
static bTree btInsertInternal(bTree, char*, char*, RegistroCarac *);
void btInsert(bTree b, char*, char*);
