/*Estudos Slide1

- Referência (Bloco1)
- Construtor de cópia (Bloco2)
- Operador de Atribuição (Bloco3)
- Redefinição de operador fora da classe (Bloco4)

*/

#include<iostream>
#include<string.h>

using namespace std;
/*Bloco2{*/
class Pessoa{
    public:
        char* nome;
        int idade, cpf;

    public:
        Pessoa(char *nome, int idade, int cpf){/*Construtor*/
            this->nome = nome;
            this->idade = idade;
            this->cpf = cpf;
        }
        //OBS1: O construtor de cópia é chamado sempre que o objeto for passado ou retornado por valor).
        //OBS2: Se nenhum construtor de cópia, for declarado, será criado um default. O mesmo aplicará o construtor de cópia correspondente a cada dado da classe.
        Pessoa(const Pessoa &A){ // Construtor de cópia
            this->nome = A.nome;
            this->idade = A.idade + 20;
            this->cpf = A.cpf;
        }

/*Bloco3{*/
        const Pessoa& operator+ (const Pessoa &A){
            nome = "Nome1+Nome2"; // Nome, idade, cpf, this é tudo em relação ao objeto que chamou a função
            idade = A.idade+10;
            cpf = cpf + A.cpf;
            return *this;
        }
/*}Bloco3*/

        

};

Pessoa foo(Pessoa a){
    cout << "Idade do objeto cópia:";
    cout << a.idade << endl;
    return a;
}
/*}Bloco2*/

/*Bloco1{*/
void troca_C( int *a, int* b ) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

void troca_Cplusplus( int& a, int& b ) { //A grande diferença é que desta forma não podemos acessar endereço de x e y declarados na main
  int aux = a;
  a = b;
  b = aux;
}
/*}Bloco1*/

/*Bloco4{*/
int operator* (double A, Pessoa B) { //O primeiro argumento "A" é o (4) na linha 115 e o segundo "B" é o objeto P4. OBS: diferente do que ocorre quando definido dentro da classe, onde o próprio objeto é um dos argumentos.
    cout<< B.idade<<endl;
    return A * B.idade - 5;
}
/*}Bloco4*/
int main(int argc, char * argv[]){
/*Bloco1{*/
  int x = 10, y = 20;
  
  troca_C( &x, &y );
  cout << "x = " << x << " ; y =" << y<< endl;
  
  troca_Cplusplus( x, y );
  cout << "x = " << x << " ; y =" << y<< endl;
/*}Bloco1*/

/*Bloco2{*/
    Pessoa P1("Eduardo", 22, 161854);
    cout << P1.nome << endl;
    cout << foo(P1).idade << endl; //Idade após retornar (ocorreu a chamada do contrutor de cópia):
/*}Bloco2*/

/*Bloco3{*/
   /* Pessoa *P2 = new Pessoa("Duda", 8, 123456);
    Pessoa *P3 = new Pessoa("Dudu", 10, 1);
    Pessoa *R;*/ //Não consegui declarando os objetos desse modo pq?

    Pessoa P2("Duda", 8, 123456);
    Pessoa P3("Dudu", 22, 1);
    Pessoa R("", 0, 0);    

    R = P3 + P2; //É equivalente à : R = (P3).operator+(P2);
   
    cout << "Nome de P2: " << P2.nome << endl << "Idade de P2:" << P2.idade << endl <<"cpf de P2: "<< P2.cpf << endl << endl;
    
    cout << "Nome de P3: " << P3.nome << endl << "Idade de P3:" << P3.idade << endl <<"cpf de P3: "<< P3.cpf << endl << endl;

    cout << "Nome de R: " << R.nome << endl << "Idade de R:" << R.idade << endl <<"cpf de R: "<< R.cpf << endl << endl;

    /*delete P2;
    delete P3;
    delete R;*/
/*}Bloco3*/

/*Bloco4{*/
    Pessoa P4("Eu", 5, 0); 
    cout<< 4*P4<< endl;
/*}Bloco4*/

}