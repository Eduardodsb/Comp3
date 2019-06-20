#include<iostream>
#include<math.h>
#include <type_traits>
#include <cstdint>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int acha_fim(string f, int pos){
    int i = 1;
    while( i != 0){
        if(f[pos] == '('){
            i++;
        }
        if(f[pos] == ')'){
            i--;
        }
        pos++;
    }
    return pos;
}

bool verifica_termos(string f){ 
    int i = 0;
    while(i < (int)f.length()){
        if((f[i] == '-')|| (f[i] == '+')){
            return true;
        }
        if(f[i] == '('){
            i = acha_fim(f,i+1);
        }else{
        i++;
        }
    }
    return false;
}

bool verifica_termos_potencia(string f){
    int i = 0;
    while(i < (int)f.length()){
        if(f[i] == '-' || f[i] == '+' || f[i] == '*' || f[i] == '/' || f[i] == '^'){
            return true;
        }
        if(f[i] == '('){
            i = acha_fim(f,i+1);
        }else{
        i++;
        }
    }
    return false;
}

string compoe_str(string op, string f1, string f2 ){
    string res = "";
    if(op == "+"){
        int i = 0;
        if(f1.compare("0") != 0){
            res = res + f1;
            i++;
        }
        if(f2.compare("0") != 0 && i != 0){
            res = res + "+" + f2;
        }else if(f2.compare("0") != 0 && i == 0){
            res = res + f2;
        }
    }
    if(op == "-"){
        if(f1.compare("0") != 0){
            res = res + f1;
        }
        if(f2.compare("0") != 0 && f2.compare("") !=0 && !verifica_termos(f2) ){
            res = res + "-" + f2;
        }else if(f2.compare("0") != 0 && verifica_termos(f2) ){
            res = res + "-(" + f2 + ")";
        }
    }
    if(op == "*"){
        if(f1.compare("1") != 0 && f2.compare("0") != 0 && !verifica_termos(f1) ){
            res = res + f1;
        }else if(f1.compare("1") != 0 && f2.compare("0") != 0 && f2.compare("1") != 0 && verifica_termos(f1)){
            res = res + "(" + f1 + ")";
        }else if(f1.compare("1") != 0 && f2.compare("0") != 0 && f2.compare("1") == 0){
            res = res + f1;
        }
        if(f2.compare("1") != 0 && f2.compare("0") != 0 && f1.compare("0") != 0 && f1.compare("1") != 0 && !verifica_termos(f2)){
            res = res + "*" + f2;
        }else if (f2.compare("1") != 0 && f2.compare("0") != 0 && f1.compare("0") != 0 && f1.compare("1") != 0 && verifica_termos(f2)){
            res = res + "*(" + f2 + ")";
        }else if(f2.compare("1") != 0 && f2.compare("0") != 0 && f1.compare("0") != 0 && f1.compare("1") == 0){
            res = res + f2;
        }
    }
    if(op == "/"){
        if(f1.compare("0") != 0 && f2.compare("0") != 0 && !verifica_termos(f1)){
            res = res + f1;
        }else if(f1.compare("0") != 0 && f2.compare("0") != 0 && verifica_termos(f1) ){
            res = res + "(" + f1 + ")";
        }
        if(f1.compare("0") != 0 && !verifica_termos(f2)){
            res = res + "/" + f2;
        }else if (f1.compare("0") != 0 && verifica_termos(f2)){
           res = res + "/(" + f2 + ")";
        }
    }
    if(op == "^"){
        if(f2.compare("0") == 0){
            res = res + "1";
        }else if(f2.compare("1") == 0){
            res = res + f1;
        }else if(f1.compare("0") != 0 && !verifica_termos_potencia(f1)){
            res = res + f1 + "^" + f2;
        }else if(f1.compare("0") != 0 && verifica_termos_potencia(f1)){
            res = res + "(" + f1 + ")^" + f2;
        }
    }
    return res;
}


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
        return compoe_str("*","cos(" +f1.str() + ")",f1.dx_str());
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
        return compoe_str("*","-sin(" +f1.str() + ")",f1.dx_str());
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
        return compoe_str("*","exp(" + f1.str() + ")",f1.dx_str());
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
        return compoe_str("*",compoe_str("/","1",f1.str()),f1.dx_str());
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
        return compoe_str("+",f1.str(),f2.str());
    }
    string dx_str() const{
        return compoe_str("+",f1.dx_str(),f2.dx_str());
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
        return compoe_str("-",f1.str(),f2.str());
    }
    string dx_str() const{
        return compoe_str("-",f1.dx_str(),f2.dx_str());
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
        return compoe_str("*", f1.str(), f2.str());
    }
    string dx_str() const{
        return compoe_str("+", compoe_str("*", f1.dx_str(), f2.str()) , compoe_str("*", f1.str(), f2.dx_str()) );
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
        return compoe_str("/", f1.str(), f2.str());
    }
    string dx_str() const{
        return compoe_str("/",compoe_str("-", compoe_str("*", f1.dx_str(), f2.str()) , compoe_str("*", f1.str(), f2.dx_str())),compoe_str("^",f2.str(),"2") ) ;
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
        return compoe_str("^",f1.str(),f2.str());
    }
    string dx_str() const{
        std::stringstream novo_exp;
        novo_exp << newExp;
        return compoe_str("*",f2.str(),compoe_str("*",f1.dx_str(),compoe_str("^",f1.str(),novo_exp.str())));
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
    double v = 9;
    //x->*2;
   // auto f = sin( x * x * cos( 3.14 * x + 1.0 ) );
    auto f = log( x->* 4 + 8.0 ) * sin( cos( x / 3.14 ) );
    cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
    cout << "f=" << f.str() << ", f'=" << f.dx_str() << endl;

//teste 
/*
f(x) = 1.0 / (sin(x)->*2 + cos(x)->*2)->*4
*/

//teste 
/*
auto f = exp( x * log( x - 8.0 ) + 1.0 ) ;
v = 9;
*/


//teste
/*
input : f(x) = exp( (x + 1.0)*(x - 1.0) )->*2 
f(x) = exp((x+1)*(x-1))^2, f'(x) = 2*exp((x+1)*(x-1))*((x-1)+(x+1))*exp((x+1)*(x-1))
*/

//teste
/*
Test 11: f(x) = log( x->* 4 + 8.0 ) * sin( cos( x / 3.14 ) ) 
f(x) = log(x^4+8)*sin(cos(x/3.14)), f'(x) = 1/(x^4+8)*4*x^3*sin(cos(x/3.14))+log(x^4+8)*cos(cos(x/3.14))*-sin(x/3.14)*3.14/3.14^2
*/

    return 0;

}