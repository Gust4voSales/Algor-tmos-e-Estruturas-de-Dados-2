#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <set> 
#include <iterator> 
#include "grafo.h"
#include <iostream>

using namespace std;

void inicializar (grafo *g, int tamanho) {
	//tamanho = 4;
	int i,j;
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
	g->matriz = (int **) malloc(sizeof(int *) * tamanho);
	for(i =0; i < tamanho; i++)
		g->matriz[i] = (int *) malloc(sizeof(int) * tamanho);

	for(i =0; i < tamanho; i++) {
		for(j=0; j < tamanho; j++) {
			g->matriz[i][j] = 0;
				/*if(i==j) {
					g->matriz[i][j] = 1;
				} else {
					g->matriz[i][j] = 0;
				}*/
		}
	}
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
		//fgetc(arquivo_dados); // ler o espaço
		fscanf(arquivo_dados, " %d", &peso);
		
		//printf("%c%c = %d\n", a1, a2, peso);			
		adicionarAresta(g, a1, a2, peso);
	}
	
	fclose(arquivo_dados);
}

void imprimir(grafo *g) {
	int i,j;

	printf("\n");
	for(j = 0; j < g->v; j++) {
		printf("\t%c", g->mapa[j]);
	}
	printf("\n");

	for(i =0; i < g->v; i++) {
		printf("%c", g->mapa[i]);	
		for(j = 0; j < g->v; j++) {			
			printf("\t%d", g->matriz[i][j]);
		}					
		printf("\n");
	}
}

void algoritmoKruskal(grafo *g) {
	lista_arestas listaDeArestas;
	lista_arestas listaMST;
	aresta temp;
	int pertence[g->v];
	
	listaDeArestas.n = 0;		
	
	// Adicionar arestas na lista de arestas 
	for (int i = 1; i < g->v; i++) {
		for (int j = 0; j < i; j++) {
			if (g->matriz[i][j] != 0) {
				temp.v1 = g->mapa[i];				
				temp.v2 = g->mapa[j];
				temp.peso = g->matriz[i][j];

				listaDeArestas.dado[listaDeArestas.n] = temp;
				listaDeArestas.n++;	
			}
		}
	}
	
	// ordernar as arestas pelo peso
	ordernarArestas(g, &listaDeArestas);
	
	// Criar um set para cada vertice do grafo
	for (int c=0; c < g->v; c++) {
		pertence[c] = c;
	}
	
	listaMST.n = 0;
	
	for(int c = 0; c < listaDeArestas.n; c++) {
		int verticeIndex1 = buscarIndiceVertice(g, listaDeArestas.dado[c].v1);
		int verticeIndex2 = buscarIndiceVertice(g, listaDeArestas.dado[c].v2);

		int vert1 = find_set(pertence, verticeIndex1);
		int vert2 = find_set(pertence, verticeIndex2);


		if (vert1 != vert2) {
			listaMST.dado[listaMST.n] = listaDeArestas.dado[c];
			listaMST.n = listaMST.n + 1;
			uniao(g, pertence, vert1, vert2);
		}
	}
	
	// FIM DO ALGORITMO

	// Prints auxiliar para verificação
	int pesoTotal = 0;
	for (int c=0; c < g->v; c++) {
		printf("%c---%d---%c\n", listaMST.dado[c].v1, listaMST.dado[c].peso, listaMST.dado[c].v2);
		pesoTotal+= listaMST.dado[c].peso;
	}
	printf("Peso minímo total: %d\n", pesoTotal);
}

int find_set(int pertence[], int vertice) {
	return pertence[vertice];
}

void uniao(grafo *g, int pertence[], int v1, int v2) {
  int i;

  for (i = 0; i < g->v; i++)
    if (pertence[i] == v2)
      pertence[i] = v1;
}

void ordernarArestas(grafo *g, lista_arestas *listaDeArestas) {
	aresta temp;
	
	for (int i = 1; i < listaDeArestas->n; i++) {
		for (int j = 0; j < listaDeArestas->n - 1; j++) {
			if (listaDeArestas->dado[j].peso > listaDeArestas->dado[j + 1].peso) {
				temp = listaDeArestas->dado[j];
				listaDeArestas->dado[j] = listaDeArestas->dado[j + 1];
				listaDeArestas->dado[j + 1] = temp;
			}
		}
	}
	
	printf("Arestas ordenadas por peso:\n");
	for (int c=0; c<listaDeArestas->n; c++) {
		printf("%c%c = %d\n", listaDeArestas->dado[c].v1, listaDeArestas->dado[c].v2, listaDeArestas->dado[c].peso);
	}
	printf("\n");
}


void adicionarAresta(grafo *g, char v1, char v2, int peso) {
	int pos1 = buscarIndiceVertice(g, v1);
	int pos2 = buscarIndiceVertice(g, v2);		
	

	g->matriz[pos1][pos2] = peso;
	g->matriz[pos2][pos1] = peso;
}

int buscarIndiceVertice(grafo *g, char vertice) {
	for (int c = 0; c < g->v; c++) {	
		if (g->mapa[c] == vertice) {
			return c;
		}		
	}
	return -1;
}


