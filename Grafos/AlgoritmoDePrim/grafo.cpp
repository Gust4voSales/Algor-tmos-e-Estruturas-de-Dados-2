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

lista* criarNo(int v, int peso) {
  lista* novoNo = (lista*) malloc(sizeof(lista));
  novoNo->vertice = v;
  novoNo->peso = peso;
  novoNo->prox = NULL;
  return novoNo;
}


void montarGrafo(grafo *g) {
	FILE *arquivo_dados = fopen("grafo.in", "r");
	int num_vertices;
	int num_arestas;
	int contador_vertices = 0;
	int peso;
	
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
		fscanf(arquivo_dados, " %d", &peso);
	
		adicionarAresta(g, a1, a2, peso);

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
			printf("%c(%d), ", g->mapa[temp->vertice], temp->peso);
			temp = temp->prox;
		}
	printf("\n");
	}
}

void algoritmoPrim(grafo *g) {
	int pais[g->v];
	int chaves[g->v];
	int cores[g->v];

	for (int c = 0; c < g->v; c++) {
		cores[c] = BRANCO;
		chaves[c] = INFINITO;
	}
	chaves[0] = 0;
	pais[0] = -1; // Primeiro vertice é o pai da arvore.
	
	for (int c = 0; c < g->v; c++) {
		int u = menorVertice(g, chaves, cores);		
					
		cores[u] = PRETO;

		lista* temp = g->listaAdj[u];
		while(temp != NULL) {
			if (cores[temp->vertice]==BRANCO && temp->peso < chaves[temp->vertice]) {
				pais[temp->vertice] = u;
				chaves[temp->vertice] = temp->peso;
			}

			temp = temp->prox;
		}
		
	}


	// FIM DO ALGORITMO 


	//PRINTS AUXILIARES PARA VERIFICAÇÂO
	int pesoTotal = 0;
	printf("\nArvore Minima: \n");
	for (int c=0; c < g->v; c++) {
		int peso = retornarPesoAresta(g, c, pais[c]);
		pesoTotal += peso;
		printf("%c--%d--%c\n", g->mapa[pais[c]], peso, g->mapa[c]);
	}
	printf("Peso total: %d\n", pesoTotal);

}

int menorVertice(grafo *g, int chaves[], int cores[]) {
	int min_index;
	int min = INFINITO;

	for (int c=0; c < g->v; c++){
		if (cores[c]==BRANCO && chaves[c] < min){
			min = chaves[c];
			min_index = c;
		}
	}
	return min_index;
}

int retornarPesoAresta(grafo *g, int v1, int v2) {
	lista *temp = g->listaAdj[v1];

	while(temp) {
		if (temp->vertice == v2) {
			return temp->peso;
		}		

		temp = temp->prox;		
	}
	return 0;
}

void adicionarAresta(grafo *g, char v1, char v2, int peso) {
	int pos1 = buscarIndiceVertice(g, v1);
	int pos2 = buscarIndiceVertice(g, v2);		
	
	// Adicionar aresta da pos1 para pos2
	lista* novoNo = criarNo(pos2, peso);
	novoNo->prox = g->listaAdj[pos1];
	g->listaAdj[pos1] = novoNo;

	// Adicionar aresta da pos2 para pos1
	novoNo = criarNo(pos1, peso);
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





