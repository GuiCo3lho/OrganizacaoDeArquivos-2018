#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>

void CriarIndPri(TipoRegistro * Reg, TipoApontador * Dicionario)
{


    char chaveP[8];
    char ch;
    char NOME_CHAVE[3];
    char MAT_CHAVE[4];
    int z,j,n_registros;
    z = 0,j = 0,n_registros = 0;
    int tamanhoRegistro;
    FILE * file = fopen("lista.txt","rb");
    FILE * file2 = fopen("indicelistabt.txt","wb");
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

      //fread(Registro,sizeof(char),tamanhoRegistro,file);
      coletaRegistro(Reg,file);
      //printf("Registro:%s\n",Registro);
      printf("Registro:");
      imprimeRegistro(Reg);
      fseek(file,tamanhoRegistro*j,SEEK_SET);
      fread(NOME_CHAVE,sizeof(char),3,file);
      printf("%ld\n",strlen(NOME_CHAVE));
        while(z < strlen(NOME_CHAVE))
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
      printf("Chave:%s\n",chaveP);

      strcpy(Reg->chavePrimaria,chaveP);
      printf("chavePrimaria:%s\n",Reg->chavePrimaria);
      Reg->byteoffset = tamanhoRegistro*j;
      printf("byteofset:%d\n",Reg->byteoffset);
      fwrite(Reg->chavePrimaria,sizeof(char),8,file2);
      fputs(" ",file2);
      fprintf(file2,"%d",Reg->byteoffset);
      fputs("\n",file2);
      Reg->Chave = ChaveNumerica(Reg->chavePrimaria);

      //btInsere(reg,p);
      j++;
      z = 0;
  }

//  btImprime(*p);

    printf("==============================================================\n");
    fclose(file);
    fclose(file2);
    free(Registro);
}

int ChaveNumerica(char StringChave[])
{
    int dec = 0, i, j, len;
    len = strlen(StringChave);
    for(i=0; i<len; i++)
    {
        dec = dec * 10 + (StringChave[i] - '0' );
    }
    return dec;
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

void coletaRegistro(TipoRegistro * Reg,FILE * arqDados)
{
    //char nomeT[40];
    fgets(Reg->nome,40,arqDados);
    fscanf(arqDados,"%d", &Reg->matricula);
    fscanf(arqDados,"  %s", Reg->curso);
    fscanf(arqDados,"  %c\n", &Reg->turma);
    return;
}

void imprimeRegistro(TipoRegistro * Reg)
{
    printf("%s ",(char*)Reg->nome);
    printf(" %d", Reg->matricula);
    printf("  %s", Reg->curso);
    printf("  %c\n", Reg->turma);
    return;
}
