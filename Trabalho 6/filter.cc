#include<iostream>
#include<string>
#include<vector>
#include <map>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <cstdint>
#include <sstream>


using namespace std;

void print( int x ) { cout << x << " "; }

template<typename T, int n, typename F> 
auto operator| (T (&elementos)[n], F f) {
    if constexpr (is_same<void,decltype(f(elementos[0]))>::value){
        for(auto x : elementos)(0)
        f(x);
    }else if constexpr(is_same<bool,decltype(f(elementos[0]))>::value){
        vector<T> res;
        for(auto x : elementos){
            if(f(x)){
                res.push_back(x);
            }
        }
        return res;
    }
}

template<template<typename> class E, typename T, typename F> 
auto operator| (E<T> &elementos, F f) {
    if constexpr (is_same<void,decltype(f(*elementos.begin()))>::value){
        for(auto x : elementos){
            f(x);
        }
    }else if constexpr (is_same<bool,decltype(f(*elementos.begin()))>::value){
        E<T> res;
        for(auto x : elementos){
            if(f(x)){
                res.push_back(x);
            }
        }
        return res;
    }
}

vector<int>  operator| (vector<string> &elementos, decltype(&string::length) f) {
    vector<int> res;
    for(auto x : elementos){        
        res.push_back(x.length());  
    }
    return res;
}

template<template<typename,typename> class E = map, typename T, typename G, typename F> 
auto operator| (const E<T,G> &elementos, F f) {
    if constexpr (is_same<void,decltype(f(*elementos.begin()))>::value){
        for(auto x : elementos)
            f(x);
    }else if constexpr (is_same<bool,decltype(f(*elementos.begin()))>::value){
        E<T,G> res1;
        for(auto x : elementos){
            if (f(x)){
                res1[x.first] = x.second;
            }
        }
        return res1;
    }else if constexpr(is_same<string,decltype(f(*elementos.begin()))>::value){
        vector<string> res3;
        for(auto x : elementos)
            res3.push_back(f(x));
        return res3;
    }else if constexpr (is_same<pair<decltype(f(*elementos.begin()).first),decltype(f(*elementos.begin()).second)>,decltype(f(*elementos.begin()))>::value){
        E<decltype(f(*elementos.begin()).first),decltype(f(*elementos.begin()).second)> res2;
        for(auto x : elementos){
            res2[f(x).first] = f(x).second;
        }
        return res2;
    }
}

int main(int argc, char *argv[]){ //TESTES

   /* 
    int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
    vector<int> v{ 2 , 6, 8 };

    tab | []( int x ) { cout << x*x << endl; };
    tab | [ &v ]( int x ) { v.push_back( x ); };
    v | []( int x ) { cout << x*x << endl; };
    v | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << endl; };
    v | &print;
*/

/*
    vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
    auto result = v1 | []( int x ) { return x % 2 == 0; };
    for( auto x : result )
        cout << x << " ";
*/

/*
    vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
    auto result = v1 | []( int x ) { return x % 2 == 0; };
    for( auto x : result )
        cout << x << " ";
*/


/*
    map<string,string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" } };
    v | []( auto x ){ return pair{ x.first, stod( x.second ) }; } | []( auto p ) { cout << p.second + 1.1 << " "; };
*/

/*
    map<string,string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" }, { "f", "6" } };
    auto par = []( auto x ){ return stoi( x.second ) % 2 == 0; };
    auto upper_first = []( auto x ){ string st = x.first; transform(st.begin(), st.end(), st.begin(), ::toupper); return st; };
    v | par | upper_first | []( auto st ) { cout << st + "! "; };
*/

/*
    map<string,string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" }, { "F", "6" } };
    auto par = []( auto x ){ return stoi( x.second ) % 2 == 0; };
    auto first = []( pair<string,string> p ) { return p.first; };
    auto upper = []( string st ){ transform(st.begin(), st.end(), st.begin(), ::toupper); return st; };
    vector<string> result = v | par | first | upper;
    result | []( auto st ) { cout << st + "! "; };
*/
/*
    vector<string> v1 = { "janeiro", "fevereiro", "março", "abril", "maio" };
    v1 | &string::length | [] ( int x ) { cout << x << " "; };
*/

    return 0;
}

//Nome tipos retornados.

/*#include <typeinfo>
#include <cxxabi.h>*/

     /*   char * name = 0;
	int status;
	name = abi::__cxa_demangle(typeid(decltype(f(0))).name(), 0, 0, &status);
        if (name != 0) { std::cout << name << std::endl; }
        else { std::cout << typeid(decltype(f(0))).name() << std::endl; }*/