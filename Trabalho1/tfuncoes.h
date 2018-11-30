#ifndef TFUNCOES_H_
#define TFUNCOES_H_

typedef struct registro_original
{
    char matricula[7];
    char nome[41];
    char op[4];
    char curso[9];
    char turma[2];

}t_registro_original;


void criarindicep(FILE*,char*);
int countregisters(FILE*);
void print_file(char* titulo, FILE* ind, int register_size);
char* ler_chave_primaria(char * original);
t_registro_original ler_registro_original(char * original);
int procura_chaveSec(FILE * arq_chaveSec, char chaveSec[9], int *registro_apontado);
int insere_registro_labelID(FILE * labelID, char chavePrim[31], int endereco);
void insere_registro_sec(FILE * original, FILE * chaveSec, FILE * labelID);
void criarindicesec(FILE * original, FILE * chaveSec, FILE * labelID);
//void criarinds(void);
//void criarindicesec(FILE * file, FILE * indpr, char * filename1, char * filename2);

#endif /* TFUNCOES_H_ */