#ifndef TRIPLE_HPP
#define TRIPLE_HPP

template<class A, class B, class C> 
class triple {
public:
  A first;
  B second;
  C third;
  
  triple(A a, B b, C c) : first(a), second(b), third(c) { }  
  triple(triple const &t) : first(t.first), second(t.second), third(t.third) { }  
};

template<class A, class B, class C>
bool operator==(triple<A,B,C> const &x, triple<A,B,C> const &y) {
  return x.first == y.first && x.second == y.second && x.third == y.third;
}

template<class A, class B, class C>
bool operator!=(triple<A,B,C> const &x, triple<A,B,C> const &y) {
  return x.first != y.first || x.second != y.second || x.third != y.third;
}

template<class A, class B, class C>
bool operator<(triple<A,B,C> const &x, triple<A,B,C> const &y) {
  return x.first < y.first || 
    (!(y.first < x.first) && x.second < y.second) || 
    (!(y.first < x.first) && !(y.second < x.second) && x.third < y.third);
}

template<class A, class B, class C>
triple<A,B,C> make_triple(A a, B b, C c) {
  return triple<A,B,C>(a,b,c);
}

#endif
