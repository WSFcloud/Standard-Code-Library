// 查找 $y$ 年 $m$ 月 $d$ 日是星期几
int week(int y, int m, int d) {
    if (m <= 2) {
        m += 12;
        y--;
    }
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;
}

const int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 检查 $y$ 年是否为闰年
bool isLeap(int y) {
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}
// 查找 $y$ 年 $m$ 月有几天
int daysInMonth(int y, int m) {
    return d[m - 1] + (isLeap(y) && m == 2);
}
// 查找 $y$ 年 $m$ 月 $d$ 日是星期几
int getDay(int y, int m, int d) {
    int ans = 0;
    for (int i = 1970; i < y; i++) {
        ans += 365 + isLeap(i);
    }
    for (int i = 1; i < m; i++) {
        ans += daysInMonth(y, i);
    }
    ans += d;
    return (ans + 2) % 7 + 1;
}