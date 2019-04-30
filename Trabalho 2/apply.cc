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
