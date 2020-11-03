#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	grafo g;	
	char origem;		
	
	// inicializar(&g, 4); A função montar grafo já chama a função inicializar com o tamanho do grafo de acordo com o passado no arquivo de entrada
	montarGrafo(&g);	
	
	imprimir(&g);
	
	origem = 'D';	// O algoritmo buscaEmLargura irá partir do char que estiver em origem
	
	// buscarIndiceVertice retorna o indice do char passado. Ex: Se 'A' foi o primeiro vertice do grafo, buscarIndiceVertice(g, 'A') irá retornar 0
	buscaEmLargura(&g, buscarIndiceVertice(&g, origem)); 
}
