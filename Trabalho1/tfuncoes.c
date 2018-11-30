#include <stdio.h>
#include <stdlib.h>
#include <trabalho.h>
#include <string.h>



int opcoes()
{
    printf("-------------------MENU-----------------------\n");
    printf("Mostrar Registros (1)\n");
    printf("Criar indice primario (2)\n");
    printf("Mostrar Índice Primário (3)\n");
    printf("Encerrar programa (4)\n");
    int opcao;
    printf("Opção:");
    scanf("Opcao: %d",&opcao);
    getchar();
    return opcao;
}

void OpcaoEscolhida(int opcao, Aponta * l1, Aponta * l2,FILE * lista1, FILE * lista2)
{
  int numArq;
  char filename[20];

  switch(opcao)
  {
    case 1:
    MostraLista(l1,1);
    MostraLista(l2,2);
    break;
    case 2:
    printf("Escolha o arquivo\n");
    printf("Lista1 (1)\n");
    printf("Lista2 (2)\n");
    scanf("%d", &numArq);
    if(numArq == 1)
    {
    sprintf(filename,"indicePlista1.txt");
    criarindicep(lista1,filename);
  }
  else{
    sprintf(filename,"indicePlista2.txt");
    criarindicep(lista2,filename);
  }

    case 3:
    printf("Escolha o arquivo\n");
    printf("Lista1 (1)\n");
    printf("Lista2 (2)\n");
    scanf("%d", &numArq);
    /*
    if(numArq == 1)
    {
       PrintarChavesPrimarias(lista1,1);
       else
       PrintarChavesPrimarias(lista2,2);
       */
       break;


    case 4:
    exit(1);
    break;
  }
}

Aponta * CriarAponta()
{
    Aponta * p = (Aponta*)malloc(sizeof(Aponta));
    p->inicio = NULL;
    p->fim = NULL;
    p->tamanho = 0;
    return p;
}


Lista * InserirLista(int matricula, char * nome, char * curso, char turma, char * chave_primaria,int op, Aponta * lista, int pos)
{
  Lista * novo = (Lista*)malloc(sizeof(Lista));
  novo->matricula = matricula;

  strcpy(novo->nome,nome);
  strcpy(novo->curso,curso);
  strcpy(novo->chavePrimaria,chave_primaria);
  novo->op = op;
  novo->prox = NULL;
  if(lista->inicio == NULL)
  {
    lista->inicio = novo;
  }
  else{
    lista->fim->prox = novo;
  }
  lista->fim = novo;
  return novo;
}


void MostraLista(Aponta *lista,int arq)
{
  int i;

    Lista * aux = lista->inicio;
    if(arq == 1)
    {
        printf("Registros da Lista 1");
    }
    else
    {
        printf("Registros da Lista 2");
    }
  while(aux != NULL)
  {
      printf("%d %s\t%d  %s\t\t%c|%d\n",aux->matricula,aux->nome,aux->op,aux->curso,aux->turma,i);
  }
}


int vazia(Aponta * lista)
{
  if(lista == NULL)
  {
    return 0; /* lista vazia */
  }
  else
  {
    return 1;
  }
}

void criarindicep(FILE * file,char * filename)
{
  file = fopen("lista1.txt","rb");
  if(file == NULL)
  {
    printf("Falha!!");
    exit(1);
  }

    long pos;
    char ch;
    int i = 0,j = 0,n_registros;
    char * vchavep;//vetor que vai armazenar a chave primária (MATRICULA/NOME)
    char * vreg;//vetor que vai armazenar o registro todo
    char * matricula;
    char nome[41];
    int op;
    char curso[3];
    char turma;
    FILE * ind;//ponteiro para possibilitar escrita no arquivo de índices primários
    //Declarações e verificações de ponteiros para arquivos
    ind = fopen(filename,"wb");
    if(file == NULL)
    {
      printf("Falha!!");
      exit(1);
    }
    if(ind == NULL)
    {
      printf("Falha!!");
      exit(1);
    }
    //alocaçao de memório para os vetores
    vchavep = (char *) malloc(sizeof(char)*30);//aloca chave primaria
    vreg = (char *)malloc (100*sizeof(char));//aloca registro
    matricula = (char *)malloc (7*sizeof(char));//aloca registro


    //Calcular tamanho de um registro
    ch = fgetc(file);
    vreg[0] = ch;
    while( (ch = fgetc(file)) != '\n')
    {
      i++;
      vreg[i] = ch;
    }
    printf("PrimeiroChar %c\n", vreg[61]);
    printf("Tamanho %ld", strlen(vreg));
    printf("Tamanho+1 %ld",strlen(vreg)+1);
    //voltar para inicio do arquivo após calcular tamanho do registro
    rewind(file);
     //verificar numero de registros no arquivo lista
    n_registros = countregisters(file); //função para contar registros
    printf("\nNumber of Registers:%d\n",n_registros);//teste;

    //Construção do índice primário
    while(j < n_registros)//leitura até o fim do arquivo lista
    {
      fseek(file,(strlen(vreg)+1)*j,SEEK_SET);
      pos = ftell(file);
      printf("Registro%d:%ld\n",j,pos);
      fread(matricula,sizeof(char)*6,6,file);
      printf("matricula:%s",matricula);
      fseek(file,(strlen(vreg)+1)*j,SEEK_SET);
      fread(vchavep,sizeof(char),30,file);//leitura da chave primária
      fwrite(vchavep,sizeof(char),30,ind);//chave primária gravada
      fputc('|',ind);//separador entre chave primária e referencia
      fprintf(ind,"%ld",pos);//referencia gravada
      fputc('\n',ind);//pular pra próxima linha
      j++;

    }
    //desalocação e fechamento
    free(vreg);
    free(vchavep);
    fclose(file);
    fclose(ind);
}
//funcao para contar número de registros do arquivo
int countregisters(FILE * p)
{
    char ch;
    int n_registros = 0;
     while(!feof(p))
     {
       ch = fgetc(p);
       if(ch == '\n')
       {
         n_registros++;
       }
     }
     return n_registros;
     free(p);
}
