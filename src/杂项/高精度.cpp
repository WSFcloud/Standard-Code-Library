#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define MAXN 9999
#define MAXSIZE 1010
#define DLEN 4

class BigNum {
private:
    int a[500];
    // 可以控制大数的位数
    int len;

public:
    BigNum() {
        len = 1;
        memset(a, 0, sizeof(a));
    }
    // 构造函数
    BigNum(const int);
    // 将一个int类型的变量转化成大数
    BigNum(const char *);
    // 将一个字符串类型的变量转化为大数
    BigNum(const BigNum &);                          // 拷贝构造函数
    BigNum &operator=(const BigNum &);               // 重载赋值运算符，大数之间进行赋值运算
    friend istream &operator>>(istream &, BigNum &); // 重载输入运算符
    friend ostream &operator<<(ostream &, BigNum &); // 重载输出运算符
    BigNum operator+(const BigNum &) const;
    // 重载加法运算符，两个大数之间的相加运算
    BigNum operator-(const BigNum &) const;
    // 重载减法运算符，两个大数之间的相减运算
    BigNum operator*(const BigNum &) const;
    // 重载乘法运算符，两个大数之间的相乘运算
    BigNum operator/(const int &) const;
    // 重载除法运算符，大数对一个整数进行相除运算
    BigNum operator^(const int &) const;
    // 大数的 n 次方运算
    int operator%(const int &) const;
    // 大数对一个类型的变量进行取模运算int
    bool operator>(const BigNum &T) const;
    // 大数和另一个大数的大小比较
    bool operator>(const int &t) const;
    // 大数和一个 int 类型的变量的大小比较
    void print();
    // 输出大数
};
// 将一个int类型的变量转化为大数
BigNum::BigNum(const int b) {
    int c, d = b;
    len = 0;
    memset(a, 0, sizeof(a));
    while (d > MAXN) {
        c = d - (d / (MAXN + 1)) * (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}
// 将一个字符串类型的变量转化为大数
BigNum::BigNum(const char *s) {
    int t, k, index, L, i;
    memset(a, 0, sizeof(a));
    L = strlen(s);
    len = L / DLEN;
    if (L % DLEN)
        len++;
    index = 0;
    for (i = L - 1; i >= 0; i -= DLEN) {
        t = 0;
        k = i - DLEN + 1;
        if (k < 0)
            k = 0;
        for (int j = k; j <= i; j++)
            t = t * 10 + s[j] - '0';
        a[index++] = t;
    }
}
// 拷贝构造函数
BigNum::BigNum(const BigNum &T) :
    len(T.len) {
    int i;
    memset(a, 0, sizeof(a));
    for (i = 0; i < len; i++)
        a[i] = T.a[i];
}
// 重载赋值运算符，大数之间赋值运算
BigNum &BigNum::operator=(const BigNum &n) {
    int i;
    len = n.len;
    memset(a, 0, sizeof(a));
    for (i = 0; i < len; i++)
        a[i] = n.a[i];
    return *this;
}
istream &operator>>(istream &in, BigNum &b) {
    char ch[MAXSIZE * 4];
    int i = -1;
    in >> ch;
    int L = strlen(ch);
    int count = 0, sum = 0;
    for (i = L - 1; i >= 0;) {
        sum = 0;
        int t = 1;
        for (int j = 0; j < 4 && i >= 0; j++, i--, t *= 10) {
            sum += (ch[i] - '0') * t;
        }
        b.a[count] = sum;
        count++;
    }
    b.len = count++;
    return in;
}
// 重载输出运算符
ostream &operator<<(ostream &out, BigNum &b) {
    int i;
    cout << b.a[b.len - 1];
    for (i = b.len - 2; i >= 0; i--) {
        printf("%04d", b.a[i]);
    }
    return out;
}
// 两个大数之间的相加运算
BigNum BigNum::operator+(const BigNum &T) const {
    BigNum t(*this);
    int i, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++) {
        t.a[i] += T.a[i];
        if (t.a[i] > MAXN) {
            t.a[i + 1]++;
            t.a[i] -= MAXN + 1;
        }
    }
    if (t.a[big] != 0)
        t.len = big + 1;
    else
        t.len = big;
    return t;
}
// 两个大数之间的相减运算
BigNum BigNum::operator-(const BigNum &T) const {
    int i, j, big;
    bool flag;
    BigNum t1, t2;
    if (*this > T) {
        t1 = *this;
        t2 = T;
        flag = 0;
    } else {
        t1 = T;
        t2 = *this;
        flag = 1;
    }
    big = t1.len;
    for (i = 0; i < big; i++) {
        if (t1.a[i] < t2.a[i]) {
            j = i + 1;
            while (t1.a[j] == 0)
                j++;
            t1.a[j--]--;
            while (j > i)
                t1.a[j--] += MAXN;
            t1.a[i] += MAXN + 1 - t2.a[i];
        } else
            t1.a[i] -= t2.a[i];
    }
    t1.len = big;
    while (t1.a[t1.len - 1] == 0 && t1.len > 1) {
        t1.len--;
        big--;
    }
    if (flag)
        t1.a[big - 1] = 0 - t1.a[big - 1];
    return t1;
}
// 两个大数之间的相乘
BigNum BigNum::operator*(const BigNum &T) const {
    BigNum ret;
    int i, j, up;
    int temp, temp1;
    for (i = 0; i < len; i++) {
        up = 0;
        for (j = 0; j < T.len; j++) {
            temp = a[i] * T.a[j] + ret.a[i + j] + up;
            if (temp > MAXN) {
                temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);
                up = temp / (MAXN + 1);
                ret.a[i + j] = temp1;
            } else {
                up = 0;
                ret.a[i + j] = temp;
            }
        }
        if (up != 0)
            ret.a[i + j] = up;
    }
    ret.len = i + j;
    while (ret.a[ret.len - 1] == 0 && ret.len > 1)
        ret.len--;
    return ret;
}
// 大数对一个整数进行相除运算
BigNum BigNum::operator/(const int &b) const {
    BigNum ret;
    int i, down = 0;
    for (i = len - 1; i >= 0; i--) {
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
    }
    ret.len = len;
    while (ret.a[ret.len - 1] == 0 && ret.len > 1)
        ret.len--;
    return ret;
}
// 大数对一个int类型的变量进行取模
int BigNum::operator%(const int &b) const {
    int i, d = 0;
    for (i = len - 1; i >= 0; i--)
        d = ((d * (MAXN + 1)) % b + a[i]) % b;
    return d;
}
// 大数的n次方运算
BigNum BigNum::operator^(const int &n) const {
    BigNum t, ret(1);
    int i;
    if (n < 0)
        exit(-1);
    if (n == 0)
        return 1;
    if (n == 1)
        return *this;
    int m = n;
    while (m > 1) {
        t = *this;
        for (i = 1; (i << 1) <= m; i <<= 1)
            t = t * t;
        m -= i;
        ret = ret * t;
        if (m == 1)
            ret = ret * (*this);
    }
    return ret;
}
// 大数和另一个大数的大小比较
bool BigNum::operator>(const BigNum &T) const {
    int ln;
    if (len > T.len)
        return true;
    else if (len == T.len) {
        ln = len - 1;
        while (a[ln] == T.a[ln] && ln >= 0)
            ln--;
        if (ln >= 0 && a[ln] > T.a[ln])
            return true;
        else
            return false;
    } else
        return false;
}
// 大数和一个int类型的变量的大小比较
bool BigNum::operator>(const int &t) const {
    BigNum b(t);
    return *this > b;
}
// 输出大数
void BigNum::print() {
    int i;
    printf("%d", a[len - 1]);
    for (i = len - 2; i >= 0; i--) {
        printf("%04d", a[i]);
    }
    printf("\n");
}