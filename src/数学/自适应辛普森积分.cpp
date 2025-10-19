constexpr double EPS = 1e-9;
double f(double x) { // 被积函数
    return x * x * sin(x);
}
double simpson(double (*f)(double), double l, double r) {
    double mid = (l + r) / 2;
    return (f(l) + 4 * f(mid) + f(r)) * (r - l) / 6;
}
double rec(double (*f)(double), double l, double r, double eps, double st) {
    double mid = (l + r) / 2;
    double sl = simpson(f, l, mid);
    double sr = simpson(f, mid, r);
    if (abs(sl + sr - st) <= 15 * eps) {
        return sl + sr + (sl + sr - st) / 15;
    }
    return rec(f, l, mid, eps / 2, sl) + rec(f, mid, r, eps / 2, sr);
}
double calc(double (*f)(double), double l, double r) {
    return rec(f, l, r, EPS, simpson(f, l, r));
}