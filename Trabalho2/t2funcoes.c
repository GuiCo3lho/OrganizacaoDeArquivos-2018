//corpo das funções
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>



void criaindpri(FILE * file, bTree b)
{
  //Declarações de variáveis
  RegistroCarac ElementoReg;
  char ch;
  int pos;
  int n_registros;
  int i = 0;
  int j = 0;
  int z = 0;
  char oi;
  int tamanhoRegistro,tamanhoChaveP;
  char * vetorChaveP1;
  char * vetorChaveP2;
  char * vetorChaveP;
  char * vetorTamRegistro;
  char * vetorRegistro;

  if(file == NULL)
  {
    printf("Falha!!");
    exit(1);
  }

  //alocaçao de memório para os vetores
  vetorChaveP = (char *) malloc(8*sizeof(char));//aloca chave primaria
  vetorRegistro = (char *) malloc(60*sizeof(char));
  vetorTamRegistro = (char *) malloc(60*sizeof(char));//aloca registro
  vetorChaveP1 = (char *) malloc(3*sizeof(char));//aloca registro
  vetorChaveP2 = (char *) malloc(5*sizeof(char));//aloca registro



  //Calcular tamanho de um registro
  ch = fgetc(file);
  printf("\nPrimeiroChar:%c\n",ch);
  vetorTamRegistro[0] = ch;
  while( (ch = fgetc(file)) != '\n')
  {
    i++;
    vetorTamRegistro[i] = ch;

  }

  tamanhoRegistro = strlen(vetorTamRegistro);
  printf("Tamanho do registro:%d\n",tamanhoRegistro);
  printf("UltimoChar:%c\n",vetorTamRegistro[52]);

  rewind(file);


  n_registros = countregisters(file);
  printf("Número de registros:%d\n",n_registros);
  pos = ftell(file);



  while(j < n_registros)
{
  fseek(file,(tamanhoRegistro+1)*j,SEEK_SET);
  pos = ftell(file);
  printf("Registro%d:%d\n",j,pos);//veificar numero do registro e sua posição em bytes no arquivo
  fread(vetorChaveP1,sizeof(char),3,file);//leitura da chave primária
  while(z < sizeof(vetorChaveP1))
  {
    ch = vetorChaveP1[z];
    ch = toupper(ch);
    vetorChaveP1[z] = ch;
    z++;
  }
  fseek(file,(tamanhoRegistro+1)*j+41,SEEK_SET);
  fread(vetorChaveP2,sizeof(char),5,file);
  fseek(file,(tamanhoRegistro+1)*j, SEEK_SET);
  fread(vetorRegistro,sizeof(char),54,file);
  strcat(vetorChaveP,vetorChaveP1);
  strcat(vetorChaveP,vetorChaveP2);
  tamanhoChaveP = strlen(vetorChaveP);
  printf("%s\n",vetorRegistro);
  printf("%s\n",vetorChaveP);
  printf("TamanhoChaveP:%d\n",tamanhoChaveP);
  printf("=====================================================\n");
  strcpy(ElementoReg.Registro, vetorRegistro);
  strcpy(ElementoReg.chaveP , vetorChaveP);
  memset(vetorChaveP,0,sizeof(vetorChaveP));//reseta o vetor que carrega as chavesPrimarias
  rewind(file);
  j++;
  z = 0;
}
  /*
  fwrite(vetorChaveP,sizeof(char),8,ind);//chave primária gravada
  fputc('|',ind);//separador entre chave primária e referencia
  fprintf(ind,"%ld",pos);//referencia gravada
  fputc('\n',ind);//pular pra próxima linha
  j++;
  */

  //liberação das alocações dinâmicas e fechamento de arquivos
  free(vetorChaveP1);
  free(vetorChaveP2);
  free(vetorChaveP);
  free(vetorTamRegistro);
  fclose(file);
}



//função para contar número de registros em um arquivo de dados
  int countregisters(FILE * file)
{
  char ch;
  int n_registros = 0;
  while(!feof(file))
   {
     ch = fgetc(file);
     if(ch == '\n')
     {
       n_registros++;
     }
   }
   return n_registros;
   fclose(file);
}
