#ifndef GRAFO_H
#define GRAFO_H

enum cor { BRANCO, CINZA, PRETO };

typedef struct grafo {
	int v;
	char *mapa;
	int **matriz;
} grafo;

void inicializar (grafo *g, int tamanho);

void montarGrafo(grafo *g);

void imprimir(grafo *g);

void adicionarAresta(grafo *g, char v1, char v2);

int buscarIndiceVertice(grafo *g, char vertice);

void buscaEmLargura(grafo *g, int origem);

void imprimeCaminho(grafo *g, int *predecessores, int origem, int destino);

#endif
