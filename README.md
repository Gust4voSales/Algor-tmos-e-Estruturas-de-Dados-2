## 🌴 Binary Trees 
- [x] Binary Search Tree 
- [x]  AVL Tree
- [x] Red-black Tree

#### 🛠 How to run
  1. Go inside the "Arvores" folders, eg. ```cd Arvores/BST```
  2. Compile to an executable with ```gcc *.c  -o the_name_of_the_executable```, eg. ```gcc *.c  -o resultado```
  3. Run the program with ```./resultado```
#### 🚧 Testing
  1. Run the executable passing an input file (teste.in) and redirect the result to an output file (resultado.out) with 
  ```./resultado < teste.in > resultado.out```
  2. Compare the output file to a template file (teste_esperado.out) which contaims the expected result to the input file used before,  run ```diff teste_esperado.out resultado.out```
  
## 🧩 Graphs 
- [x] Kruskal's Algorithm (implemented with Adjacency Matrix representation)
- [x] Prim's Algorithm (implemented with Adjacency List representation)
- [x] Breadth first search (implemented with Adjacency Matrix representation)
- [x] Depth first search (implemented with Adjacency List representation)
#### 🛠 How to run
  1. Go inside the "Grafos" folders, eg. ```cd Grafos/AlgoritmoDeKruskal```
  2. Compile to an executable with ```g++ *.cpp  -o the_name_of_the_executable```, eg. ```g++ *.cpp  -o resultado```
  3. Run the program with ```./resultado```

## 📂 Files
This demo saves books in the disk and is also able to read them by implementing an indexing logic where we don't need to store the whole books' file in the memory, 
we use an index structure instead. In this case, an AVL tree.

Each node from the tree only stores the book's code and its index from the saved books' file, so we save a lot of
memory by storing the tree structure with only two integers (the book's index and key) as it's content, instead of the whole book info, which could become a problem if we say, 
we have 1.000.000 books for example. 

When we want to read a specific book, we simply search in the index structure (AVL tree) for its code, that tree node also contaims the 
index for that book from the data file, when we open it, we have the book's exactly position and only loads that book in the memory, not the the whole data file. 
It's an efficient memory use case implementation.

#### 🛠 How to run
  1. Go inside the "Arquivos" folder ```cd Arquivos```
  2. Compile to an executable with ```gcc *.c  -o the_name_of_the_executable```, eg. ```gcc *.c  -o resultado```
  3. Run the program with ```./resultado```
  
