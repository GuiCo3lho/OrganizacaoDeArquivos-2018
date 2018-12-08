#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>

int main()
{

  int opcao;
  TipoRegistro x;
  TipoPagina * D;
  btImprime(D);
  btInicializa(&D);
  CriarIndPri(&x,&D);
  btImprime(D);
  opcao = menu();
  while(opcao != -1)
  {
    switch(opcao) {
      case 0:
              printf("Até mais!\n");

              getchar();
              return 0;
      case 3:
              printf("OI\n");
              break;
      case 2:
              printf("Arrombado!\n");
              break;
      default:
              printf("Opcao invalida\n");
              break;

		}
    opcao = menu();
  }

  free(D);

}
