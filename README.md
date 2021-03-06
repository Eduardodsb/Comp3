# Computação 3 - C++

Trabalhos realizados na disciplina de Computação 3. Tal disciplina tem como foco a aprendizagem de c++ e a mesma é lecionada pelo professor Geraldo Zimbrão.

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

"Derivador Simbólico - Parte 2

Usando a solução da tarefa Derivador Simbólico, e efetuando as devidas correções e alterações, acrescente no derivador simbólico dois métodos: str e dx_str, com o cabeçalho abaixo:

string str() const;
string dx_str() const;

Esse métodos devem retornar a representação em string da função e de sua derivada. Não deve ser feita nenhuma simplificação, ou seja, saídas como (0 * x + 1 * 1) são aceitáveis e devem ser mantidas.

Na saída substitua o operador "->*" por "^"."


## - Trabalho 6
* Filter
* is_same 
* Template

### Enunciado
"Acrescentar na tarefa anterior o conceito de filter. Um filter é um predicado que retorna bool, e somente repassa para o próximo "pipe" os elementos que retornarem verdadeiro.

Usando o exempla tarefa Stream:

v | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << endl; };

Irá imprimir apenas os números pares."


## - Trabalho 7
* Derivador Simbólico
* static_assert
* is_same 
* Template

### Enunciado
"Usando o Derivador construído na parte 2, remova todos os parênteses desnecessários, e removendo multiplicação por 1, 0, adição com 0 e potenciação a 0 e 1.
Exemplos:

Entrada: (x+3)->*2
Saída: f(x) = (x+3)^2, f'(x) = 2*(x+3) 

Entrada: (x)->*3
Saída: f(x) = x^3, f'(x) = 3*x^2 "


## - Trabalho 8
* Expressões Lambda
* invoke
* invoke_result
* is_same 
* Template

### Enunciado
Expressões Lambda Simplificadas

Tente fazer expressões lambda que permitam o programa abaixo compilar (e executar corretamente):

X x; // Declarar em algum lugar global.<br>
int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };.<br>
vector<int> v;.<br>
tab | cout << x*x << '\n';.<br>
tab | [ &v ]( int x ) { v.push_back( x ); };.<br>
v | x % 2 == 0 | cout << x*x + 1 << '\n';.<br>
v | x % 2 == 1 | x*x | cout << x << '\n';.<br>


## - Trabalho 9
* Expressões Lambda
* invoke
* invoke_result
* is_same 
* Template

### Enunciado
Usando as Expressões Lambda Simplificadas da tarefa anterior, faça com que o código abaixo rode também:

vector m< vector<int> >;
m | x[0] != 0 | ( x | cout << x << '\n' );
   
Nesse caso m é um vetor de vetores, e então o primeiro x é um vetor. Logo, podemos escrever um pipe para ele.
E será necessário redefinir o operador "[]" para Expressões Lambda.


## - Trabalho 10
* Bind
* invoke
* Variadic templates
* is_same 
* is_class
* is_invocable

### Enunciado
Classe Bind e função bind

Classe Bind 

Nesse trabalho você deve criar uma classe template Bind que recebe um functor/função e armazena esse functor, juntamente com possíveis parâmetros. Cada vez que uma função é ligada (binded) a um parâmetro, ela perde em n-aridade (ou seja, diminui o seu número de parâmetros). Ex: se uma função de dois parâmetros é ligada a um parâmetro, ela se torna uma nova função de apenas um parâmetro (o outro deve ser armazenado).

int mdc( int a, int b ) { return b == 0 ? a : mdc( b, a%b ); }<br>
auto f = bind( mdc, 12 ); <br>
// f é uma função de um parâmetro que calcula o mdc entre 12 e o parâmetro passado.  <br>
cout << f( 9 ) << endl; // deve imprimir 3, que é o mdc entre 12 e 9.<br>

Outros exemplos de uso:<br>

void func4( int a, string b, int c, double d ) {
  // Faz algum processamento
}<br>


int main() {
  auto f3 = bind( func4, 5 );

  cout << f3( "b", 7, 2.1 ) << endl;
 
  auto f2 = bind( f3, "b" );
  auto f2_a = f3( "b" );
  auto f2_b = f3( "b" );
  auto f1 = f3( "b", 8 );

  cout << f1( 1.1 ) << endl; 
  cout << f2( 2, 1.1 ) << endl; 
  cout << f2_a( 2, 1.1 ) << endl; 
  cout << f2_b( 2, 1.1 ) << endl; 
}

Note que devemos declarar uma função auxiliar bind, embora poderia ser possível usar a sintaxe Bind{ func4, 1, "a" };


## - Trabalho 11
* invoke
* invoke_result
* is_same 

### Enunciado
Otimizador de Expressões

Um otimizador de expressões para Matrizes é um conjunto de classes e operadores que, dada uma expressão de matrizes envolvendo "+" e "*" (por exemplo, A*B + C) escolhe a ordem de execução com menor número de operações de soma e multiplicação (e que por isso deve ter a execução mais rápida). Por exemplo, (A*B)*C pode ser bem mais lento do que A*(B*C), embora o resultado seja idêntico (basta que A seja uma matriz-coluna, B uma matriz-linha e C uma matriz quadrada).

Nessa tarefa você deve construir um tipo template Matriz<L,C> para double e os respectivos operadores de multiplicação e adição de matrizes, bem como uma operação para aplicar uma função à uma matriz.

Exemplo de declarações válidas:

innt main() {
  Matriz<10,20> a;
  Matriz<20,3> b;
  auto c = a*b;
  
// aplicar uma função à uma matriz:
  
  auto f = Apply( []( double x ){ return rand(); } );
  
  c = f(c);
  /* Vai calcular c[i][j] = g( c[i][j] ); */
  auto d = f(a) * b;
  
  for( int i = 0; i < d.nLin(); i++ )
    for( int j = 0; j < d.nCol(); j++ )
      cout << d[i][j] << endl;
  
  return 0;  
}
