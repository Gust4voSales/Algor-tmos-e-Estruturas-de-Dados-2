#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char * argv[]) {
	tabela tab;
	int opcao;
	int controleFB;
	inicializarTabela(&tab, &controleFB);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						printf("%d\n", altura(tab.indices));
						break;
				case 2:
						inserirLivro(&tab, ler_dados(), &controleFB);
						break;
				case 3:
						printf("Código do livro: ");
						scanf("%d", &valor);
						buscarLivro(tab.indices, &tab, valor);
						break;
				case 4:
						pre_order(tab.indices, &tab);
						printf("\n");
						break;
				case 5:
						in_order(tab.indices, &tab);
						printf("\n");
						break;
				case 6:
						pos_order(tab.indices, &tab);
						printf("\n");
						break;

				case 7:
						salvar_arquivo("dados.txt", tab.indices);
						break;

				case 8:
						tab.indices = carregar_arquivo("indices.dat", tab.indices, &controleFB);
						break;
				case 99:
						finalizar(&tab);
						exit(0);
		}
	}
}
