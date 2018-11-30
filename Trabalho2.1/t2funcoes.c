#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>

void CriarIndPri(void)
{
    Registro reg;
    char chaveP[8];
    char ch;
    char NOME_CHAVE[5];
    char MAT_CHAVE[3];
    int z,j,n_registros;
    z = 0,j = 0,n_registros = 0;
    int tamanhoRegistro;
    FILE * file = fopen("lista.txt","rb");
    if(file == NULL)
    {
      printf("Arquivo não encontrado");
      return;
    }



    ch = fgetc(file);
    tamanhoRegistro = 1;
    while(ch = fgetc(file) != '\n')
    {
      tamanhoRegistro++;
    }
    tamanhoRegistro = tamanhoRegistro + 1;
    printf("Tamanho Registro %d\n",tamanhoRegistro);
    char * Registro = (char *) malloc(sizeof(char)*tamanhoRegistro);
    rewind(file);
    n_registros = countregisters(file);
    printf("Número de registros:%d\n",n_registros);
    rewind(file);


    while(j < n_registros)
  {
      printf("==============================================================\n");

      fseek(file,tamanhoRegistro*j,SEEK_SET);
      fread(Registro,sizeof(char),tamanhoRegistro,file);
      printf("Registro:%s\n",Registro);
      fseek(file,tamanhoRegistro*j,SEEK_SET);
      fread(NOME_CHAVE,sizeof(char),3,file);
        while(z < sizeof(NOME_CHAVE))
        {
          ch = NOME_CHAVE[z];
          ch = toupper(ch);
          NOME_CHAVE[z] = ch;
          z++;
        }

      strcpy(chaveP,NOME_CHAVE);
      fseek(file,((tamanhoRegistro)*j)+41,SEEK_SET);
      fread(MAT_CHAVE,sizeof(char),5,file);
      strncat(chaveP,MAT_CHAVE,5);
      strcpy(reg.chavePrimaria,chaveP);
      printf("chavePrimaria:%s\n",reg.chavePrimaria);

      reg.byteoffset = tamanhoRegistro*j;
      printf("byteofset:%d\n",reg.byteoffset);
      j++;
      z = 0;
  }

    printf("==============================================================\n");
    fclose(file);
    free(Registro);
}

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
