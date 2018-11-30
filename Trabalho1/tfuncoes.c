#include <stdio.h>
#include <stdlib.h>
#include "tfuncoes.h"
#include <string.h>

//função que cria um arquivo com todos os índices primários
void criarindicep(FILE * file, char * filename)
{
  long pos;
  char ch;
  int i = 0, j = 0, n_registros;
  char *vchavep; //vetor que vai armazenar a chave primária (MATRICULA/NOME)
  char *vreg;    //vetor que vai armazenar o registro todo
  FILE *ind;     //ponteiro para possibilitar escrita no arquivo de índices primários
  //Declarações e verificações de ponteiros para arquivos
  if (file == NULL)
  {
    printf("Falha!!");
    exit(1);
  }
  ind = fopen(filename, "w+");
  if (ind == NULL)
  {
    printf("Falha!!");
    exit(1);
  }
  //alocaçao de memório para os vetores
  vchavep = (char *)malloc(sizeof(char) * 30); //aloca chave primaria
  vreg = (char *)malloc(100 * sizeof(char));   //aloca registro
  //Calcular tamanho de um registro
  ch = fgetc(file);
  vreg[0] = ch;
  while ((ch = fgetc(file)) != '\n')
  {
    i++;
    vreg[i] = ch;
  }
  //voltar para inicio do arquivo após calcular tamanho do registro
  rewind(file);
  //verificar numero de registros no arquivo lista
  n_registros = countregisters(file); //função para contar registros
  //printf("\nNumber of Registers: %d\n",n_registros);//teste;

  //Construção do índice primário
  while (j < n_registros) //leitura até o fim do arquivo lista
  {
    fseek(file, (strlen(vreg) + 1) * j, SEEK_SET);
    pos = ftell(file);
    //printf("Registro %d: %ld\n",j,pos/64);
    fread(vchavep, sizeof(char), 30, file); //leitura da chave primária
    fwrite(vchavep, sizeof(char), 30, ind); //chave primária gravada
    fputc('|', ind);                        //separador entre chave primária e referencia
    fprintf(ind, "%8ld", pos/64);               //referencia gravada
    fputc('\n', ind);                       //pular pra próxima linha
    j++;
  }
  //desalocação e fechamento
  free(vreg);
  free(vchavep);
  fclose(ind);
}

//funcao para contar número de registros do arquivo
int countregisters(FILE * p)
{
  char ch;
  int n_registros = 0;
  while (!feof(p))
  {
    ch = fgetc(p);
    if (ch == '\n') 
    {
      n_registros++;
    }
  }
  return n_registros;
  free(p);
}

//função que escreve o arquivo no terminal seguindo uma largura fixa de registro
void print_file(char * titulo, FILE * ind, int register_size)
{
  char buffer[register_size];

  printf("\n%s\n", titulo);
  rewind(ind);
  while(!feof(ind))
  {
    fread(buffer, 1, register_size, ind);
    buffer[register_size-1] = '\0';
    printf("%s\n", buffer);
  }
}

//função para ler a chave primária no arquivo original (lista1, por exemplo)
char* ler_chave_primaria(char* original)
{
  char* chavePrim;

  chavePrim = (char*)malloc(31*sizeof(char)); //aloca 30 caracteres para a chave primária e um para a quebra de linha
  sscanf(original, "%30[^\n]\n", chavePrim); // escreve a quebra de linha no final da string

  return chavePrim;
}

//função que ler um registro completo no arquivo original e retorna uma struct com todas as informações coletadas
t_registro_original ler_registro_original(char* original)
{
  t_registro_original registro;
  sscanf(original, "%6[^\n] %40[^\n] %3[^\n] %8[^\n] %1[^\n]", registro.matricula, registro.nome, registro.op, registro.curso, registro.turma);
  return registro;
}

//função que confere se a chave secundária já existe
int procura_chaveSec(FILE * arq_chaveSec, char chaveSec[9], int *registro_apontado)
{
  char aux[9];
  int n_reg, n_linha = 0;

  rewind(arq_chaveSec); //volta pro início do arquivo
  while(!feof(arq_chaveSec)) //enquanto não chegar no final do arquivo
  {
    fscanf(arq_chaveSec, "%8[^|]| %d\n", aux, &n_reg); //lê chave secundária
    aux[8] = '\0';
    if(strcmp(aux, chaveSec) == 0) //se existir,
    {
      *registro_apontado = n_reg; //guarda no ponteiro passado o número apontado no arquivo de chave secundária como o primeiro da lista
      return n_linha; //retorna a posição do registro no arquivo de chaves secundárias
    }
    n_linha++;
  }
  *registro_apontado = -1; //se não existir, guarda no ponteiro passado o -1 
  return -1; // retorna -1 como posição do registro no arquivo de chaves secundárias (pq ainda não existe esse registro no arquivo)
}

//função que insere um registro no arquivo com as LabelIDs
int insere_registro_labelID(FILE * labelID, char chavePrim[31], int endereco)
{
  int contador = 0;
  long size;

  fseek(labelID, 0, SEEK_END); //vai para o início do arquivo
  size = ftell(labelID); //indica qual é o índice do registro
  fprintf(labelID, "%30s| %7d\n", chavePrim, endereco);
  return (int)size/40;
}

//função que insere um registro no arquivo secundário
void insere_registro_sec(FILE * original, FILE * chaveSec, FILE * labelID)
{
  int i, pos_ind, pos_reg, endereco_labelID, endereco_chaveSec;
  char linha[64], *chavePrim;
  t_registro_original registro;

  fscanf(original, "%[^\n]\n", linha);
  linha[63] = '\0';
  registro = ler_registro_original(linha);
  chavePrim = ler_chave_primaria(linha);
  pos_ind = procura_chaveSec(chaveSec, registro.curso, &pos_reg);
  if(pos_ind == -1)
  {
    // inserir no labelID a chavePrim com o valor sendo -1 e grava posição escrita (retorno da func) 
    endereco_labelID = insere_registro_labelID(labelID, chavePrim, pos_reg);
    fseek(chaveSec, 0, SEEK_END);
    fprintf(chaveSec, "%8s| %7d\n", registro.curso, endereco_labelID);
  }
  else
  {
    // acessa chaveSec e descobre qual num ele aponta
    // insere no labelID com esse número que ele aponta e guarda onde foi escrito
    endereco_labelID = insere_registro_labelID(labelID, chavePrim, pos_reg);
    rewind(chaveSec);
    for(i = 0; i < pos_ind; i++)
    {
      fscanf(chaveSec, "%*[^\n]\n");
    }
    fprintf(chaveSec, "%8s| %7d\n", registro.curso, endereco_labelID); //descobrir como escrever por cima
  }
  free(chavePrim);
}

//função que cria um arquivo de índices secundários
void criarindicesec(FILE * original, FILE * chaveSec, FILE * labelID)
{
  rewind(original);
  insere_registro_sec(original, chaveSec, labelID);
  while(!feof(original))
  {
    insere_registro_sec(original, chaveSec, labelID);
  }
}
/*
void quicksort(int vec[], int inicio, int fim) {
int pivo = vec[ (int)(inicio+fim)/2 ];
int i = inicio, j = fim, temp;
while (i < j) {
while(pivo > vec[i]) i++;
while(pivo < vec[j]) j--;
if (i<=j) {
temp = vec[i];
vec[i] = vec[j];
vec[j] = t;
i++;
j--;
}
}
if (j > inicio)
quicksort(vec, inicio, j);
if (i < fim)
quicksort(vec, i, fim);
}*/