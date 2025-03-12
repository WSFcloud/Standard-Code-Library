#include <iostream>
#include <stdint.h>
#include <cpuid.h>
using namespace std;

int main() {
    uint32_t data[4];
    char str[48];
    for (int i = 0; i < 3; ++i) {
        __cpuid_count(0x80000002 + i, 0, data[0], data[1], data[2], data[3]);
        for (int j = 0; j < 4; ++j) {
            reinterpret_cast<uint32_t *>(str)[i * 4 + j] = data[j];
        }
    }
    cout << str << endl;
}