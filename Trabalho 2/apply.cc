#include<iostream>
#include<string.h>
#include<vector>
#include<list>
#include<initializer_list>

using namespace std;

int teste(int n){
    return n*n;
}
template<template<typename> class E, typename T, class F>
auto apply(const E<T> &elementos, F f){
    E<decltype(f(*elementos.begin()))> res;
    for(auto x : elementos){
        res.push_back(f(x));
    }

    return res;
}

template<typename T, typename F>
auto apply(const initializer_list<T> &elementos, F f){
    vector<decltype(f(*elementos.begin()))> res;
    for(auto x : elementos){
        res.push_back(f(x));
    }

    return res;
}


/*
template<template<typename, typename> class E, template<typename> class A, typename B, typename T, typename F>
auto apply(const E<T, A<B>> &elementos, F f){
    int i = 0;
    E<decltype(f(*elementos.begin()), A<decltype(f(*elementos.begin()))> > res;
    for(auto x : elementos){
        res.push_back(f(x));
    }

    return res;
}
*/

/*
template<template<typename> class E, typename T, class F>
auto apply(const E<T> &elementos, F f){
    int i = 0;
    E<decltype(f(*elementos.begin()))> res;
    for(auto x : elementos){
        res.push_back(f(x));
    }

    return res;
}*/



/*
template<template<typename> class E, typename T, typename F>
auto apply(const E<T> &elementos, F f){
    int i = 0;
    E<decltype(f(*elementos.begin()))> res;
    char * name = abi::__cxa_demangle(typeid(F).name(), 0, 0, 0);
    if(strcmp(name,"main::{lambda(auto:1)#1") == 0){
        for(auto x : elementos){
            res.push_back((f)(x));
        }
    }else{
        for(auto x : elementos){
            res.push_back((*f)(x));
        }
    }
    return res;
}
*/



/*
template<typename T, int n, typename F>
void apply(T (&elementos)[n], F f){
    for(auto x : elementos){
        (*f)(x);
    }
}*/

/*
template<template<typename> class E, typename T, typename F>
auto apply(const E<T> &elementos, F f){
    int i = 0;
    E<decltype(f(*elementos.begin()))> res;
   // typename E<T,A>::iterator it;
   // it = (*res).begin();
    for(auto x : elementos){
        res.push_back((*f)(x));
      // *next(it,i++) = (*f)(x);
    }
    return res;
}
*/
int main(int argc, char *argv[]){
    vector<int> A = {5, 4 ,3 ,9 ,7};
    int B[5] = {1, 2, 3, 4, 5};
    list<int> C = {1,2,3,4,5,6};
    initializer_list<int> D = {7,8,9};

    vector<int> v{ 1, 2, 3, 4, 5 };

    initializer_list<int>::iterator it;
    it = D.begin();
   // inserter(it,1);

   //  cout << D << endl;

    vector<int, allocator<int>> Z;

    for(auto x : apply({ 1, 2, 3, 4, 5 }, teste)){
        cout << x << endl;
    }

    for(auto x : apply(C, teste)){
        cout << x << endl;
    }

  for(auto x : apply(A, []( auto n )->double { return n*n + 0.1; })){
        cout << x << endl;
    }
    return 0;
}
