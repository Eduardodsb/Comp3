/* Estudos slide1

- Diferença entre struct e class
- Public e Private
- Formas de criar um objeto e de se referenciar a ele
- Construtor e Destrutor
- Chamar métodos sem criar objetos
*/


#include <iostream>

using namespace std; //Permite usar os métodos de std sem ter que se referenciar com dois pontos (std::cout)
// using namespace FilaInt; Porque, não funciona?


class FilaInt{ // Struct por padrão será public e class por padrão private.
    private:
        int fila[10], atual, temp;

    public:
        int a;

        FilaInt(){ //Construtor
            cout << "OIEE" << endl;
            atual = 0;     
        }

        ~FilaInt(){ // Destrutor
            cout << "FUII" << endl;     
        }

        void Incluir(int number){
            fila[atual] = number;
        }

        int Remover(){
            temp = fila[0];
            for(int j = 0; j< atual-1; j++){
                fila[j] = fila[j+1];
            }
            return temp;
        }

        void static Print(int idade){
            cout << idade << endl;
        }



};


int main(int argc, char * argv[]){

    { // Neste caso o construtor é chamado automaticamente e o destrutor tb ao fim do bloco.
    FilaInt objeto1;
    objeto1.a = 2;
    cout << objeto1.a << endl;
    }

    { // Neste caso o construtor e o destrutor não são chamados automaticamente. O objeto deve ser inicializado com new e detruido com delete ao final, para liberar a memória e chamar o destrutor.
    FilaInt *objeto2 = new FilaInt();
    (*objeto2).a = 15;
    cout << (*objeto2).a << endl;
    delete objeto2;
    //delete[] objeto2 /*Para o caso de um arrey*/
    }

    FilaInt::Print(22); //CONSEGUI CHAMAR DESSE MODO APENAS UM MÉTODO ESTÁTICO. ???

    return 0;

}