#include <iostream>
#include <type_traits>
#include <functional>
#include <vector>

using namespace std;

template <typename Functor>
class Lambda {
public:
  Lambda( Functor f ): f(f) {}

  template <typename V>
  invoke_result_t< Functor, V > operator()( V v ) const {
    return f( v );
  }

  auto operator[] (int a){
      return [a]( auto v ) { return v[a]; };
  }

private:
  Functor f;
};

auto aux = []( auto v ){ return v; };

Lambda x{aux};

template <typename A, typename B>
auto operator + ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) + b(v); } };
}


template <typename A, typename B>
auto operator + ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) + b; } };
}

template <typename A, typename B>
auto operator + ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a + b(v); } };
}

template <typename A, typename B>
auto operator + ( vector<A> a, B b ) {
    a.push_back(b); 
    return a;
}

template <typename A, typename B>
auto operator - ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) - b(v); } };
}

template <typename A, typename B>
auto operator - ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) - b; } };
}

template <typename A, typename B>
auto operator - ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a - b(v); } };
}

template <typename A, typename B>
auto operator * ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) * b(v); } };
}

template <typename A, typename B>
auto operator * ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) * b; } };
}

template <typename A, typename B>
auto operator * ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a * b(v); } };
}

template <typename A, typename B>
auto operator / ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) / b(v); } };
}

template <typename A, typename B>
auto operator / ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) / b; } };
}

template <typename A, typename B>
auto operator / ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a / b(v); } };
}

template <typename A, typename B>
auto operator % ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) % b(v); } };
}

template <typename A, typename B>
auto operator % ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) % b; } };
}

template <typename A, typename B>
auto operator % ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a % b(v); } };
}

template <typename A, typename B>
auto operator % ( A a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) % b; } };
}

template <typename A, typename B>
auto operator == ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) == b(v); } };
}

template <typename A, typename B>
auto operator == ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) == b; } };
}

template <typename A, typename B>
auto operator == ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a == b(v); } };
}

template <typename A, typename B>
auto operator == ( A a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) == b; } };
}

template <typename A, typename B>
auto operator != ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) != b(v); } };
}

template <typename A, typename B>
auto operator != ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) != b; } };
}

template <typename A, typename B>
auto operator != ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a != b(v); } };
}

template <typename A, typename B>
auto operator != ( A a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) != b; } };
}

/*
template <typename A, typename B>
auto operator | ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { for(auto x : v){ b(a(x));} } };
}*/

template <typename A, typename B>
auto operator | ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { a(v) | b; } };
}

template<typename T, typename F>
auto operator | ( const T& iterable, F function ) {
    if constexpr ( is_same_v< bool, invoke_result_t< F, decltype( *begin(iterable) ) > > ) {
        vector< decay_t< decltype( *begin(iterable) ) > > result;

        for( auto element : iterable ) 
            if( invoke( function, element ) )
                result.push_back( element );
        
        return result;
    }else if constexpr ( (is_same_v< void, invoke_result_t< F, decltype( *begin(iterable) ) > > ||
                        is_reference_v< invoke_result_t< F, decltype( *begin(iterable) ) > >)) {
        for( auto element : iterable ) 
            invoke( function, element );
    }else {
        std::vector< decay_t< invoke_result_t< F, decltype( *begin(iterable) ) > > > result;

        for( auto element : iterable ) 
            result.push_back( invoke( function, element ) );
        
        return result;
    }
}

template <typename A>
auto operator << ( ostream& o, Lambda<A> opr ) { 
 return Lambda{ [&o,opr]( auto v ) -> ostream& { return o << opr(v); } };
}

template <typename A, typename B>
auto operator << ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) ->ostream& { return a(v) << b(v); } };
}

template <typename A, typename B>
auto operator << ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) ->ostream& { return a(v) << b; } };
}
template <typename A, typename B>
auto operator << ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) ->ostream& { return a << b(v); } };
}
/*
template <typename A, typename B>
auto operator [] (Lambda<A> a, Lambda<B> b ){
    return;
}*/

int main() {
//testes

/*vector<int> v = { 1, 2, 3, 4 };
  auto f = cout << x*x + 1 << '\n';
  v | f;*/
/*
    vector< vector<int> > m{ { 1, 2, 3 },{ 0, 3, 7 },{ 1, 3 } };
    m | [](auto v) { return v[0] != 0; } | [](auto v) { (v + 7) | cout << x << ' '; };
*/
/*
    vector< vector<int> > m{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
    m | []( auto v ) { return v[0] != 0; } | ( x | cout << x << ' ' );
*/

/*
vector< vector<int> > m{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
m | x[0] != 0 | ( x | cout << x << ' ' );
*/


vector< vector<int> > m{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
m | x[0] != 0 | (( x * 7 ) | cout << x << ' ' );
  return 0;
}