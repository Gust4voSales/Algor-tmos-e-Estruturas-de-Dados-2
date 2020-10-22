#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	grafo g;			
	
	// inicializar(&g, 9); A função montar grafo já chama a função inicializar com o tamanho do grafo de acordo com o passado no arquivo de entrada
	montarGrafo(&g);	
	
	imprimir(&g);

	algoritmoPrim(&g);
}
