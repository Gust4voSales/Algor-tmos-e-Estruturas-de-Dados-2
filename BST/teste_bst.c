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
		no* resNo;
		int resInt;
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
			resNo = maior(arvore);
			printf("%d ", resNo->chave);				
                	break;
		case 7:
			resNo = menor(arvore);
			printf("%d ", resNo->chave);				
                	break;
		case 8:
			resInt = altura(arvore);
			printf("%d ", resInt);				
                	break;
		case 9:
			resInt = quantidade_elementos(arvore);
			printf("%d ", resInt);				
                	break;
		case 10:
			scanf("%d", &chave); 
			resInt = existe(arvore, chave);
			printf("%d ", resInt);				
                	break;
		case 11:
			resNo = predecessor(arvore);
			printf("%d ", resNo->chave);				
                	break;
		case 12:
			resNo = sucessor(arvore);
			printf("%d ", resNo->chave);				
                	break;
		default:
			;
		}

	} while(opcao != 99);
}	
