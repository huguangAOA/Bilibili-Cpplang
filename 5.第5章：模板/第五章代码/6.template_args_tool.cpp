/*************************************************************************
	> File Name: 6.template_args_tool.cpp
	> Author: hug
	> Mail: hug@haizeix.com
	> Created Time: 一  3/16 00:09:23 2026
 ************************************************************************/

#include <iostream>
using namespace std;

template<typename T, typename ...ARGS>
struct ARGS_TOOL {
    typedef T __type;
    typedef ARGS_TOOL<ARGS...> __rest;
};

template<typename T>
struct ARGS_TOOL<T> {
    typedef T __final;
};

template<typename ...ARGS>
class Test {
public :
    auto operator()(
        typename ARGS_TOOL<ARGS...>::__type a,
        typename ARGS_TOOL<ARGS...>::__rest::__final b) -> decltype(a + b) {
        return a + b;
    }
};

int main() {
    Test<int, double> f;
    cout << f(123, 456.7) << endl;
    return 0;
}
