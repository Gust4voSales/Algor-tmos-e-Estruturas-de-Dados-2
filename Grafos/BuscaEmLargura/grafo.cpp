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
	int i,j;
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
	g->matriz = (int **) malloc(sizeof(int *) * tamanho);
	for(i =0; i < tamanho; i++)
		g->matriz[i] = (int *) malloc(sizeof(int) * tamanho);

	for(i =0; i < tamanho; i++) {
		for(j=0; j < tamanho; j++) {
				if(i==j) {
					g->matriz[i][j] = 1;
				} else {
					g->matriz[i][j] = 0;
				}
		}
	}
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

void adicionarAresta(grafo *g, char v1, char v2) {
	int pos1 = buscarIndiceVertice(g, v1);
	int pos2 = buscarIndiceVertice(g, v2);		
	

	g->matriz[pos1][pos2] = 1;
	g->matriz[pos2][pos1] = 1;
}

int buscarIndiceVertice(grafo *g, char vertice) {
	for (int c = 0; c < g->v; c++) {	
		if (g->mapa[c] == vertice) {
			return c;
		}		
	}
	return -1;
}

void buscaEmLargura(grafo *g, int origem) {
	int tam = g->v;		
	int cores[tam];
	int *predecessores = (int *) malloc(tam * sizeof(int));
	int d[tam];
	queue <int> fila;

	//Inicialização
	for (int c = 0; c < tam; c++) {
		cores[c] = BRANCO;
		d[c] = 99999;		

		// Utilizar NULL aqui não funciona porque é um array de inteiros e NULL da erro
		predecessores[c] = -99999; 
	}
	cores[origem] = CINZA;
	d[origem] = 0;
	//predecessores[origem] = -99999; 
	fila.push(origem);

	while(!fila.empty()) {
		int u =  fila.front(); // Primeiro da fila
		fila.pop();

		// Percorrendo os adjacentes a U
		for (int v = 0; v < tam; v++) {
			if (g->matriz[u][v] == 1) {
				if (cores[v] == BRANCO) {
					cores[v] = CINZA;
					d[v] = d[u] + 1;
					predecessores[v] = u;
					fila.push(v);
				}
			}		
		}

		cores[u] = PRETO;
	}
	
	// FIM DO ALGORITMO

	// Funções auxiliares para verificação
	printf("\n");
	for (int c = 0; c<tam; c++) {
		if (d[c]==99999) 
			printf("Distância de %c para %c --> INFINITO\n", g->mapa[origem], g->mapa[c]);		
		else
			printf("Distância de %c para %c --> %d\n", g->mapa[origem], g->mapa[c], d[c]);		
	}
	printf("\n");
	for (int i = 0; i<tam; i++) {
		printf("Caminho da origem(%c) até %c: \t", g->mapa[origem], g->mapa[i]);
		imprimeCaminho(g, predecessores, origem, i);
		printf("\n");
	}
}

void imprimeCaminho(grafo *g, int *predecessores, int origem, int destino) {	
	if (origem == destino) {
		printf("-->%c", g->mapa[origem]);
	}
	else if (predecessores[destino] == -99999) {
		printf("Nenhum caminho de %c para %c existente.", g->mapa[origem], g->mapa[destino]);
	}
	else {
		imprimeCaminho(g, predecessores, origem, predecessores[destino]);
		printf("-->%c", g->mapa[destino]);	
	}
}

