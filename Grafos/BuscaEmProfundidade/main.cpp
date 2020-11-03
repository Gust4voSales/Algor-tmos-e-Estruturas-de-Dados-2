#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	grafo g;	
	char origem;
	int tempo;		
	
	// inicializar(&g, 4); A função montar grafo já chama a função inicializar com o tamanho do grafo de acordo com o passado no arquivo de entrada
	montarGrafo(&g);
	
	imprimir(&g);
		
	buscaEmProfundidade(&g, &tempo); 
}
