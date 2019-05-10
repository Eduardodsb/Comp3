# Computação 3 - C++

Trabalhos realizados na disciplina de Computação 3. Tal disciplina tem como foco a aprendizagem de c++.

## Requisítos necessários:

### - Ambiente linux:

* g++
   
   comando para instalar o g++:<br>
   $ sudo apt-get update<br>
   $ sudo apt-get install g++

* Compilar e rodar

   g++ -o arquivo arquivo.cc -ansi -Wall --std=c++17 <br>
   ./arquivo

## - Trabalho 1

* classe
* vector
* Template
* Sobrecarga de operadores 

### Enunciado

"Implementar uma classe template Vetor<n,T> onde T deve ser numérico. As operações básicas de vetores geométricos devem estar implementadas.

Um Vetor em duas dimensões seria Vetor<2,double>.

Criar os operadores de multiplicação, adição e subtração de vetores. Lembrando que existe produto escalar e produto vetorial. Criar também multiplicação e divisão por escalar.

Bole uma forma do código abaixo compilar:

Vetor<2,double> v;
v = 4.5, 6.1;

O produto escalar será feito através de '*', e o produto vetorial, através de '**'.

Esse operador '**' não existe em C++, mas ele pode ser simulado através de 

v = a ** b;

Para isso você deve redefinir o operador '*' unário (ponteiro) para retornar uma classe intermediária (por exemplo, MeioDoProdutoVetorial) que contém o vetor b. Além disso, você deve redefinir o operador '*' entre um Vetor e a classe MeioDoProdutoVetorial para realizar o produto vetorial.

Por último, crie o operador '<<' para imprimir. "


## - Trabalho 2

* Função Apply
* Função Lambda
* Parâmetros template para template  
* Auto
* Decltype

### Enunciado

"Crie uma função apply que recebe um array (pode ser vector também, na verdade qualquer tipo iterável) e uma função F, e retorna uma estrutura do mesmo tipo passado mas com o tipo base sendo definido pelo valor de retorno de F.

Exemplo:

Entrada: [1, 2, 3, 4] vector<int> <br>
F = int sqr( int a ) { return a*a; } <br>
Saida: [ 1, 4, 9, 16 ] vector<int>

Se a função F for algo do tipo 

string romanos( int n ) { // blablaba } <br>
a saída será vector<string> => [ "I", "IV", "IX", "XVI" ]

Exemplo de uso:

vector<int> v; <br>
v.push_back( 1 ); <br>
v.push_back( 3 ); <br> 
v.push_back( 5 ); <br>
vector<double> s = apply( v, sin );"


## - Trabalho 3

* Stream
* Função Lambda
* Parâmetros template para template  

### Enunciado

"Implementar uma template que torne possível o seguinte tipo de código:

int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 }; <br>
vector<int> v{ 2 , 6, 8 }; <br>
tab | []( int x ) { cout << x*x << endl; }; <br>
tab | [ &v ]( int x ) { v.push_back( x ); }; <br>
v | []( int x ) { cout << x*x << endl; }; <br>
v | &print; <br>

onde print é uma função que recebe um int. 

void print( int x ) { cout << x << " "; }

Esse operador será equivalente a:

for_each( tab, tab+10,  []( int x ) { cout << x*x << endl; } );"

## - Trabalho 4
* Derivador Simbólico
* static_assert
* is_same 
* Template


### Enunciado

"
Nesta tarefa você deve criar templates, funções e operadores para permitir a criação de um derivador simbólico. A idéia é que você possa definir uma fórmula para uma função que recebe um parâmetro x e essa função possa ser chamada através do método e (passando um valor para x), e calculando também o valor da derivada dela em relação a x através do método dx.

Exemplos:

int main() { <br>
  auto f = 3.0 * x * x;<br>
  double v = 7;<br>
  
  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;<br>
}

Saida esperada:

f(7)=147, f'(7)=42

Além das expressões com os operadores aritméticos simples +, -, * e /, implementar as funções exp, log, sin e cos. Lembre-se de usar a regra da cadeia para sin(f(x)) funcionar.

Redefina o operador "->*" para aceitar int, significando:

x->*2 ==> x²

Gere um erro de compilação se "->*" for usado com um double: x->*0.5, por exemplo. A mensagem do erro deve ser: "Operador de potenciação definido apenas para inteiros".
"

## - Trabalho 5
* Derivador Simbólico
* static_assert
* is_same 
* Template


### Enunciado

Derivador Simbólico - Parte 2

Usando a solução da tarefa Derivador Simbólico, e efetuando as devidas correções e alterações, acrescente no derivador simbólico dois métodos: str e dx_str, com o cabeçalho abaixo:

string str() const;
string dx_str() const;

Esse métodos devem retornar a representação em string da função e de sua derivada. Não deve ser feita nenhuma simplificação, ou seja, saídas como (0 * x + 1 * 1) são aceitáveis e devem ser mantidas.

Na saída substitua o operador "->*" por "^".
