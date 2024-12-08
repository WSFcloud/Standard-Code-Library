#include <string>
using namespace std;

// 将奇数下标的字母大小写转换
void rev(std::string &s) {
    int l = s.size();
    for (int i = 1; i < l; i += 2) {
        if (std::isupper(s[i])) {
            s[i] = std::tolower(s[i]);
        } else {
            s[i] = std::toupper(s[i]);
        }
    }
}
// 获取在字母表中的序号
int get(char c) {
    int x;
    if (std::islower(c)) {
        x = c - 'a';
    } else {
        x = 26 + c - 'A';
    }
    return x;
}