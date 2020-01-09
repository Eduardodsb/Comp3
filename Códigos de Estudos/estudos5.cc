/*
- Templates
- Especialização de templates
- parâmetros constantes na template
- Parâmetros por omissão em métodos e construtores.

OBS: Compilar com -std=c++11
*/

#include<iostream>
#include<string.h>

using namespace std;

template <typename T>
const T& Max(const T &a, const T &b){
    return a > b ? a : b;
}

template <typename T>
T Max2(T a, T b){
    return a > b ? a : b;
}

template <>
const char* Max2( const char *a, const char *b){
    return  strcmp(a,b) > 0 ? a : b;
}

// Função template com parametro int
template <int N>
inline int escala( int x ) {
  return N * x;
}

int paramOmissao(int x = 0, int y = 0, int z = 0){ //Essa ideia tb pode ser aplicada em construtores.
    return x+y+z;
}

int main(int argc, char * argv[]){

    //Instanciação explícita
    cout << Max<int>(2.89,1.2) << endl;

    //Dedução automática
    cout << Max(2.65,2.3) << endl;
    //cout << Max(2, 2.001) << endl; //Neste caso ele fica confuso, entre usar int ou double.

    //Erro lógico
    cout << Max("eduu", "dudu") << endl; //pq só pode strings de mesmo tamanho?
    //Sem erro lógico. Fazendo uso da especialização.
    cout << Max2("Aeduu", "Zdudu") << endl;
    
    cout << escala<10>( 8 ) << endl;

    // Podemos obter o endereço de uma função template instanciando ela.
    int (*ptrFun)( int ) = &escala<7>;
    cout << ptrFun( 9 ) << endl;
  
    // Outra forma, mais prática:
    auto ptrFun2 = &escala<78>;
    cout << ptrFun2( 10 ) << endl;
    

//_______________________________________

    cout << paramOmissao(1) << endl;
    cout << paramOmissao(1,1) << endl;
    cout << paramOmissao(1,1,1) << endl;


    return 0;
}