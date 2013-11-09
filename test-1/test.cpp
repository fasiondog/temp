#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <cstdlib>
#include <cstring>

//使用vector<int>保存数据，深拷贝，不使用reserve
class A {
public:
    A(int n) {
        for (int i = 0; i < n; ++i) {
            _list.push_back(i);
        }
    }

    A(const A& x) {//: _list(x._list) {
		//std::cout << "A(const A& x)" << std::endl;
		_list = x._list;
    }

    virtual ~A() {}

    size_t size() const { return _list.size(); }

    int operator[](int i) const { return _list[i];}

private:
    std::vector<int> _list;
};

//使用vector<int>保存数据，深拷贝，使用reserve
class A1 {
public:
    A1(int n) {
        _list.reserve(n);
        for (int i = 0; i < n; ++i) {
            _list.push_back(i);
        }
    }

    A1(const A1& x) {// : _list(x._list) {
		//std::cout << "A1(const A1& x)" << std::endl;
		_list = x._list;
    }

    virtual ~A1() {}

    size_t size() const { return _list.size(); }

    int operator[](int i) const { return _list[i];}

private:
    std::vector<int> _list;
};

//使用shared_ptr<vector<int> >保存内部数据，浅拷贝，reserve
class B {
public:
    B(int n) {
        _plist = std::shared_ptr<std::vector<int> >(new std::vector<int>);
		_plist->reserve(n);
        for (int i = 0; i < n; ++i) {
            _plist->push_back(i);
        }    
    }

    B(const B& x) { //: _plist(x._plist) {
		//std::cout << "B(const B& x)" << std::endl;
		_plist = x._plist;
	}

    virtual ~B() {}

    size_t size() const { return _plist->size(); }

    int operator[](int i) const { return (*_plist)[i];}

private:
    std::shared_ptr<std::vector<int> > _plist;
};

//使用vector<int> * 保存内部数据，深拷贝，reserve
class C {
public:
    C(int n) {
        _plist = new std::vector<int>;
		_plist->reserve(n);
        for (int i = 0; i < n; ++i) {
            _plist->push_back(i);
        }
    }    

    C(const C& x) {
		//std::cout << "C(const C& x)" << std::endl;
        _plist = new std::vector<int>;
		(*_plist) = (*x._plist);
		/*_plist->reserve(x.size());
		size_t total = x.size();
        for (int i = 0; i < total; ++i) {
            _plist->push_back(x[i]);
        }*/
    }
	
    virtual ~C() { delete _plist; }

    size_t size() const { return _plist->size(); }

    int operator[](int i) const { return (*_plist)[i];}

private:
    std::vector<int> *_plist;
};

//使用vector<int> * 保存内部数据，深拷贝，reserve，实现C++11移动语义
class D {
public:
    D(int n) {
        _plist = new std::vector<int>;
        _plist->reserve(n);
        for (int i = 0; i < n; ++i) {
            _plist->push_back(i);
        }
    }    

    D(const D& x) {
		std::cout << "D(const D& x)" << std::endl;
        _plist = new std::vector<int>;
		(*_plist) = (*x._plist);
        /*_plist->reserve(x.size());
        for (int i = 0; i < x.size(); ++i) {
            _plist->push_back(x[i]);
        }*/
    }
	
	D(D&& x) { //: _plist(x._plist) {
		//std::cout << "D(D&& x)" << std::endl;
		_plist = x._plist;
        x._plist = 0;
    }
	
    virtual ~D() { delete _plist; }

    size_t size() const { return _plist->size(); }

    int operator[](int i) const { return (*_plist)[i];}

private:
    std::vector<int> *_plist;
};

//使用int *保证内部数据，深拷贝
class E {
public:
    E(int n):_size(n) {
        _plist = new int[n];
        for (int i = 0; i < n; ++i) {
            _plist[i] = i;
        }
    }    

    E(const E& x):_size(x._size) {
		//std::cout << "E(const E& x)" << std::endl;
        _plist = new int[_size];
        std::memcpy(_plist, x._plist, x._size * sizeof(int));
        /*for (int i = 0; i < x.size(); ++i) {
            _plist[i] = x[i];
        }*/
    }
	
#if 1
    E(E&& x): _size(x._size), _plist(x._plist) {
		//std::cout << "E(E&& x)" << std::endl;
        x._plist = 0;
    }
#endif

    virtual ~E() { delete[] _plist; }

    size_t size() const { return _size; }

    int operator[](int i) const { return _plist[i];}

private:
    size_t _size;
    int *_plist;
};

template <class T>
T func(int n) {
	T result(n);
	if (n <= 1) { //此处只用<，会被msvc优化掉
		//std::cout << "T Func" << std::endl;
		return T(1);
	}
	return result;
}

///编译时，需注意编译器优化NRO
int main() {
    unsigned long long t1=0, t2=0;
    int max = 50000;
    
    for (int i = 1; i < max; ++i) {
        //A a = func<A>(i);
		//A1 a = func<A1>(i);
        //B a = func<B>(i);
        //C a = func<C>(i);
        //D a = func<D>(i);
        E a = func<E>(i);
        for (int j = 1; j < a.size(); ++j) {
            t1 += a[j];
        }
        //t1 += a.size();
    }        

    std::cout << t1 << std::endl;
}
