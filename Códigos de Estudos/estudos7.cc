/*
- Iterator //Nada mais é do que um ponteiro para determinado objeto.
- For_Each
- Functor
- Expressões Lambda
*/

#include<iostream>
#include<string>
#include<vector>
#include <algorithm> //Necessário para o uso do for_each e do count_if

using namespace std;

void foo(int n){
    cout << n*2 << endl;
}

class PrintSqr {
public:
  PrintSqr( ostream& o ): o(o) {}
  
  void operator() ( int x ) {
    o << x * x << endl;
  }
  
private:
  ostream& o;
};

int main (int argc, char * argv[]){
//____________________________ITERATOR______________________________________________________________________________________
    cout << "ITERATOR" << endl << endl;
    vector<string> v = {"edu", "duda", "rafa" , "karen", "tata", "lipe"};
    vector<string>::iterator it;

    it = v.begin(); //OBS: v.end retorna o endereço da primeira posição disponível. 
    cout << *it << endl;
    // next, prev, advance
    //advance
    advance(it,2); //Altera pra quem o iterator it aponta
    cout << *it << endl;
    //next
    cout << *next(it,2) << endl; //Não altera o pra quem o iterator aponta, apenas retorna um ponteiro.
    cout << *it << endl;
    //prev
    cout << *prev(it,2) << endl; //Não altera o pra quem o iterator aponta, apenas retorna um ponteiro.
    cout << *it << endl;

    vector<int> v2 = {7, 1, 45 , 21, 8, 4};

    cout << *v2.begin() << endl;
    cout << *v2.end() << endl;

    cout << endl << "ITERATOR" << endl << endl;

//formas de imprimir:
//______________________FOR_EACH______________________________________________________________________________________________
    cout << "FOR_EACH" << endl << endl;
    for_each(v2.begin(), v2.end(), foo); //for_each(iterator, iterator, função qualquer)
    
    for(auto x : v){
        cout << x << " ";
    }
    cout << endl;

    cout << endl << "FOR_EACH" << endl << endl;

//______________________FUNCTOR______________________________________________________________________________________________
    cout << "FUNCTOR" << endl << endl;
   
    for_each( v2.begin(), v2.end(), PrintSqr( cerr ) ); //OBS: Usando um functor geralmente é mais otimizado do que usar uma função qaulquer. 
   
    cout << endl << "FUNCTOR" << endl << endl;

//______________________EXPRESSÕES_LAMBDA______________________________________________________________________________________________
    cout << "EXPRESSÕES_LAMBDA" << endl << endl;
    //Funções lambda não possui nome (função anônima). Pode ser declarada em qualquer parte do código e associada a variáveis ou métodos. 
    //[](){} == [captura de variáveis](parâmetro)->tipo_retorno{corpo da função}
    //Expressões lambda são functores.

    //Exemplo1
    auto maior = [](int n1, int n2)->int{return n1>=n2?n1:n2;};
    cout << maior(5,2) << endl;
    
    //Exemplo2
    //O [captura de variáveis] serve para capturar as variaveis declaradas no escopo. OBS [=] é equivalente a colocar todas as variaveis do escopo no [].
    int soma = 0;
    auto somador = [&soma](int x){ soma += x; };
    

    for_each( v2.begin(), v2.end(), somador); //OBS: Usando um functor geralmente é mais otimizado do que usar uma função qaulquer. 
    cout << soma << endl;

    auto somador2 = [=](int x){ return soma + x; }; //OBS: Caso essa linha estivesse antes do somador ser chamado (linha 93) o resultado seria 2 (considerando soma = 0)
    cout << somador2(2) << endl;

    //Exemplo3
    // Lambda pode ser ponteiro para função apenas se não tiver nada entre [].
    void (*f)(int) = [](int x){ cout << x << endl; };
    f(1996);

    //Exemplo4
    cout << "Possui " 
       << count_if( v2.begin(), v2.end(), [](int x){ return x % 2 != 0; } ) //cout_if(iterator, iterator, função) retorna a quantidade de elementos em que a condição da função foi verdadeira.
       << " números impares" << endl;
    
    cout << endl << "EXPRESSÕES_LAMBDA" << endl << endl;
    

    return 0;
}