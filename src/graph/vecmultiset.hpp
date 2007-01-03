#ifndef VECSET_H
#define VECSET_H

#include <vector>
#include <algorithm>
#include <functional>

template<class T, class K>
class vecmultiset;

template<class T, class K, class S>
bool set_union(vecmultiset<T,K> &to, S const &from) {
  if(static_cast<void const *>(&to) != static_cast<void const *>(&from)) {
    vecmultiset<T,K> tmp;
    tmp._data.reserve(std::max(to.size(),from.size()));
    std::set_union(to.begin(),to.end(),from.begin(),from.end(),std::back_inserter(tmp._data));
    if(tmp.size() > to.size()) {
      to.swap(tmp); // faster than assignment, I think!
      return true;
    }
  }
  
  return false;
}

template<class T, class K>
bool is_subset(vecmultiset<T,K> const &a, vecmultiset<T,K> const &b) {
  // is "b" subset of "a".
  if(&a == &b) { 
    return true; 
  } else if(b.size() > a.size()) { return false; }
  else if(b.size() == a.size()) {
    return a == b;
  } else {    
    for(typename vecmultiset<T,K>::const_iterator i(b.begin());
	i!=b.end();++i) {
      if(a.find(*i) == a.end()) { return false; }
    }
    return true;
  }
}

template<class T, class K, class S, class ITER>
bool set_union_diff(vecmultiset<T,K> &to, S const &from, ITER d) {
  if(static_cast<void const *>(&to) != static_cast<void const *>(&from)) {
    std::vector<T> tmp;
    tmp.reserve(std::max(to.size(),from.size()));
    unsigned int os(to.size());

    typename S::iterator t(to.begin());
    typename S::iterator tend(to.end());
    typename S::const_iterator f(from.begin());
    typename S::const_iterator fend(from.end());
    
    while(t != tend && f != fend) {
      if(*f < *t) {
	tmp.push_back(*f);
	*d = *f;
	++f;++d;
      } else {
	if(!(*t < *f)) { ++f; }
	tmp.push_back(*t);
	++t;
      }
    }

    while(t != tend) {
      // hinted set insertion is better
      // than range set insertion i think ...
      tmp.push_back(*t);
      ++t;
    }

    while(f != fend) {
      // hinted set insertion is better
      // than range set insertion i think ...
      tmp.push_back(*f);
      *d = *f;
      ++f;++d;
    }

    if(tmp.size() > to.size()) {
      to._data.swap(tmp); // faster than assignment, I think!
      return true;
    }
  }  
  return false;
}

template<class T, class KeyCompare = std::less<T> >
class vecmultiset {
 public:
  typedef T value_type;
  typedef KeyCompare key_compare;
  typedef KeyCompare value_compare;
  typedef typename std::vector<T>::pointer pointer;
  typedef typename std::vector<T>::reference reference;
  typedef typename std::vector<T>::const_reference const_reference;
  typedef typename std::vector<T>::size_type size_type;
  typedef typename std::vector<T>::difference_type difference_type;
  typedef typename std::vector<T>::iterator iterator;
  typedef typename std::vector<T>::const_iterator const_iterator;
  typedef typename std::vector<T>::reverse_iterator reverse_iterator;
  typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;

  template<class Y, class L, class S> friend bool set_union(vecmultiset<Y,L> &, S const &);
  template<class Y, class L, class S, class ITER> friend bool set_union_diff(vecmultiset<Y,L> &, S const &, ITER);
  template<class Y, class L, class S> friend bool set_intersection(vecmultiset<Y,L> &, S const &);
  template<class Y, class L, class S> friend bool set_difference(vecmultiset<Y,L> &, S const &);
 protected:
  KeyCompare _comp;
  std::vector<T> _data;
 public:
  vecmultiset(void) {
  }

  template<class InputIterator>
    vecmultiset(InputIterator beg, InputIterator end) {
    for(;beg!=end;++beg) {
      insert(*beg);      
    }
  }

  vecmultiset(KeyCompare &comp)
    : _comp(comp) {
  }  

  vecmultiset(vecmultiset const &src) 
    : _data(src._data) {
  }

  iterator begin(void) {
    return _data.begin();
  }

  iterator end(void) {
    return _data.end();
  }

  const_iterator begin(void) const {
    return _data.begin();
  }

  const_iterator end(void) const {
    return _data.end();
  }

  reverse_iterator rbegin(void) {
    return _data.rbegin();
  }

  reverse_iterator rend(void) {
    return _data.rend();
  }

  const_reverse_iterator rbegin(void) const {
    return _data.rbegin();
  }

  const_reverse_iterator rend(void) const {
    return _data.rend();
  }

  size_type size(void) const { return _data.size(); }
  bool empty(void) const { return _data.empty(); }
  key_compare key_comp(void) const { return key_compare(); }
  value_compare value_comp(void) const { return value_compare(); }

  vecmultiset const &operator=(vecmultiset const &src) {
    _data = src._data;
  }

  bool operator==(vecmultiset const &src) const {
    return _data == src._data;
  }

  bool operator<(vecmultiset const &src) const {
    return _data < src._data;
  }

  template<class InputIter>
  void insert(InputIter first, InputIter last)
  { for (; first != last; ++first) insert(*first); }
  
  std::pair<iterator, bool> insert(const value_type &x) {
    iterator i(std::lower_bound(_data.begin(),_data.end(),x,_comp));
    if(i != _data.end() && *i == x) {
      // item already present
      return std::make_pair(i,false);
    } else {
      return std::make_pair(_data.insert(i,x),true);
    }
  }

  iterator insert(iterator start, const value_type &x) {
    iterator i(std::lower_bound(start,_data.end(),x,_comp));
    if(i != _data.end() && *i == x) {
      // item already present
      return i;
    } else {
      return _data.insert(i,x);
    }
  }

  void erase(iterator pos) {
    _data.erase(pos);
  }

  size_type erase(value_type const &x) {
    iterator i(std::lower_bound(_data.begin(),_data.end(),x,_comp));
    if(i != _data.end() && *i == x) {
      _data.erase(i);
      return 1;
    } 
    return 0;
  }

  void erase(iterator beg, iterator end) {
    _data.erase(beg,end);
  }

  void clear(void) {
    _data.clear();
  }

  void swap(vecmultiset<T> &src) {
    _data.swap(src._data);
  }

  iterator find(value_type const &x) {
    iterator i(std::lower_bound(_data.begin(),_data.end(),x,_comp));
    if(i != _data.end() && *i == x) {
      return i;
    } else {
      return _data.end();
    }
  }

  const_iterator find(value_type const &x) const {
    const_iterator i(std::lower_bound(_data.begin(),_data.end(),x,_comp));
    if(i != _data.end() && *i == x) {
      return i;
    } else {
      return _data.end();
    }
  }

  iterator lower_bound(value_type const &x) {
    return std::lower_bound(_data.begin(),_data.end(),x,_comp);
  }

  iterator upper_bound(value_type const &x) {
    return std::upper_bound(_data.begin(),_data.end(),x,_comp);
  }
};

#endif
