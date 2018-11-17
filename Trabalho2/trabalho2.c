//função main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <trabalho2.h>

int main()
{

  bTree c;
  FILE * lista;
  lista = fopen("lista.txt","rb");
  if(lista == NULL)
  {
    printf("Falha!!");
    exit(1);
  }

  c = btCreate();
  btDestroy(c);
  criaindpri(lista,c);



  return 0;
}
