#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

/*----------
Adiciona um novo elemento à árvore e realiza as operações de balanceamento, se necessário
Parâmetros:
    valor   - elemento a ser inserido
    raiz    - raiz da árvore onde o elemento será inserido
    cresceu - variável de controle que ajuda a calcular o fator de balanço

Retorno:
    Raiz da árvore resultante da operação de adicionar
--*/

arvore adicionar (int valor, arvore raiz, int *cresceu) {
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
	if(valor > raiz->dado) {
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

/*----------
Verifica o tipo de rotação que deve ser aplicado para reajustar a árvore
Parâmetros:
    raiz - pivô (ou raiz da sub-árvore que se encontra 
    com o |fb| = 2 ) 
Retorno:
    raiz da sub-árvore resultante
---*/
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
	
	if(raiz->dado == valor) {
		*diminuiu = 1;		
		
		if(raiz->esq == NULL) {				
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}

		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado, raiz->esq, diminuiu);
		
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
	if(valor > raiz->dado) {
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

/*-------
Realiza a rotação simples esquerda sobre o pivô "raiz" e 
retorna a raiz relativa da árvore resultante 

      p
     / \
    t1  u
       / \
      t2 t3

     =>

      u
     / \
    p  t3
   / \
  t1 t2

-------*/
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
	p->dir = t1;
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
void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

/*---
Auxiliar de imprimir
---*/
void imprimir_elemento(arvore raiz) {
	printf("%d [%d]", raiz->dado, raiz->fb);
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

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

