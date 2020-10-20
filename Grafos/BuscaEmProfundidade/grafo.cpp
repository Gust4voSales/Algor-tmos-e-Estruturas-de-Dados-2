#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <queue> 
#include "grafo.h"
#include <iostream>

using namespace std;

void inicializar (grafo *g, int tamanho) {
	//tamanho = 4;
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
  	g->listaAdj = (no**) malloc(tamanho * sizeof(no*));

	for (int i = 0; i < tamanho; i++)
		g->listaAdj[i] = NULL;	
}

lista* criarNo(int v) {
  lista* novoNo = (lista*) malloc(sizeof(lista));
  novoNo->vertice = v;
  novoNo->prox = NULL;
  return novoNo;
}


void montarGrafo(grafo *g) {
	FILE *arquivo_dados = fopen("grafo.in", "r");
	int num_vertices;
	int num_arestas;
	int contador_vertices = 0;
	
	fscanf(arquivo_dados, "%d %d", &num_vertices, &num_arestas);
	//printf("%d %d\n", num_vertices, num_arestas);
	
	// inicializo o grafo
	inicializar(g, num_vertices);
	
	char vertices[num_vertices];
	//char arestas[2][num_arestas];
    	char c, a1, a2;
		
	// Salvar os vertices
	for (int cont = 0; cont < num_vertices; cont++) {
		c = fgetc(arquivo_dados); // ler o \n
    		vertices[cont] = fgetc(arquivo_dados); // ler o char e salvar
	}
	
	// Adicionar os vertices ao mapa
	for (int i = 0; i<num_vertices; i++) {
		//printf("%c, ", vertices[i]);
		g->mapa[i] = vertices[i];
	}

	// Ler e adicionar arestas
	for (int cont = 0; cont < num_arestas; cont++) {
		fgetc(arquivo_dados); // ler o \n
		
		a1 = fgetc(arquivo_dados);
		a2 = fgetc(arquivo_dados);
		adicionarAresta(g, a1, a2);

		/*arestas[0][cont] = a1; // ler o char e salvar    		
		arestas[1][cont] = a2; // ler o char e salvar*/
	}
	
	fclose(arquivo_dados);
	/*for (int i = 0; i<num_arestas; i++) {
		printf("%c%c, ", arestas[0][i], arestas[1][i]);
	}*/ 
}

void imprimir(grafo *g) {
	for (int v = 0; v < g->v; v++) {
		lista* temp = g->listaAdj[v];
		printf("\n Vertice %c: ", g->mapa[v]);
		while (temp) {
			printf("%c, ", g->mapa[temp->vertice]);
			temp = temp->prox;
		}
	printf("\n");
	}
}

void adicionarAresta(grafo *g, char v1, char v2) {
	int pos1 = buscarIndiceVertice(g, v1);
	int pos2 = buscarIndiceVertice(g, v2);		
	
	// Adicionar aresta da pos1 para pos2
	lista* novoNo = criarNo(pos2);
	novoNo->prox = g->listaAdj[pos1];
	g->listaAdj[pos1] = novoNo;

	// Adicionar aresta da pos2 para pos1
	novoNo = criarNo(pos1);
	novoNo->prox = g->listaAdj[pos2];
	g->listaAdj[pos2] = novoNo;
}

int buscarIndiceVertice(grafo *g, char vertice) {
	for (int c = 0; c < g->v; c++) {	
		if (g->mapa[c] == vertice) {
			return c;
		}		
	}
	return -1;
}

void buscaEmProfundidade(grafo *g, int *tempo) {
	int tam = g->v;		
	cor *cores = (cor *) malloc(tam * sizeof(cor));
	int *predecessores = (int *) malloc(tam * sizeof(int));
	int *d = (int *) malloc(tam * sizeof(int));
	int *f = (int *) malloc(tam * sizeof(int));
	
	*tempo = 0;
	
	//Inicialização
	for (int c = 0; c < tam; c++) {
		cores[c] = BRANCO;	
		
		// Utilizar NULL aqui não funciona porque é um array de inteiros e NULL da erro
		predecessores[c] = -99999; 
	}
	
	for (int u = 0; u < g->v; u++) {
		if (cores[u] == BRANCO) {
			buscaEmProfundidadeVisita(g, predecessores, cores, d, f, tempo, u);
		}
	}
	
	
	// FIM DO ALGORITMO

	// Prints auxiliares para verificação
	printf("\n");
	printf("\n");
	for (int i = 0; i<tam; i++) {
		printf("%c(%d/%d)", g->mapa[i], d[i], f[i]);
		if (predecessores[i] != -99999)
			printf("\tPredecessor de %c -> %c\n", g->mapa[i], g->mapa[predecessores[i]]);
		else		
			printf("\t%c não tem predecessor\n", g->mapa[i]);
	}
}

void buscaEmProfundidadeVisita(grafo *g, int *predecessores, cor *cores, int *d, int *f, int *tempo, int u){
	lista* listaAdj = g->listaAdj[u];
	lista* temp = listaAdj;
	
	cores[u] = CINZA;
	*tempo = *tempo + 1;
	d[u] = *tempo;
	//printf("%d\n", *tempo);
	while (temp != NULL) {
		int verticeConectado = temp->vertice;

		if (cores[verticeConectado] == BRANCO) {
			predecessores[verticeConectado] = u;
			buscaEmProfundidadeVisita(g, predecessores, cores, d, f, tempo, verticeConectado);
		}
		temp = temp->prox;
	}
	
	cores[u] = PRETO;
	*tempo = *tempo + 1;	
	f[u] = *tempo;
}



