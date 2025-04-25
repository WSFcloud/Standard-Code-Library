#include <iostream>
using namespace std;
int main() {
    cout << "C++ Standard: ";
    if (__cplusplus == 202002L)
        cout << "C++20" << endl;
    else if (__cplusplus == 201703L)
        cout << "C++17" << endl;
    else if (__cplusplus == 201402L)
        cout << "C++14" << endl;
    else if (__cplusplus == 201103L)
        cout << "C++11" << endl;
    else
        cout << "Pre-C++11 or other: " << __cplusplus << endl;
    cout << "Compiler version: " << __VERSION__ << endl;
    return 0;
}