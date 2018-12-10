#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trabalho2.h"

int menu()
{
    // inicializar variável da opção
    int opcao;

    // imprimir menu principal na interface
    printf("==============================================================\n");
    printf("                       Menu do Trabalho 2\n");
    printf("==============================================================\n");
    printf("Escolha a opçao desejada\n");
    printf("Criar Arvore-B a partir da lista1.txt                      (1)\n");
    printf("Visualizar arvore                                          (2)\n");
    printf("Criar Arquivo de Indice Primario                           (3)\n");
    printf("Mostrar informações do TipoRegistro                        (4)\n");
    printf("Pesquisar registro                                         (5)\n");
    printf("Inserir Registro no arquivo de Dados                       (6)\n");
    printf("Opcao:");

    // ler opção escolhida pelo usuário
    scanf("%d", &opcao);

    // retornar a opção selecionada pelo usuário
    return opcao;
}

// criar um índice primário
void CriarIndPri(TipoRegistro * Reg, TipoApontador * Dicionario)
{
    // declarar variáveis
    char chaveP[10];
    char ch;
    char NOME_CHAVE[3];
    char MAT_CHAVE[4];
    int z, j, n_registros;
    int tamanhoRegistro;
    //char * Registro;
    FILE * file = fopen("lista.txt","rb");

    // inicializar variáveis
    z = 0, j = 0,n_registros = 0;
    //FILE * file2 = fopen("indicelistabt.txt","wb");

    // checar se o arquivo existe
    if(file == NULL)
    {
        printf("Arquivo não encontrado");
        return;
    }

    // se existir, pegar o caractere do arquivo
    ch = fgetc(file);
    tamanhoRegistro = 1;

    //Tamanho do registro
    while((ch = fgetc(file)) != '\n')
    {
        tamanhoRegistro++;
    }
    tamanhoRegistro = tamanhoRegistro + 1;

    // voltar ao início do arquivo para contar os registros
    rewind(file);
    n_registros = countregisters(file);//calcula numero de registros

    // voltar ao início do arquivo
    rewind(file);

    // enquanto j for menor que o núvemo total de registros
    while(j < n_registros)
    {
        printf("==================Inserido registro %d====================\n",j);
        fseek(file, tamanhoRegistro*j, SEEK_SET);
        coletaRegistro(Reg, file);//coleta dados do registro
        /* 8 chars do indice primario */
        fseek(file, tamanhoRegistro*j, SEEK_SET);
        fread(NOME_CHAVE, sizeof(char), 3, file);

        // enquanto z for menor que o tamanho do nome da chave
        while(z < strlen(NOME_CHAVE))
        {
            ch = NOME_CHAVE[z];
            ch = toupper(ch);
            NOME_CHAVE[z] = ch;
            z++;
        }

        // procurar pela chave requisitada pelo usuário
        NOME_CHAVE[3] = '\0';
        fseek(file, ((tamanhoRegistro)*j)+41, SEEK_SET);
        fread(MAT_CHAVE, sizeof(char), 5, file);
        strcpy(chaveP, NOME_CHAVE);
        strncat(chaveP, MAT_CHAVE, 5);
        strcpy(Reg->chavePrimaria, chaveP);

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

// encontrar a chave numérica
int ChaveNumerica(char StringChave[])
{
    // declarar variáveis
    int dec = 0, i, len;
    len = strlen(StringChave);
    for(i=0; i<len; i++)
    {
        dec = dec * (10-i) + (int)StringChave[i];
    }
    return dec;
}

// contar registros
int countregisters(FILE * file)
{
    // declarar variáveis
    char ch;
    int n_registros = 0;

    // enquanto o arquivo não chegar ao fim, contar a quantidade de registros
    while(!feof(file))
     {
       ch = fgetc(file);
       if(ch == '\n')
       {
         n_registros++;
       }
     }
     //fclose(file);
     return n_registros;
}

//void criaChavePrimaria();

// coletar registro
void coletaRegistro(TipoRegistro * Reg,FILE * arqDados)
{
    // ler o nome do registro passado pelo usuário, a matrícula, o curso e a turma
    fgets(Reg->nome,40,arqDados);
    fscanf(arqDados,"%d", &Reg->matricula);
    fscanf(arqDados,"  %s", Reg->curso);
    fscanf(arqDados,"  %c\n", &Reg->turma);
    return;
}



void imprimirDados(TipoRegistro Reg)
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

void imprimirRegistro(TipoRegistro Reg){
    printf("%s ",(char*)Reg.nome);
    printf(" %.5d", Reg.matricula);
    printf("  %s", Reg.curso);
    printf("  %c\n", Reg.turma);
}


//printf("Chave:%s\n",chaveP);

//printf("Registro:%s\n",Registro);
//printf("Registro:");


//fread(Registro,sizeof(char),tamanhoRegistro,file);

//char * Registro = (char *) malloc(sizeof(char)*tamanhoRegistro);
