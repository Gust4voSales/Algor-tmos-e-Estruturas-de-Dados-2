## 🌴 Árvores Binárias 
- [x] Árvore Binária de Busca 
- [x] Árvore AVL
- [x] Árvore Vermelho-Preta

#### 🛠 Como rodar
  1. Entre em alguma pasta dentro do diretório "Arvores", exemplo: ```cd Arvores/BST```
  2. Compile para um executável com ```gcc *.c  -o nome_do_executavel```, exemplo: ```gcc *.c  -o resultado```
  3. Rode o programa com ```./resultado```
#### 🚧 Teste
  1. Rode o executável passando o arquivo de entrada (teste.in) e redirecione o resultado para um arquivo de saída(resultado.out) com
  ```./resultado < teste.in > resultado.out```
  2. Compare o arquivo de sáida com o arquivo de gabarito (teste_esperado.out) que contém o resultado esperado para o arquivo de entrada usado antes, rode ```diff teste_esperado.out resultado.out```
  
## 🧩 Grafos 
- [x] Algorítmo de Kruskal (implementado com a representação Matriz de Adjacência) 
- [x] Algorítmo de Prim (implementado com a representação Lista de Adjacência)
- [x] Busca em Largura (implementado com a representação Matriz de Adjacência)
- [x] Busca em Profundidade (implementado com a representação Lista de Adjacência)
#### 🛠 Como rodar
  1. Entre em alguma pasta dentro do diretório "Grafos", exemplo: ```cd Grafos/AlgoritmoDeKruskal```
  2. Compile para um executável com ```g++ *.cpp  -o nome_do_executavel```, exemplo: ```g++ *.cpp  -o resultado```
  3. Rode o programa com ```./resultado```

## 📂 Arquivos
Esse demo salva livros no disco e também é capaz de lê-los ao implementar uma lógica de indexação onde não é necessário salvar todo o arquivo dos livros na memória, 
invés disso, nós usamos uma estrutura de indexação. Nesse caso, uma Árvore AVL.

Cada nó da árvore armazena apenas o código do livro e seu índice do arquivo dos livros salvos, então estamos economizando muita memória ao armazenar apenas dois inteiros
(o código e o índice do livro) como conteúdo da estrutura da árvore, no lugar de salvar toda as informações dos livros, o que se tornaria um problema, se tivéssemos, por exemplo,
1.000.000 de livros.

Quando precisamos ler um livro específico, apenas fazemos uma pesquisa na estrutura de indexação (Árvore AVL) pelo seu código, este nó também contém o índice daquele livro
do arquivo de dados, quando o abrimos, já temos a exata posição do livro que queremos, então apenas carregamos ele na memória, não o arquivo de dados inteiro.
É uma implementação eficiente de uso de memória. 

#### 🛠 Como rodar
  1. Entre no diretório "Arquivos" com ```cd Arquivos```
  2. Compile para um executável com ```gcc *.c  -o nome_do_executavel```, exemplo: ```gcc *.c  -o resultado```
  3. Rode o programa com ```./resultado```
