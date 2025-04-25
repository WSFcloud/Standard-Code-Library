#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

int main() {
    for (int Case = 1; Case <= 10000; Case++) {
        cout << "==============\n";
        system("./generator");

        auto start = high_resolution_clock::now();
        system("./brute");
        auto end = high_resolution_clock::now();

        system("./std");

        if (system("diff -q std.out brute.out")) {
            cout << "\033[31mWrong Answer\n\033[0m";
            exit(0);
        } else {
            cout << "\033[32mAccept!\n\033[0m";
            auto duration = duration_cast<milliseconds>(end - start).count();
            cout << "测试点 #" << Case << "，用时 " << duration << "ms\n";
        }
    }
    return 0;
}
