#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trabalho2.h"

int main()
{
  int opcao;
  TipoRegistro x;
  //TipoRegistro y;
  TipoPagina * D;
  
	// executar funções iniciais
	btInicializa(&D);
	btImprime(D);

	//btImprime(D);

	// igualar opção ao menu
	opcao = menu();

	// checar qual é a opção selecionada e executar o comando pedido
	while(opcao != -1)
	{
		switch(opcao) 
		{
			// opção 0: sair do programa
			case 0:
				printf("Até mais!\n");
				getchar();
				return 0;
			
			// opção 1: criar um índice primário
			case 1:
				printf("Árvore B Criada!\n");
				CriarIndPri(&x,&D);
				break;

			// opção 2: imprimir a árvore-B
			case 2:
				printf("Árvore B virtual!\n");
				btImprime(D);
				break;

			// opção 3: gravar os índices no arquivo	
			case 3:
				printf("Indices gravados em indicelista.bt!\n");
				btGravarIndice(D);
				break;

			// opção 4: ver o tipo do registro
			case 4:
				printf("Conteudos do TipoRegistro\n");
				btTipoRegistro(D);
				break;

			// opção 5: pesquisar um registro
			case 5:
				printf("Entre com a chave Primaria\n");
				btBuscarRegistro(D);
				break;
			
			case 6:
				IncluirRegistro();
				break;

			// opção inválida -> imprime mensagem de erro
			default:
				printf("Opcao invalida\n");
				break;
		}
	
		// iguala a opção ao menu
		opcao = menu();
	}

	free(D);

}

