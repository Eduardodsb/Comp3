#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/timeb.h>

using namespace std;
 
double** alocarMatriz(int L, int C){ /*Recebe o tamanho de linhas e colunas da matriz*/
  double **m = (double**)malloc(L * sizeof(double*)); /*Aloca um vetor de ponteiros*/
  if(!m){ /*Verifico se a memória foi alocada para as linhas*/
    printf("Erro: Nao foi possível alocar memória.\n");
    exit(1);
  }
  for (int i = 0; i < L; i++){
       m[i] = (double*) malloc(C * sizeof(double)); /*Aloca um vetor de inteiros para cada posição do vetor de ponteiros.*/
       if(!m[i]){ /*Verifico se a memória foi alocada para as colunas*/
         printf("Erro: Nao foi possível alocar memória.\n");
         exit(1);
       }
       for (int j = 0; j < C; j++){
            m[i][j] = 0; /*inicializa com 0.*/
       }
  }
return m; /*Retorna o ponteiro para a matriz alocada*/
}

double** multMatriz(double **m1, double **m2, int L1, int LC, int C2){
 double** res =  alocarMatriz(L1,C2);
    for( int i = 0; i < L1; i++ ){
      for( int j = 0; j < C2; j++ ){
        res[i][j] = 0;
        for( int k = 0; k < LC; k++ ){
	        res[i][j] += m1[i][k] * m2[k][j];
        }
      }
    }
  return res;
}

template <int L3, int C3>
class Meio{
public:
double **m3;
  Meio(double **m3): m3(m3){}
};

template <int L1, int C1, int L2, int C2>
class Otimizador{
public:
int Li1, Co1, Li2, Co2, Li3, Co3;
double **m1;
double **m2;
double **res;
int aux = 0;

Otimizador( double **mm1, double **mm2): Li1(L1), Co1(C1), Li2(L2), Co2(C2){
    m1 = mm1;
    m2 = mm2;
    res = alocarMatriz(L1,C2);
}

  template<int L3 = C2, int C3>
  Otimizador<L1,C2,L3,C3> operator() (Meio<L3,C3> m3) {
    Li3 = L3;
    Co3 = C3;
    if ((Li1*Co1*Co2)+(Li1*Co2*(Co1-1)) > (Li2*Co2*Co3)+(Li2*Co3*(Co2-1))){
      Otimizador<L1,C2,L3,C3> o2(res,m3.m3);
      o2.aux = 1;
      o2.res = multMatriz(multMatriz(m1,m2,L1,C1,C2),m3.m3,L1,C2,C3); 
      return o2;

    }else{
      Otimizador<L1,C2,L3,C3> o2(m1,res);
      o2.aux = 1;
      o2.res = multMatriz(m1,multMatriz(m2,m3.m3,L2,C2,C3),L1,C1,C3); 
      return o2;
    }
  }
private:
};

template <int L, int C>
class Matriz {
public:
double **m;
  Matriz(): m(alocarMatriz(L,C)){}

  template<int L2 = C, int C2 = L>
  Matriz<L,C> operator+ ( Matriz<L2,C2> m2 ) const {
    Matriz<L,C2> res;
    for( int i = 0; i < L; i++ )
      for( int j = 0; j < C2; j++ )
        res.m[i][j] = m[i][j] + m2.m[i][j];
    
    return res;
    }

  template<int L2 = C, int C2 = L,int T1, int T2, int T3, int T4>
  Matriz<L,C> operator+ ( Otimizador<T1, T2, T3, T4> o ) const {
    Matriz<L,C2> res;
    double **m2;
    if(o.aux == 0){
      m2 = multMatriz(o.m1,o.m2,o.Li1,o.Co1,o.Co2);
    }else{
      m2 = o.res;
    }
    for( int i = 0; i < L; i++ )
      for( int j = 0; j < C2; j++ )
        res.m[i][j] = m[i][j] + m2[i][j];
    
    return res;
    }

  template<int T1, int T2, int T3, int T4>
  Matriz(const Otimizador<T1, T2, T3, T4> &o) {
    if(o.aux == 0){
      m = multMatriz(o.m1,o.m2,o.Li1,o.Co1,o.Co2);
    }else{
      m = o.res;
    }
  }
   
private:
};

template<int T1, int T2, int T3, int T4, int T5, int T6, int T7, int T8>
Matriz<T1,T4> operator+ (Otimizador<T1, T2, T3, T4> o1, Otimizador<T5, T6, T7, T8> o2 ) {
  Matriz<T1,T4> res;
  for( int i = 0; i < T1; i++ )
    for( int j = 0; j < T4; j++ )
      res.m[i][j] = o1.res[i][j] + o2.res[i][j];
  return res;
}

template <int LC, int C, int T1, int T2,int T3, int T4>
auto operator* (Otimizador<T1,T2,T3,T4> o, const Matriz<LC,C> &m3 ) {
  return o(Meio<LC,C>(m3.m));
}

template <int L, int LC, int C>
Otimizador<L, LC, LC, C> operator* ( const Matriz<L,LC> &m1,const Matriz<LC,C> &m2 ) {
  return Otimizador<L, LC, LC, C> (m1.m,m2.m);
}

template <typename F>
class Apply {
public:
  Apply( F f ): f(f) {}
  
  template <int L, int C>
  Matriz<L,C> operator()( const Matriz<L,C>& m ) const {
      Matriz<L,C> res;
      for( int i = 0; i < L; i++ ){
        for( int j = 0; j < C; j++ ){
           res.m[i][j] = f(m.m[i][j]);
        }
      }
      return res;
  }
  
private:
  F f;
};
 
template <int L, int C>
int tamanho(Matriz<L,C> m){
  return L * C;
}

template <int T1, int T2, int T3, int T4>
int tamanho(Otimizador<T1,T2,T3,T4> m){
  return T1 * T4;
}


template <typename F>
Apply<F> apply( F f ) {
  return Apply<F>(f);
}

int main() {
//Testes

 /* int opcao = 0;
  
  inicializa( a );
  inicializa( b );
  inicializa( c );

  cin >> opcao;
  
  if( opcao == 0 ) {
    cout << "multiplicacao a * b * c" << endl;
    mult( t1, a, b );
    mult( res, t1, c );
  }
  else {
    cout << "multiplicacao a * (b * c)" << endl;
    mult( t2, b, c );
    mult( res, a, t2 );
  }*/

//Teste1
// Eu criei uma função apply com minúsculas.
  // template <typename F> Apply<F> apply( F f ) { return Apply<F>(f); }
  // Sua classe deve ser Apply, com maiúscula.
/*  int i = 0;
  auto f0 = apply( [&i]( double x ) { return i++; } );
  auto print = apply( []( double x ) { cout << x << " "; return x; } );
  auto f2 = apply( []( double x ) { return x*x; } );
  Matriz<4,3> m;

  m = f0( m );
  print( m );
  cout << endl;
  m = f2( m );
  print( m );
  cout << endl;

  cout << tamanho( m ) << endl;
*/

//Teste2
/*     
Matriz<100,1> a;
  Matriz<1,100> b;

  auto x = a * b;
  auto y = b * a;

  cout << tamanho( x ) << endl;
  cout << tamanho( y ) << endl;
*/

//Teste3
/* 
   Matriz<17,93> a, b;

  auto x = a + b;
  auto y = a + b + a + b;

  cout << tamanho( x ) << endl;
  cout << tamanho( y ) << endl;  
  return 0;
*/

//Teste4
/*     
Matriz<1000,1> a;
  Matriz<1,1000> b;
  Matriz<1000,1000> c;
  int tempo = 0, lapso1, lapso2;
 
  tempo = clock();
 
  Matriz<1000,1000> x1 = a * b;
  Matriz<1000,1000> x2 = x1 * c;

  cout << tamanho(x1) << endl;
  cout << tamanho(x2) << endl;

  lapso1 = clock() - tempo;

  tempo = clock();
  
  Matriz<1000,1000> y = a * b * c;

  lapso2 = clock() - tempo;
  cout << tamanho(y) << endl;

  if( lapso1/lapso2 > 10 ){
    cout << "Otimizou" << endl;
  }else{
    cout << "Não otimizou" << endl;
  }*/

  //Teste5
  /*  
  Matriz<997,1> a;
  Matriz<1,997> b;
  Matriz<997,997> c;
  int tempo = 0, lapso1, lapso2;

  tempo = clock();

  Matriz<997,997> x1 = a * b;
  Matriz<997,997> x2 = x1 * c;
  Matriz<997,997> t1 = a * (b + b);
  Matriz<997,997> x3 = x2 + t1 * c;

  cout << tamanho(x1) << endl;
  cout << tamanho(x2) << endl;
  cout << tamanho(t1) << endl;
  cout << tamanho(x3) << endl;

  lapso1 = clock() - tempo;

  tempo = clock();

  Matriz<997,997> y = a * b * c + a * (b + b) * c;

  lapso2 = clock() - tempo;
  cout << tamanho(y) << endl;

  if( lapso1/lapso2 > 10 )
    cout << "Otimizou" << endl;
  else
    cout << "Não otimizou" << endl;*/
return 0;
}

