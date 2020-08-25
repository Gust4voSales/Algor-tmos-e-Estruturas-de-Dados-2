#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


no* inserir(no *raiz, int chave) {
	//Caso Base
	if(raiz == NULL) {
		no * novo;
		//Passo 1 - Alocar memória
		novo = (no*) malloc (sizeof(no)); 
		//Passo 2 - Inicializar Valores
		novo->chave = chave;
		novo->esq = NULL;
		novo->dir = NULL;
		//Passo 3 - Retornar o ponteiro para o nó que foi criado
		return novo;
	} else {
		//Verificar se o valor deve ser inserido na esquerda (<) ou direita (>)
		if(chave > raiz->chave) {
			raiz->dir = inserir(raiz->dir, chave);
		} else {
			raiz->esq = inserir(raiz->esq, chave);				
		}
		return raiz;		
	}
}

void preorder(no *raiz) {
	if(raiz != NULL) {
		printf("[%d]", raiz->chave);
		preorder(raiz->esq);
		preorder(raiz->dir);
	}
}

void inorder(no *raiz) {
	if (raiz != NULL) {
		inorder(raiz->esq);
		printf("[%d]", raiz->chave);
		inorder(raiz->dir);
	}
}

void posorder(no *raiz) {
	if (raiz != NULL) {
		posorder(raiz->esq);
		posorder(raiz->dir);
		printf("[%d]", raiz->chave);
	}
}

no* remover(no *raiz, int chave) {
	if (raiz == NULL) {
		return raiz;
	}

	if (chave < raiz->chave) {
		raiz->esq = remover(raiz->esq, chave);	
	} else if (chave > raiz->chave) {
		raiz->dir = remover(raiz->dir, chave);
	}
	// A raiz que é pra ser removida
	else {
		if (raiz->esq == NULL) {
			no *temp = raiz->dir; 
			free(raiz); 
			return temp; 
		} else if (raiz->dir == NULL) {
			no *temp = raiz->esq; 
			free(raiz); 
			return temp; 		
		}

		// Raiz tem dois filhos
		no *temp = raiz->esq; 
		raiz->chave = temp->chave;

		raiz->esq = remover(raiz->esq, temp->chave);
	} 

	return raiz;
}

no* maior(no *raiz) {
	no* noAtual = raiz;
	
	while(noAtual && noAtual->dir != NULL) {
		noAtual = noAtual->dir;
	}
	
	return noAtual;
}

no* menor(no *raiz) {
	no* noAtual = raiz;
	
	while(noAtual && noAtual->esq != NULL) {
		noAtual = noAtual->esq;
	}
	
	return noAtual;
}

int altura(no *raiz) {
	if (raiz == NULL) {
		return 0;
	}
	
	int extensaoLadoDir = altura(raiz->dir);
	int extensaoLadoEsq = altura(raiz->esq);
	// Maior extensão será a altura da arvore
	if (extensaoLadoDir > extensaoLadoEsq) {
		return extensaoLadoDir + 1;
	} 
	return extensaoLadoEsq + 1;
}

























