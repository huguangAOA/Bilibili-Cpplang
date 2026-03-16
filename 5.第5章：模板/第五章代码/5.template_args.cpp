/*************************************************************************
	> File Name: 5.template_args.cpp
	> Author: hug
	> Mail: hug@haizeix.com
	> Created Time: 日  3/15 23:02:32 2026
 ************************************************************************/

#include <iostream>
#include <functional>
using namespace std;

template<typename T>
void print(T &a) {
    cout << "left : " << a << endl;
    return ;
}

template<typename T>
void print(T &&a) {
    cout << "right : " << a << endl;
    return ;
}

template<typename T, typename ...ARGS> 
void print(T &&a, ARGS &&...args) {
    cout << a << endl;
    print(std::forward<ARGS>(args)...);
    return ;
}

struct Point {
    int x, y;
};

ostream &operator<<(ostream &out, const Point &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

int main() {
    Point p1 = {3, 4};
    print(1); // right
    print(12.3, "hello world"); // left
    print(12.3, string("hello world")); // right
    print("hug", 45.6, p1); // left
    return 0;
}
