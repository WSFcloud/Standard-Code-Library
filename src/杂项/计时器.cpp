#include <iostream>
#include <chrono>
using namespace std;

// main函数开头定义Timer timer;即可
struct Timer {
	chrono::steady_clock::time_point start;
	Timer() : start(chrono::steady_clock::now()) {}
	~Timer() {
		auto finish = chrono::steady_clock::now();
		auto runtime = chrono::duration_cast<chrono::microseconds>(finish - start).count();
		cerr << runtime / 1e6 << "s" << endl;
	}
};