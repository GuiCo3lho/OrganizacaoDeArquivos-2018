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
  btInicializa(&D);
  btImprime(D);

  //btImprime(D);
  opcao = menu();
  while(opcao != -1)
  {
    switch(opcao) {
      case 0:
              printf("Até mais!\n");

              getchar();
              return 0;
      case 1:
              printf("Árvore B Criada!\n");
              CriarIndPri(&x,&D);
              break;
      case 2:
              printf("Árvore B virtual!\n");
              btImprime(D);
              break;
      case 3:
              printf("Indices gravados em indicelista.bt!\n");
              btGravarIndice(D);
              break;
      default:

              printf("Opcao invalida\n");
              break;

		}
    opcao = menu();
  }

  free(D);

}
