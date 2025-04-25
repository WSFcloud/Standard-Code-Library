#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int Case = 1; Case <= 10000; Case++) {
        cout << "==============\n";
        system("generator.exe");
        double start = clock();
        system("brute.exe");
        double end = clock();
        system("std.exe");
        if (system("fc std.out brute.out")) {
            cout << "\033[31m" << "Wrong Answer\n"
                 << "\033[0m";
            exit(0);
        } else {
            cout << "\033[32m" << "Accept!\n"
                 << "\033[0m";
            cout << "测试点 #" << Case << "，用时" << end - start << "ms\n";
        }
    }
    return 0;
}