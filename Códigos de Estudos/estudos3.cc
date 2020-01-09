/*Estudos Slide1

- Herança
- Classe abstrata 
- Métodos virtuais 
- Const (Métodos podem ser const se não alterarem nenhum campo do objeto)

*/

#include<iostream>
#include<string.h>

using namespace std;


/*OBS CLASSE ABSTRATA: Percebam, primeiramente, que em C++ a declaração da classe abstrata não ocorre explicitamente. Ela se torna abstrata pelo fato de possuir métodos sem implementação.
Se declararmos um método em C++ como virtual e o implementarmos, fazemos com que a implementação dele por parte da subclasse torne-se opcional*/

class Base {//Caso seja um classe abstrata não é possível criar um objeto do tipo da mesma, ou seja, não pode ser instanciada. Contudo podemos criar um ponteiro de Base que recebe uma classe filha.  
public:

    Base(){
        cout << "Construtor da Base" << endl;
    }

  // Método abstrato. Está fazendo com que a classe Base seja abstrata.
  virtual int size() = 0;
  
  // Para o polimorfismo funcionar é necessário declarar 'virtual'
  virtual void metodo() {
    cout << "Metodo da classe base" << endl;
  }
   void const metodo2() {
    cout << "Metodo da classe base" << endl;
  }
  
  // Se você não sabe se uma classe vai ser derivada, devemos declarar o 
  // destrutor como virtual
  virtual ~Base() {}
  
private:
   int x;
};

class Derivada: public Base { //Modo de representar a herança
  public:

    Derivada(): Base() { //Executa o construtor da base e em seguida a linha abaixo (OBS: FAZ ISSO MESMO SE FOSSE UM CONSTRUTOR COMUM).
        cout << "Construtor dois" << endl;
    };

   int size() {
      return sizeof( *this );
    } 
      
   void metodo() {
    cout << "Metodo da classe derivada" << endl;
  }
};

void foo( Base& x ) {
  x.metodo();
}

int main(int argc, char * argv[]){
   //Base L;// Isso não pode ser feito, pois size não está implementado, fazendo com que a classe base seja abstrata.
   
   /*Meus testes*/
    Base *A;
    Derivada B;
    A = &B;
    cout << (*A).size() << endl;
    cout << B.size() << endl;
    (*A).metodo();
    (*A).size();
    /*meu*/

    /*Zimbrão*/
    Base* b;
    Derivada d;
    Base *pb = &d;
    
    //foo( *b );
    foo( d );
    pb->metodo();

    cout << "Base:    " << sizeof( b ) 
        << " &b: " << &b << endl;
    cout << "Dervida: " << sizeof( d ) 
        << " &d: " << &d << endl;

    /*Zimbrão*/
   return 0;
}