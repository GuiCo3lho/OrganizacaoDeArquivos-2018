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
    printf("Criar Arvore-B a partir da lista1.txt(1)\n");
    printf("Visualizar arvore(2)\n");
    printf("Criar Arquivo de Indice Primario(3)\n");
    printf("Mostrar informações do TipoRegistro(4))\n");
    printf("Pesquisar registro(5)\n");

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
    char * Registro;
    FILE * file = fopen("lista.txt","rb");
    //FILE * file2 = fopen("indicelistabt.txt","wb");
    if(file == NULL)
    {
      printf("Arquivo não encontrado");
      return;
    }


    ch = fgetc(file);
    tamanhoRegistro = 1;
    //Tamanho do registro
    while(ch = fgetc(file) != '\n')
    {
      tamanhoRegistro++;
    }
    tamanhoRegistro = tamanhoRegistro + 1;


    rewind(file);
    n_registros = countregisters(file);//calcula numero de registros

    rewind(file);


    while(j < n_registros)
  {
      printf("==============================================================\n");

      fseek(file,tamanhoRegistro*j,SEEK_SET);
      coletaRegistro(Reg,file);//coleta dados do registro
      /* 8 chars do indice primario */
      fseek(file,tamanhoRegistro*j,SEEK_SET);
      fread(NOME_CHAVE,sizeof(char),3,file);

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

      /* Termina de criar 8 chars do indice primario */
      Reg->byteoffset = tamanhoRegistro*j;
      Reg->Chave = ChaveNumerica(Reg->chavePrimaria);
      btInsere(*Reg,Dicionario);
      //imprimeRegistro(Reg);





      //imprimeRegistro(Reg);

      j++;
      z = 0;
  }

 //btImprime(*p);

    printf("==============================================================\n");
    fclose(file);
    //fclose(file2);

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



void imprimeRegistro(TipoRegistro Reg)
{
    printf("Registro:%s ",(char*)Reg.nome);

    printf(" %d", Reg.matricula);
    printf("  %s", Reg.curso);
    printf("  %c\n", Reg.turma);
    printf("chavePrimaria:%s\n",Reg.chavePrimaria);
    printf("byteofset:%d\n",Reg.byteoffset);
    printf("Chave:%d\n\n",Reg.Chave);
    return;

}
//printf("Chave:%s\n",chaveP);

//printf("Registro:%s\n",Registro);
//printf("Registro:");


//fread(Registro,sizeof(char),tamanhoRegistro,file);

//char * Registro = (char *) malloc(sizeof(char)*tamanhoRegistro);
