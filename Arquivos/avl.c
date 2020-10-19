#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

int inicializarTabela(tabela *tab, int *controleFB) {
	inicializar(&tab->indices);	
	tab->arquivo_dados = fopen("dados.txt", "a+");
	tab->indices = carregar_arquivo("indices.dat", tab->indices, controleFB);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo("indices.dat", tab->indices);
}

void inserirLivro(tabela *tab, dado *livro, int *controleFB){
	if(tab->arquivo_dados != NULL) {
		int tamanhoLivro = 0;
		char * titulo;
		tamanhoLivro = (sizeof(livro->titulo) + sizeof(livro->autor) + sizeof(livro->ano) + sizeof(livro->codigo)); 		

		fseek(tab->arquivo_dados, 0L, SEEK_END);

		tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));
		novo->chave = livro->codigo;
		novo->indice = ftell(tab->arquivo_dados);
		
		//fwrite(livro, sizeof(livro), 1, tab->arquivo_dados);
		fprintf(tab->arquivo_dados, "%s|%s|%d|%d|", livro->titulo, livro->autor, livro->ano, livro->codigo);
		
		tab->indices = adicionar(novo, tab->indices, controleFB);
	} 
}

void buscarLivro(arvore raiz, tabela * tab, int codigoLivro) {
	arvore arvoreDesejada = buscarArvore(raiz, codigoLivro);

	imprimir_elemento(arvoreDesejada, tab);
}

arvore buscarArvore(arvore raiz, int chave) {
	if (raiz == NULL || raiz->dado->chave == chave) {
	       return raiz; 
	}

	if (raiz->dado->chave < chave) 
		return buscarArvore(raiz->dir, chave);
	else
		return buscarArvore(raiz->esq, chave);
}	

arvore adicionar (tipo_dado *valor, arvore raiz, int *cresceu) {
    //Caso base da recursão: ou a árvore está vazia ou chegou em uma folha
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
	  	* cresceu = 1; 
		return novo;
	}

    //Casos recursivos, se a raiz (relativa) não for NULL,        
    //acrescenta-se o elemento na sub-árvore direita ou esquerda,
    //dependendo do valor a ser inserido. Elementos maiores vão 
    //para direita, menores para esquerda.
	if(valor->chave > raiz->dado->chave) {
        //Elemento maior => adicionar na direita
		raiz->dir = adicionar(valor, raiz->dir, cresceu);
        //Após adicionar o elemento na direita, 
        //verifica se a sub-árvore da direita cresceu.
        //Em caso afirmativo, ajusta-se o fator de balanço 
        //da raiz relativa
        	if(*cresceu) {
            	//Chegando neste ponto, sabe se que:
            	//a) O elemento foi inserido na sub-árvore direita; e
            	//b) A sub-árvore a direita cresceu
			switch(raiz->fb) {
				case 0:
					raiz->fb = 1;
		            		*cresceu = 1;
					break;
			    	case -1:
					raiz->fb = 0;
					*cresceu = 0;
					break;
			   	case 1:
					*cresceu = 0;
		            		//o fator de balanço passaria ao valor 2,
					return rotacionar(raiz);
			}
		}
	} else {
       //Elemento menor que raiz relativa, fazer o caso simétrico
		raiz->esq = adicionar(valor, raiz->esq, cresceu);
		//Após adicionar o elemento na esquerda, 
		//verifica se a sub-árvore da esquerda cresceu.
		//Em caso afirmativo, ajusta-se o fator de balanço 
		//da raiz relativa
        	if(*cresceu) {
            	//Chegando neste ponto, sabe se que:
            	//a) O elemento foi inserido na sub-árvore esquerda; e
            	//b) A sub-árvore a esquerda cresceu
			switch(raiz->fb) {
				case 0:
					raiz->fb = -1;
		            		*cresceu = 1;
					break;
			    	case -1:
					*cresceu = 0;
		            		//o fator de balanço passaria ao valor -2,
					return rotacionar(raiz);
			   	case 1:
					raiz->fb = 0;
					*cresceu = 0;
					break;
			}
		}
	}
    	//Se tirar isso, caga a árvore toda
	return raiz;
}

arvore rotacionar(arvore raiz) {
    //fb maior que zero => rotação esquerda
	if(raiz->fb > 0) {
		switch(raiz->dir->fb) {
            	//o zero "conta" como rotação simples. 
            	//Só ocorre no remover
			case 0:
			case 1:
				return rotacao_simples_esquerda(raiz);
			case -1:
				return rotacao_dupla_esquerda(raiz);					
		} 
	} else {
    	//implementar o simétrico
		switch(raiz->esq->fb) {
            	//o zero "conta" como rotação simples. 
            	//Só ocorre no remover
			case 0:
			case -1:
				return rotacao_simples_direita(raiz);
			case 1:
				return rotacao_dupla_direita(raiz);					
		} 
	}
}

arvore remover (int valor, arvore raiz, int *diminuiu) {
	if(raiz == NULL) 
		return NULL;
	
	if(raiz->dado->chave == valor) {
		*diminuiu = 1;		
		
		if(raiz->esq == NULL) {				
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}

		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado->chave, raiz->esq, diminuiu);
		
		if (*diminuiu) {
			int h_esq, h_dir;
			h_esq = altura(raiz->esq);
			h_dir = altura(raiz->dir);
			if (h_dir-h_esq == 0) {
				raiz->fb = 0;
			} else if (h_dir-h_esq == 2){
				raiz = rotacionar(raiz);				
			} else {
				raiz->fb = 1;
			}
			
		}	
		*diminuiu = 0;		
		return raiz;
	}	
	if(valor > raiz->dado->chave) {
		raiz->dir = remover(valor, raiz->dir, diminuiu);

		if (*diminuiu) {
			switch(raiz->fb) {
				case 0:
					raiz->fb = -1;
		            		*diminuiu = 0;
					break;
			    	case -1:
					*diminuiu = 1;
		            		//o fator de balanço passaria ao valor -2,
					return rotacionar(raiz);
			   	case 1:
					raiz->fb = 0;
					//*diminuiu = 0;
					break;
			}
		}			
	} else {
		raiz->esq = remover(valor, raiz->esq, diminuiu);

		if (*diminuiu) {
			switch(raiz->fb) {
				case 0:
					raiz->fb = 1;
		            		*diminuiu = 0;
					break;
			    	case -1:
					raiz->fb = 0;
					//*diminuiu = 0;
					break;
					
			   	case 1:
					*diminuiu = 1;
		            		//o fator de balanço passaria ao valor -2,
					return rotacionar(raiz);
			}
		}	
	}
	
	return raiz;

}

arvore rotacao_simples_esquerda(arvore raiz) {
	arvore p, u, t1, t2, t3;
    	//inicializa os ponteiros
	p = raiz;
	u = raiz->dir;
	t1 = p->esq;
	//t2 e t3 não estão sendo modificados. 
	//só estão aqui por questões didáticas
	t2 = u->esq;
	t3 = u->dir;

    //Atualiza os ponteiros
	p->dir = t2;
	u->esq = p;
    
    //Atualiza os fatores de balanço de acordo com o fb de u
    //Esses valores vieram dos cálculos demonstrados na aula
	if(u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = 1;
		u->fb = -1;
	}	
    
    //Retorna a raiz da sub-árvore resultante, ou seja "u".
	return u;
}

arvore rotacao_dupla_esquerda(arvore raiz) {
	arvore p, u, v, t1, t2, t3, t4;
	//inicializa os ponteiros	
	p = raiz;
	u = raiz->dir;
	v = u->esq;
	t2 = v->esq;
	t3 = v->dir;
	//t1 e t4 não estão sendo modificados. 
	//só estão aqui por questões didáticas 
	t1 = p->esq;
	t4 = u->dir;

	//Primeiro, rotação simples direita no u
	p->dir = v;
	v->dir = u;
	u->esq = t3;
	//Segundo, rotação simples esquerda no p
	v->esq = p;
	p->dir = t2;
	
	//Calculo de balanço
	if(v->fb == 1) {
		p->fb = -1;
	} 
	else {
		p->fb = 0;
	} 
	if (v->fb == -1) {
		u->fb = 1;
	}
	else {
		u->fb = 0;
	}
	
	v->fb = 0;
	return v;
}

arvore rotacao_simples_direita(arvore raiz) {
	arvore p, u, t1, t2, t3;
    	//inicializa os ponteiros
	p = raiz;
	u = raiz->esq;
	t1 = p->dir;
	//t2 e t3 não estão sendo modificados. 
	//só estão aqui por questões didáticas
	t2 = u->esq;
	t3 = u->dir;

    	//Atualiza os ponteiros
	p->esq = t3;
	u->dir = p;
	
	//Atualiza os fatores de balanço de acordo com o fb de u
    	//Esses valores vieram dos cálculos demonstrados na aula
	if(u->fb == -1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = -1;
		u->fb = 1;
	}	

	return u;
}
arvore rotacao_dupla_direita(arvore raiz) {
	arvore p, u, v, t1, t2, t3, t4;
	//inicializa os ponteiros	
	p = raiz;
	u = raiz->esq;
	v = u->dir;
	t2 = v->esq;
	t3 = v->dir;
	//t1 e t4 não estão sendo modificados. 
	//só estão aqui por questões didáticas 
	t1 = u->esq;
	t4 = p->dir;

	//Primeiro, rotação simples esquerda no u
	p->esq = v;
	v->esq = u;
	u->dir = t2;
	//Segundo, rotação simples direita no p
	v->dir = p;
	p->esq = t3;
	
	//Calculo de balanço
	if(v->fb == -1) {
		p->fb = 1;
	} 
	else {
		p->fb = 0;
	} 
	if (v->fb == 1) {
		u->fb = -1;
	}
	else {
		u->fb = 0;
	}
	
	v->fb = 0;
	return v;
}



/*---
Imprime a árvore de modo a facilitar a visualização da estrutura, incluindo também o fator de balanço.
---*/
void imprimir(arvore raiz, tabela * tab) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		imprimir(raiz->esq, tab);
		imprimir(raiz->dir, tab);
	}
	printf(")");
}

void imprimir_elemento(arvore raiz, tabela * tab) {
	int * tam; 
	int contador = 0;
	char *buffer = malloc(256 * sizeof(char));
	//dado * temp = (dado *) malloc (sizeof(dado));

	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);

	while(contador<4) {
		fscanf(tab->arquivo_dados,"%c", buffer);
		if (buffer[0] == '|') {
			contador++;
			if (contador==4) printf(".\n");
			else printf(", ");		
			continue;	
		}
		
		printf("%c", buffer[0]);
	}

	free(buffer);
}


int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

tipo_dado * maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

tipo_dado * menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		pre_order(raiz->esq, tab);
		pre_order(raiz->dir, tab);
	}
}

void pos_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order(raiz->esq, tab);
		pos_order(raiz->dir, tab);
		imprimir_elemento(raiz, tab);
	}
}

void in_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order(raiz->esq, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->dir, tab);
	}
}



dado * ler_dados() {
	dado *novo = (dado *) malloc(sizeof(dado));
	char * buffer = (char *) malloc(256 * sizeof(char));
	int tamanhoDados = 0;

	getchar();
	
	printf("Titulo: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	tamanhoDados = ( (strlen(buffer) + 1) * sizeof(char) ) + tamanhoDados;
	/*	
	novo->titulo = (char *) malloc ((strlen(buffer) + 1) * sizeof(char));
	strcpy(novo->titulo, buffer);
	*/
	novo->titulo = strdup(buffer);

	printf("Autor: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	tamanhoDados = ( (strlen(buffer) + 1) * sizeof(char) ) + tamanhoDados;
	novo->autor = strdup(buffer);
	printf("Ano: ");
	scanf("%d", &novo->ano);
	tamanhoDados = sizeof(int) + tamanhoDados;
	printf("Codigo: ");
	scanf("%d", &novo->codigo);
	tamanhoDados = sizeof(int) + tamanhoDados;

	free(buffer);
	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}

}

arvore carregar_arquivo(char *nome, arvore a, int *controleFB) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
			
			a = adicionar(temp, a, controleFB);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);

	}
	return a;
}

