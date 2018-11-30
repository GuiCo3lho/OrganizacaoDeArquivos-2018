#include <stdio.h>
#include <stdlib.h>
#include "tfuncoes.h"

int main()
{
  //Declarcão,abertura e verificação de ponteiros para listas
  FILE *lista1, *lista2;
  FILE *indsec, *labelID;
  FILE * indicelista1;
  FILE * indicelista2;
  char filename[20];//string para nomear indices primários
  char filename1[20];
  char filename2[20];
  
  lista1 = fopen("lista1.txt","r");
  if(lista1 == NULL)
  {
    printf("Não foi possível abrir lista1.txt\n");
    exit(1);
  }

  lista2 = fopen("lista2.txt","r");
  if(lista2 == NULL)
  {
    printf("Não foi possível abrir lista2.txt\n");
    exit(1);
  }

  //nomeaçao dos arquivos txt e criacão dos índices primarios
  sprintf(filename,"indicelista1.txt");
  sprintf(filename,"indicelista2.txt");
  
  //criando arquivos de índices primários
  criarindicep(lista1,filename);
  criarindicep(lista2,filename);

  indicelista1 = fopen("indicelista1.txt","r");
  if(lista1 == NULL)
  {
    printf("Não foi possível abrir indicelista1.txt\n");
    exit(1);
  }
  print_file("Arquivo de índices primários da lista 1", indicelista1, 40);

  indicelista2 = fopen("indicelista2.txt","r");
  if(lista2 == NULL)
  {
    printf("Não foi possível abrir indicelista2.txt\n");
    exit(1);
  }
  print_file("Arquivo de índices primários da lista 2", indicelista2, 40);

  sprintf(filename1,"chaveSecundaria1.txt");
  sprintf(filename2,"LabelID1.txt");

  indsec = fopen(filename1, "w+");
  if(indsec == NULL)
  {
    printf("Falha!!");
    exit(1);
  }

  labelID = fopen(filename2, "w+");
  if(labelID == NULL)
  {
    printf("Falha!!");
    exit(1);
  }

  //criando arquivos de índices secundários para lista 1
  criarindicesec(lista1, indsec, labelID);
  print_file("Arquivo de chaves de índices secundários da lista 1", indsec, 18);
  print_file("Arquivo de lista invertida de índices secundários da lista 1", labelID, 40);
  
  fclose(indsec);
  fclose(labelID);

  sprintf(filename1,"chaveSecundaria2.txt");
  sprintf(filename2,"LabelID2.txt");

  indsec = fopen(filename1, "w+");
  if(indsec == NULL)
  {
    printf("Falha!!");
    exit(1);
  }

  labelID = fopen(filename2, "w+");
  if(labelID == NULL)
  {
    printf("Falha!!");
    exit(1);
  }

  //criando arquivos de índices secundários para lista 2
  criarindicesec(lista2, indsec, labelID);
  print_file("Arquivo de chaves de índices secundários da lista 2", indsec, 18);
  print_file("Arquivo de lista invertida de índices secundários da lista 1", labelID, 40);

  fclose(indsec);
  fclose(labelID);

  fclose(lista1);
  fclose(lista2);
  fclose(indicelista1);
  fclose(indicelista2);

  return 0;

}
