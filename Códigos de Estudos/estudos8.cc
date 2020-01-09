/*
- enable_if
- Parâmetros template para templates
*/

#include <iostream>

using namespace std;

template <bool N, typename T> 
struct IfTrue {
  typedef T tipo;
};

template <typename T> 
struct IfTrue<false, T> {
};

template <int N, typename T = double> 
class Vetor {
public:
  
  template <int Proximo>
  class Meio {
  public:
    Meio( Vetor* v ): v(v) {}

    auto operator , ( typename IfTrue< Proximo<=N, T >::tipo valor ) {
      v->tab[Proximo] = valor;
      return Meio<Proximo+1>( v );
    }
    
  private:       
    Vetor *v;
  };
    
  Meio<1> operator = ( T valor ) {
    tab[0] = valor;
    return this;
  }
  
  void print() {
    cout << "[ ";
    for( auto x : tab ) 
      cout << x << " ";

    cout << "]";
  }
  
private:
  T tab[N];
};

int main() {
  Vetor<4> v;
  
  v = 1, 2, 9;
  
  v.print();

  cout << endl;
  return 0;
}