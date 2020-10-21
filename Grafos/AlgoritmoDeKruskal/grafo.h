#ifndef GRAFO_H
#define GRAFO_H

#define MAX_ARESTAS 40

enum cor { BRANCO, CINZA, PRETO };

typedef struct grafo {
	int v;
	char *mapa;
	int **matriz;
} grafo;

typedef struct aresta {
	char v1;
	char v2;
	int peso;

} aresta;

// Lista que vai conter as arestas pro algoritmo 
typedef struct lista_arestas {
  aresta dado[MAX_ARESTAS];
  int n; //qntd de arestas
} lista_arestas;

void inicializar (grafo *g, int tamanho);

void montarGrafo(grafo *g);

void algoritmoKruskal(grafo *g);

int find_set(int pertence[], int vertice);

void uniao(grafo *g, int pertence[], int v1, int v2);

void ordernarArestas(grafo *g, lista_arestas *listaDeArestas);

void imprimir(grafo *g);

void adicionarAresta(grafo *g, char v1, char v2, int peso);

int buscarIndiceVertice(grafo *g, char vertice);

#endif
