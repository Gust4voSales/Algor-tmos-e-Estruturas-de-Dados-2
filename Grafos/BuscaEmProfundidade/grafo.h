#ifndef GRAFO_H
#define GRAFO_H

enum cor { BRANCO, CINZA, PRETO };

typedef struct no {
  int vertice;
  struct no* prox;
} lista;

lista* criarNo(int);

typedef struct grafo {
	int v;
	char *mapa;
	struct no** listaAdj;
} grafo;

void inicializar (grafo *g, int tamanho);

void montarGrafo(grafo *g);

void imprimir(grafo *g);

void adicionarAresta(grafo *g, char v1, char v2);

int buscarIndiceVertice(grafo *g, char vertice);

void buscaEmProfundidade(grafo *g, int *tempo);

void buscaEmProfundidadeVisita(grafo *g, int *predecessores, cor *cores, int *d, int *f, int *tempo, int u);

#endif
