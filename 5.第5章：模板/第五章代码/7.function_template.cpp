/*************************************************************************
	> File Name: 7.function_template.cpp
	> Author: hug
	> Mail: hug@haizeix.com
	> Created Time: 二  3/17 00:22:38 2026
 ************************************************************************/

#include <iostream>
#include <functional>
using namespace std;

int add1(int a, int b) {
    return a + b;
}

class ADD {
public :
    int operator()(int a, int b, int c) {
        return a + b + c;
    }
} add2;

namespace chuanshuo {

template<typename T, typename ...ARGS>
class Base_Func {
public :
    virtual T operator()(ARGS...) = 0;
    virtual Base_Func *get_copy() = 0;
    virtual ~Base_Func();
};

template<typename T, typename ...ARGS>
class normal_function : public Base_Func<T, ARGS...> {
public :
    typedef T (*Func_Ptr)(ARGS...);
    normal_function(Func_Ptr ptr) : ptr(ptr) {}
    T operator()(ARGS... args) override {
        return this->ptr(std::forward<ARGS>(args)...);
    }
    Base_Func<T, ARGS...> *get_copy() override {
        return new normal_function(ptr);
    }
    Func_Ptr ptr;
};

template<typename CLASS_TYPE, typename T, typename ...ARGS>
class callable_object : public Base_Func<T, ARGS...> {
public :
    callable_object(CLASS_TYPE &obj) : obj(obj) {}
    T operator()(ARGS... args) override {
        return this->obj(std::forward<ARGS>(args)...);
    }
    Base_Func<T, ARGS...> *get_copy() override {
        return new callable_object(obj);
    }
    CLASS_TYPE &obj;
};

template<typename T, typename ...ARGS> class function;

template<typename T, typename ...ARGS>
class function<T(ARGS...)> {
public :
    typedef T (*Func_Ptr)(ARGS...);
    function(Func_Ptr ptr) 
    : ptr(new normal_function<T, ARGS...>(ptr)) {}
    
    template<typename CLASS_TYPE>
    function(CLASS_TYPE &obj) 
    : ptr(new callable_object<CLASS_TYPE, T, ARGS...>(obj)) {}
    
    function(const function &fobj) {
        this->ptr = fobj.ptr->get_copy();
    }

    T operator()(ARGS... args) {
        return this->ptr->operator()(std::forward<ARGS>(args)...);
    }
    Base_Func<T, ARGS...> *ptr;
    ~function() {
        if (ptr != nullptr) delete ptr;
    }
};

}

int main() {
    chuanshuo::function<int(int, int)> f1 = add1;
    chuanshuo::function<int(int, int, int)> f2 = add2;
    chuanshuo::function<int(int, int)> f3 = f1;
    cout << f1(3, 4) << endl; // 7
    cout << f2(4, 5, 6) << endl; // 15
    return 0;
}
