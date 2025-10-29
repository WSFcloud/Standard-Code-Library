// A 必须是凸包 (而且是逆时针顺序)
// 测试 UVA 10173
double minRectangleCover(polygon A) {
    //要特判 A.n < 3 的情况
    if (A.n < 3)
        return 0.0;
    A.p[A.n] = A.p[0];
    double ans = -1;
    int r = 1, p = 1, q;
    for (int i = 0; i < A.n; i++) {
        //卡出离边 A.p[i] - A.p[i+1] 最远的点
        while (sgn(cross(A.p[i], A.p[i + 1], A.p[r + 1]) - cross(A.p[i], A.p[i + 1], A.p[r]))
               >= 0)
            r = (r + 1) % A.n;
        //卡出 A.p[i] - A.p[i+1] 方向上正向 n 最远的点
        while (sgn(dot(A.p[i], A.p[i + 1], A.p[p + 1]) - dot(A.p[i], A.p[i + 1], A.p[p])) >= 0)
            p = (p + 1) % A.n;
        if (i == 0)
            q = p;
        //卡出 A.p[i] - A.p[i+1] 方向上负向最远的点
        while (sgn(dot(A.p[i], A.p[i + 1], A.p[q + 1]) - dot(A.p[i], A.p[i + 1], A.p[q])) <= 0)
            q = (q + 1) % A.n;
        double d = (A.p[i] - A.p[i + 1]).len2();
        double tmp = cross(A.p[i], A.p[i + 1], A.p[r]) * (dot(A.p[i], A.p[i + 1], A.p[p]) - dot(A.p[i], A.p[i + 1], A.p[q])) / d;
        if (ans < 0 || ans > tmp)
            ans = tmp;
    }
    return ans;
}