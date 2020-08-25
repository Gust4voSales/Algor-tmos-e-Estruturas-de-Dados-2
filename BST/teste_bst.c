#include <stdio.h>
#include "bst.h"

int main(int argc, char *argv[]) {
	no * arvore;
	//inicialização da arvore
	arvore = NULL;
	int opcao;
	do {
		scanf("%d", &opcao);
		switch(opcao) {
		no* resultado;
                int chave;
    		case 1: 
        		scanf("%d", &chave);                
			arvore = inserir(arvore, chave);
                	break;
		case 2:
			preorder(arvore);
			printf(" ");				
                	break;
		case 3: 
			inorder(arvore);
			printf(" ");
			break;
		case 4: 
			posorder(arvore);
			printf(" ");
			break;
		case 5: 
			scanf("%d", &chave);  
			remover(arvore, chave);
			break;
		case 6:
			resultado = maior(arvore);
			printf("%d ", resultado->chave);				
                	break;
		case 7:
			resultado = menor(arvore);
			printf("%d ", resultado->chave);				
                	break;
		default:
			;
		}

	} while(opcao != 99);
}	
