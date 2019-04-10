#include<iostream>
#include<string.h>
#include <vector>

using namespace std;

template <int dim, typename T> 
class Vetor{
    private:
    vector<T> coords;
    int temp; //temp será usado para diferenciar os vetores temporários, criados durantes as operações. Para que os mesmos sejam liberados da memória posteriormente.

    public:

        class MeioDaOperacaoProdVetorial {
            private:
            Vetor *vetor;
            MeioDaOperacaoProdVetorial( Vetor* v ): vetor( v ) {}
        
            // Declaro que a classe Vetor pode enxergar campos e métodos privados
            friend class Vetor;  
        };

        Vetor(int temp = 0): temp(temp){} //Construtor.  

        Vetor& operator= (const T coord){ //Operador usado apenas na atribuição das coordenadas.
            coords.push_back(coord);
            return *this;
        }

        void operator= (Vetor<dim,T> &A){ //Operador usado apenas na atribuição de vetores.
            if(this->coords.size() == 0){
                for(int i = 0; i < dim; ++i){
                    this->coords.push_back(A.coords[i]);
                }
            }else{
                for(int i = 0; i < dim; ++i){
                    this->coords[i] = A.coords[i];
                }
            }
            libera(A);
        }

        Vetor& operator, ( const T coord ) { // Auxiliar na atribuição das coordenadas ao vetor. 
            if(this->coords.size() < dim)
                coords.push_back(coord);
             return *this;
        }

        Vetor& operator+ (Vetor<dim,T> &A){ //SOMA DE VETORES
            Vetor<dim,T> *R = new Vetor(1);
            for(int i = 0; i < dim; ++i){
                R->coords.push_back(this->coords[i] + A.coords[i]);
            }
            libera(A);
            libera(*this);
            return *R;
        }

        Vetor& operator- (Vetor<dim,T> &A){ //SUBTRAÇÃO DE VETORES
            Vetor<dim,T> *R = new Vetor(1);
            for(int i = 0; i < dim; ++i){
                R->coords.push_back(this->coords[i] - A.coords[i]);
            }
            libera(A);
            libera(*this);
            return *R;
        }

        Vetor& operator* (const double A){ //MULTIPLICAÇÃO POR UM ESCALAR
            Vetor<dim,T> *R = new Vetor(1);
            for(int i = 0; i < dim; ++i){ 
                R->coords.push_back(this->coords[i] * A);
            }
            libera(*this);
            return *R;
        }

        T operator* (Vetor<dim,T> &A){ //PRODUTO ESCALAR
            T res = 0;
            for(int i = 0; i < dim; ++i){
                res = res + (this->coords[i] * A.coords[i]);
            }
            libera(A);
            libera(*this);
            return res;
        }

        Vetor& operator/ (const double A){ //DIVISÃO POR UM ESCALAR
            Vetor<dim,T> *R = new Vetor(1);
            for(int i = 0; i < dim; ++i){ 
                R->coords.push_back(this->coords[i]/A);
            }
            libera(*this);
            return *R;
        }

        MeioDaOperacaoProdVetorial operator* (){ //PRODUTO VETORIAL
            return MeioDaOperacaoProdVetorial(this);
        }     

        Vetor& operator* (MeioDaOperacaoProdVetorial A) { //AUXILIAR PARA A OPERAÇÃO PRODUTO VETORIAL 
            Vetor<dim,T> *R = new Vetor(1);
            R->coords.push_back(this->coords[1] * A.vetor->coords[2] - this->coords[2] * A.vetor->coords[1]);
            R->coords.push_back(this->coords[2] * A.vetor->coords[0] - this->coords[0] * A.vetor->coords[2]);
            R->coords.push_back(this->coords[0] * A.vetor->coords[1] - this->coords[1] * A.vetor->coords[0]);
            libera(*(A.vetor));
            libera(*this);
            return *R;
        }   

        void imprime(ostream &o) const {//Auxiliar na impressão de vetores.
            o << "(";
            for(int i = 0; i<dim; ++i){
                if(i+1 != dim)
                    o << coords[i] << ",";
                else
                    o << coords[i] << ")";  
            }
        }

        void static libera(Vetor<dim,T> &A){ //Libera a memória dos objetos (vetores R's) criados temporariamente.
            if(A.temp == 1)
                delete &A;
        }
};

template<int dim, typename T> //IMPRIME VETORES
ostream& operator << (ostream &o, Vetor<dim, T> &A){
    A.imprime(o);
    Vetor<dim, T>::libera(A);
    return o;
}

template<int dim, typename T> 
Vetor<dim, T>& operator* (double A, Vetor<dim, T> &B) { //MULTIPLICAÇÃO POR UM ESCALAR (Caso o escalar venha antes do vetor. ex: A = 2 * B)
    Vetor<dim,T> *R = new Vetor<dim,T>(1);
    *R = B * A;
    Vetor<dim, T>::libera(B);
    return *R;
}

int main( int argc, char *argv[] ) { //TESTES
        Vetor<3, double> A, B, C, D;
        A = 2, 3, 0;
        B = 3, 2, 0;
        C = 10, 5, 0;
     
        D = A + B + C;
        cout << "D = A + B + C => " << D << endl;

        D = D - A;
        cout << "D = D - A => " << D << endl;

        cout << "C*2 = " << C*2 << endl;
        cout << "C/2.5 = " << C/2.5 << endl; 

        cout << "A + B + A * 2.0 = " << A + B + A * 2.0 << endl;
        cout << "A = " << A << endl;
        cout << "B = " << B << endl;
        cout << "C= " << C << endl;
        cout << "D = " << D << endl;
        
        cout << "A**B = " << A**B << endl;

        cout << "2.1 * A = " << 2.1 *A << endl;

        cout << A*B << endl;

    return 0;
}