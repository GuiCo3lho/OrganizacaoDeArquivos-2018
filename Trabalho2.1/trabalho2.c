#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <trabalho2.h>

int main()
{
  TipoRegistro x;
  TipoPagina * D;
  btImprime(D);
  btInicializa(&D);
  CriarIndPri(&x,&D);
  free(D);
}
