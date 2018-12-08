#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>

int menu()
{
    int opcao;
    printf("==============================================================\n");
    printf("                       Menu do Trabalho 2\n");
    printf("==============================================================\n");
    printf("Escolha a opçao desejada\n");
    printf("Criar Indice Primario a partir da lista1 (1)\n");
    printf("Criar Indice Primario ordenado (2)\n");
    printf("Imprimir chaves primarias contidas na arvoreB no monitor(x)\n");
    printf("Visualizar arvore(3)\n");
    printf("Mostrar Indice primario no monitor(4)\n");
    printf("Buscar chave na arvore(5))\n");
    printf("Incluir Registro(6)\n");
    printf("Remover Registro(7)\n");
    printf("Sair do programa (0)\n");
    printf("Opcao:");
    scanf("%d", &opcao);
    return opcao;
}



void CriarIndPri(TipoRegistro * Reg, TipoApontador * Dicionario)
{


    char chaveP[10];
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
      coletaRegistro(Reg,file);//coleta dados do registro
      //printf("Registro:%s\n",Registro);
      //printf("Registro:");


      //fread(Registro,sizeof(char),tamanhoRegistro,file);

      /* 8 chars do indice primario */
      fseek(file,tamanhoRegistro*j,SEEK_SET);
      fread(NOME_CHAVE,sizeof(char),3,file);
      //printf("%ld\n",strlen(NOME_CHAVE));
        while(z < strlen(NOME_CHAVE))
        {
          ch = NOME_CHAVE[z];
          ch = toupper(ch);
          NOME_CHAVE[z] = ch;
          z++;
        }
        NOME_CHAVE[3] = '\0';
      fseek(file,((tamanhoRegistro)*j)+41,SEEK_SET);
      fread(MAT_CHAVE,sizeof(char),5,file);
      strcpy(chaveP,NOME_CHAVE);
      strncat(chaveP,MAT_CHAVE,5);
      strcpy(Reg->chavePrimaria,chaveP);
      //printf("Chave:%s\n",chaveP);
      /* Termina de criar 8 chars do indice primario */
      Reg->byteoffset = tamanhoRegistro*j;
      Reg->Chave = ChaveNumerica(Reg->chavePrimaria);
      //printf("byteofset:%d\n",Reg->byteoffset);
      //printf("chavePrimaria:%s\n",Reg->chavePrimaria);

      /* Escreve indice primario */
      fwrite(Reg->chavePrimaria,sizeof(char),8,file2);
      fputs(" ",file2);
      fprintf(file2,"%d",Reg->byteoffset);
      fputs("\n",file2);
      btInsere(*Reg,Dicionario);



      //fseek(file,((tamanhoRegistro)*j)+41,SEEK_SET);
      //printf("Registro:");
      //imprimeRegistro(Reg);


      //btInsere(reg,p);
      j++;
      z = 0;
  }

 //btImprime(*p);

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
        dec = dec * (10-i) + (int)StringChave[i];
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

//void criaChavePrimaria();

void coletaRegistro(TipoRegistro * Reg,FILE * arqDados)
{

    fgets(Reg->nome,40,arqDados);
    fscanf(arqDados,"%d", &Reg->matricula);
    fscanf(arqDados,"  %s", Reg->curso);
    fscanf(arqDados,"  %c\n", &Reg->turma);
    return;
}



void imprimeRegistro(TipoRegistro * Reg)
{
    printf("Registro:%s ",(char*)Reg->nome);

    printf(" %d", Reg->matricula);
    printf("  %s", Reg->curso);
    printf("  %c\n", Reg->turma);
    printf("chavePrimaria:%s\n",Reg->chavePrimaria);
    printf("byteofset:%d\n",Reg->byteoffset);
    printf("Chave:%d\n",Reg->Chave);
    return;

}
