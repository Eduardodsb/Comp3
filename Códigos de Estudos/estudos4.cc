/*
- Incialização de Atributos (Bloco 1 e Bloco 2)
- Const (Bloco 1 e Bloco 2)
- Vector (Bloco3 e Bloco4)

OBS: Compilar com -std=c++11
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;
/*Bloco1{*/
class Base{
    private:
    int idade = 0; //Inicializando na declaração.
    string nome;

    public:
    Base(string no): nome(no){ //Inicializando no construtor.
    }

    int imprime(int const idade){ //(int const idade) >> const impede que o valor de idade seja alterado. OBS: a const é por vavriável. 
        cout << nome << endl;
        this->idade = idade;
        //idade = idade + 2;
        return this->idade;
    }

    Base const soma_idade(int idade){
       // this->idade = idade;
      //  idade = idade + 2;
        return *this;
    }
    
};
/*}Bloco1*/

/*Bloco3{*/

void teste_vector( vector<int> *v ) {//Foi passado o endereço do objeto vector
  (*v)[2] = 35;
  
  cout << "Dentro de teste_vector => " <<(*v)[2] << endl;
}

void teste_vector2( vector<int> &v ) {//POR REFERÊNCIA
  v[3] = 45;
  
  cout << "Dentro de teste_vector2 => " <<v[3] << endl;
}

void teste_vector3( vector<int> v ) { //Cópia do objeto vector
  v[1] = 12365;
  
  cout << "Dentro de teste_vector3 => " <<v[1] << endl;
}
/*}Bloco3*/

int main(int argc, char * argv[]){
/*Bloco2{*/
    int A;
    Base p("Edu");
    vector<int> v;

    A = p.imprime(5) + 6;
    cout << A << endl;
    //p.soma_idade(5).soma_idade(5); // Não funciona pois o const de soma_idade impede que o objeto seja alterado. Não consigo nem mesmo chamar uma função.

/*}Bloco2*/

/*Bloco4{*/
    v.push_back( 9 );//Inserir valores no vector v.
    v.push_back( 7 );
    v.push_back( 12 );
    v.push_back( 88 );    
    v[0] = 5; //Podemos usar a notação de vetor tb. 

    teste_vector(&v);
    teste_vector2(v);
    teste_vector3(v);
    cout <<  v[2] << endl;

    for(auto x : v) //O auto tenta adivinhar o tipo de V deste modo definindo x com o tipo correto. 
        cout<< x  << " ";
    cout << endl;

/*}Bloco4*/

    return 0;
}