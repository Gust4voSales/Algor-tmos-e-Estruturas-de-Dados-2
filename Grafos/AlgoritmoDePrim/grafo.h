#ifndef GRAFO_H
#define GRAFO_H

#define INFINITO 999999

enum cor { BRANCO, PRETO };

typedef struct no {
  int vertice;
  int peso;
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

void adicionarAresta(grafo *g, char v1, char v2, int peso);

int buscarIndiceVertice(grafo *g, char vertice);

void algoritmoPrim(grafo *g);

int menorVertice(grafo *g, int chaves[], int cores[]);

int retornarPesoAresta(grafo *g, int v1, int v2);

#endif
