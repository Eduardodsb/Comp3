#include<iostream>
#include<string>
#include<vector>

using namespace std;

void print( int x ) { cout << x << " "; }



template<template<typename> class E, typename T, typename F> 
void operator| (const E<T> &elementos, F f) {
    for(auto x : elementos)
        f(x);
}

template<typename T, int n, typename F> 
void operator| (T (&elementos)[n], F f) {
    for(auto x : elementos)
        f(x);
}


int main(int argc, char *argv[]){
    
    int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
    vector<int> v{ 2 , 6, 8 };
  
    //tab | []( int x ) { cout << x*x << endl; };
     tab | [ &v ]( int x ) { v.push_back( x ); };
   // v | []( int x ) { cout << x*x << endl; };
    v | &print;


    return 0;
}