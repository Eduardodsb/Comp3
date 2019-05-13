#include<iostream>
#include<math.h>
#include <type_traits>
#include <cstdint>
#include <sstream>

using namespace std;

class X {
    public:
        double e( double v ) {
         return v;
        }
        double dx( double v ) {
            return 1;
        }
        string str() const{
            return "x";
        }
        string dx_str() const{
            return "1";
        }
};

class Cte {
public:
    Cte( double c ): c(c) {}

    double e( double v ) {
    return c;
    }

    double dx( double v ) {
    return 0;
    }
    string str() const{
        std::stringstream res;
        res << c;
        return res.str();
    }
    string dx_str() const{
        return "0";
    }
  
private:
  double c;
};

template <typename F1>
class Sin {
public:
    Sin( F1 f1): f1(f1){}
    
    double e( double v ) {
        return sin(f1.e(v));
    }

    double dx( double v ) {
        return cos(f1.e(v))*f1.dx(v);
    }
    string str() const{
        return "sin(" + f1.str() + ")";
    }
    string dx_str() const{
        return "cos(" +f1.str() + ")*(" + f1.dx_str() + ")";
    }
  
private:
  F1 f1;
};

template <typename F1>
Sin<F1> sin(F1 f1){
    return Sin<F1>(f1);  
}

template <typename F1>
class Cos {
public:
    Cos( F1 f1): f1(f1){}
    
    double e( double v ) {
        return cos(f1.e(v));
    }

    double dx( double v ) {
        return -sin(f1.e(v))*f1.dx(v);
    }
    string str() const{
        return "cos(" + f1.str() + ")";
    }
    string dx_str() const{
        return "-sin(" + f1.str() +  ")*(" + f1.dx_str() + ")";
    }
  
private:
  F1 f1;
};

template <typename F1>
Cos<F1> cos(F1 f1){
    return Cos<F1>(f1);  
}

template <typename F1>
class Exp {
public:
    Exp( F1 f1): f1(f1){}
    
    double e( double v ) {
        return exp(f1.e(v));
    }

    double dx( double v ) {
        return exp(f1.e(v))*f1.dx(v);
    }
    string str() const{
        return "exp(" + f1.str() + ")";
    }
    string dx_str() const{
        return "exp(" + f1.str() + ")*(" + f1.dx_str() + ")";
    }
  
private:
  F1 f1;
};

template <typename F1>
Exp<F1> exp(F1 f1){
    return Exp<F1>(f1);  
}

template <typename F1>
class Log {
public:
    Log( F1 f1): f1(f1){}
    
    double e( double v ) {
        return log(f1.e(v));
    }

    double dx( double v ) {
        return (1/f1.e(v))*f1.dx(v);
    }
    string str() const{
        return "log(" + f1.str() + ")";
    }
    string dx_str() const{
        return "(1/(" + f1.str() + "))*(" + f1.dx_str() + ")";
    }
  
private:
  F1 f1;
};

template <typename F1>
Log<F1> log(F1 f1){
    return Log<F1>(f1);  
}

template <typename F1, typename F2>
class Soma {
public:
    Soma( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    double e( double v ) {
        return f1.e(v) + f2.e( v );
    }

    double dx( double v ) {
        return  f1.dx(v) + f2.dx(v);
    }
    string str() const{
        return "(" + f1.str() + ")+(" + f2.str() + ")";
    }
    string dx_str() const{
        return "(" + f1.dx_str() + ")+(" + f2.dx_str() + ")";
    }
  
private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2> 
Soma<F1,F2> operator + ( F1 f1, F2 f2 ) {
   return Soma<F1,F2>( f1, f2 );
}

template <typename F2> 
Soma<Cte,F2> operator + ( double n, F2 f2 ) {
   return Soma<Cte,F2>( n, f2 );
}

template <typename F1> 
Soma<F1,Cte> operator + ( F1 f1, double n ) {
   return Soma<F1,Cte>( f1, n );
}

template <typename F2> 
Soma<Cte,F2> operator + ( int n, F2 f2 ) {
   return Soma<Cte,F2>( n, f2 );
}

template <typename F1> 
Soma<F1,Cte> operator + ( F1 f1, int n ) {
   return Soma<F1,Cte>( f1, n );
}

template <typename F1, typename F2>
class Subtracao {
public:
    Subtracao( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    double e( double v ) {
        return f1.e(v) - f2.e( v );
    }

    double dx( double v ) {
        return  f1.dx(v) - f2.dx(v);
    }
    string str() const{
        return "(" + f1.str() + ")-(" + f2.str() + ")";
    }
    string dx_str() const{
        return "(" + f1.dx_str() + ")-(" + f2.dx_str() + ")";
    }
  
private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2> 
Subtracao<F1,F2> operator - ( F1 f1, F2 f2 ) {
   return Subtracao<F1,F2>( f1, f2 );
}

template <typename F2> 
Subtracao<Cte,F2> operator - ( double n, F2 f2 ) {
   return Subtracao<Cte,F2>( n, f2 );
}

template <typename F1> 
Subtracao<F1,Cte> operator - ( F1 f1, double n ) {
   return Subtracao<F1,Cte>( f1, n );
}

template <typename F2> 
Subtracao<Cte,F2> operator - ( int n, F2 f2 ) {
   return Subtracao<Cte,F2>( n, f2 );
}

template <typename F1> 
Subtracao<F1,Cte> operator - ( F1 f1, int n ) {
   return Subtracao<F1,Cte>( f1, n );
}

template <typename F1, typename F2>
class Multiplica {
public:
    Multiplica( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    double e( double v ) {
        return f1.e(v) * f2.e(v);
    }


    double dx( double v ) {
        return f1.e(v)*f2.dx(v) + f1.dx(v)*f2.e(v);
    }
    string str() const{
        return "(" + f1.str() + ")*(" + f2.str() + ")";
    }
    string dx_str() const{
        return "(" + f1.dx_str() + ")*(" + f2.str() + ")+(" + f1.str() + ")*(" + f2.dx_str() + ")";
    }
  
private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2> 
Multiplica<F1,F2> operator * ( F1 f1, F2 f2 ) {
   return Multiplica<F1,F2>( f1, f2 );
}

template <typename F2> 
Multiplica<Cte,F2> operator * ( double n, F2 f2 ) {
   return Multiplica<Cte,F2>( n, f2 );
}

template <typename F1> 
Multiplica<F1,Cte> operator * ( F1 f1, double n ) {
   return Multiplica<F1,Cte>( f1, n );
}

template <typename F2> 
Multiplica<Cte,F2> operator * ( int n, F2 f2 ) {
   return Multiplica<Cte,F2>( n, f2 );
}

template <typename F1> 
Multiplica<F1,Cte> operator * ( F1 f1, int n ) {
   return Multiplica<F1,Cte>( f1, n );
}

template <typename F1, typename F2>
class Divide {
public:
    Divide( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    double e( double v ) {
        return f1.e(v) / f2.e( v );
    }

    double dx( double v ) {
        return (f1.dx(v)*f2.e(v) - f1.e(v)*f2.dx(v))/(f2.e(v)*f2.e(v));
    }
    string str() const{
        return "(" + f1.str() +")/(" + f2.str() + ")";
    }
    string dx_str() const{
        return "((" + f1.dx_str() + ")*(" + f2.str() + ")-(" + f1.str() + ")*(" + f2.dx_str() + "))/(" + f2.str() +")^2";
    }
  
private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2> 
Divide<F1,F2> operator / ( F1 f1, F2 f2 ) {
   return Divide<F1,F2>( f1, f2 );
}

template <typename F2> 
Divide<Cte,F2> operator / ( double n, F2 f2 ) {
   return Divide<Cte,F2>( n, f2 );
}

template <typename F1> 
Divide<F1,Cte> operator / ( F1 f1, double n ) {
   return Divide<F1,Cte>( f1, n );
}

template <typename F2> 
Divide<Cte,F2> operator / ( int n, F2 f2 ) {
   return Divide<Cte,F2>( n, f2 );
}

template <typename F1> 
Divide<F1,Cte> operator / ( F1 f1, int n ) {
   return Divide<F1,Cte>( f1, n );
}

template <typename F1, typename F2>
class Potencia {
public:
    Potencia( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    double e( double v ) {
        auto res = f1.e(v);
        for(int i=0; i<(f2.e(v)-1); i++){
            res = f1.e(v) * res;
        }
        return res;
    }

    double dx( double v ) {
        auto res = f1.e(v);
        for(int i=0; i<(f2.e(v)-2); i++){
            res = f1.e(v)*res;
        }
        return f2.e(v)*res*f1.dx(v);
    }
    string str() const{
        return "(" + f1.str() + ")^" + f2.str();
    }
    string dx_str() const{
        std::stringstream novo_exp;
        novo_exp << newExp;
        return "(" + f2.str() + "*(" + f1.dx_str() + ")*(" + f1.str() + ")^" + novo_exp.str() +")";
    }
  
private:
  F1 f1;
  F2 f2;
  int newExp = f2.e(0) - 1;
};


template <typename F1, typename F2> 
Potencia<F1,Cte> operator ->* (F1 f1, F2 n) {
    static_assert(!is_same<double,F2>::value, "Operador de potenciação definido apenas para inteiros");
    return Potencia<F1,Cte>(f1,n);
}


X x;

int main(int argc, char *argv[]){

    X x;
    //Cte c = Cte( 3 );
    double v = 0.5;
    //x->*2;
   // auto f = sin( x * x * cos( 3.14 * x + 1.0 ) );
    auto f = x->*3;
    cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
    cout << "f=" << f.str() << ", f'=" << f.dx_str() << endl;


    return 0;

}