struct polygon {
    int n;
    Point p[maxp];
    Line l[maxp];
    void input(int _n) {
        n = _n;
        for (int i = 0; i < n; i++)
            p[i].input();
    }
    void add(Point q) {
        p[n++] = q;
    }
    void getline() {
        for (int i = 0; i < n; i++) {
            l[i] = Line(p[i], p[(i + 1) % n]);
        }
    }
    struct cmp {
        Point p;
        cmp(const Point &p0) { p = p0; }
        bool operator()(const Point &aa, const Point &bb) {
            Point a = aa, b = bb;
            int d = sgn((a - p) ^ (b - p));
            if (d == 0) {
                return sgn(a.distance(p) - b.distance(p)) < 0;
            }
            return d > 0;
        }
    };
    //进行极角排序
    //首先需要找到最左下角的点
    //需要重载号好 Point 的 < 操作符 (min 函数要用)
    void norm() {
        Point mi = p[0];
        for (int i = 1; i < n; i++)
            mi = min(mi, p[i]);
        sort(p, p + n, cmp(mi));
    }
    //得到凸包
    //得到的凸包里面的点编号是 0∼n-1 的
    //两种凸包的方法
    //注意如果有影响，要特判下所有点共点，或者共线的特殊情况
    //测试 LightOJ1203 LightOJ1239
    void getconvex(polygon &convex) {
        sort(p, p + n);
        convex.n = n;
        for (int i = 0; i < min(n, 2); i++) {
            convex.p[i] = p[i];
        }
        if (convex.n == 2 && (convex.p[0] == convex.p[1]))
            convex.n--; //特判
        if (n <= 2)
            return;
        int &top = convex.n;
        top = 1;
        for (int i = 2; i < n; i++) {
            while (top && sgn((convex.p[top] - p[i]) ^ (convex.p[top - 1] - p[i])) <= 0)
                top--;
            convex.p[++top] = p[i];
        }
        int temp = top;
        convex.p[++top] = p[n - 2];
        for (int i = n - 3; i >= 0; i--) {
            while (top != temp && sgn((convex.p[top] - p[i]) ^ (convex.p[top - 1] - p[i])) <= 0)
                top--;
            convex.p[++top] = p[i];
        }
        if (convex.n == 2 && (convex.p[0] == convex.p[1]))
            convex.n--; //特判
        convex.norm();  //原来得到的是顺时针的点，排序后逆时针
    }
    //得到凸包的另外一种方法
    //测试 LightOJ1203 LightOJ1239
    void Graham(polygon &convex) {
        norm();
        int &top = convex.n;
        top = 0;
        if (n == 1) {
            top = 1;
            convex.p[0] = p[0];
            return;
        }
        if (n == 2) {
            top = 2;
            convex.p[0] = p[0];
            convex.p[1] = p[1];
            if (convex.p[0] == convex.p[1])
                top--;
            return;
        }
        convex.p[0] = p[0];
        convex.p[1] = p[1];
        top = 2;
        for (int i = 2; i < n; i++) {
            while (top > 1 && sgn((convex.p[top - 1] - convex.p[top - 2]) ^ (p[i] - convex.p[top - 2])) <= 0)
                top--;
            convex.p[top++] = p[i];
        }
        if (convex.n == 2 && (convex.p[0] == convex.p[1]))
            convex.n--; //特判
    }
    //判断是不是凸的
    bool isconvex() {
        bool s[2];
        memset(s, false, sizeof(s));
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int k = (j + 1) % n;
            s[sgn((p[j] - p[i]) ^ (p[k] - p[i])) + 1] = true;
            if (s[0] && s[2])
                return false;
        }
        return true;
    }
    //判断点和任意多边形的关系
    // 3 点上
    // 2 边上
    // 1 内部
    // 0 外部
    int relationpoint(Point q) {
        for (int i = 0; i < n; i++) {
            if (p[i] == q)
                return 3;
        }
        getline();
        for (int i = 0; i < n; i++) {
            if (l[i].pointonseg(q))
                return 2;
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int k = sgn((q - p[j]) ^ (p[i] - p[j]));
            int u = sgn(p[i].y - q.y);
            int v = sgn(p[j].y - q.y);
            if (k > 0 && u < 0 && v >= 0)
                cnt++;
            if (k < 0 && v < 0 && u >= 0)
                cnt--;
        }
        return cnt != 0;
    }
    //直线 u 切割凸多边形左侧
    //注意直线方向
    //测试：HDU3982
    void convexcut(Line u, polygon &po) {
        int &top = po.n; //注意引用
        top = 0;
        for (int i = 0; i < n; i++) {
            int d1 = sgn((u.e - u.s) ^ (p[i] - u.s));
            int d2 = sgn((u.e - u.s) ^ (p[(i + 1) % n] - u.s));
            if (d1 >= 0)
                po.p[top++] = p[i];
            if (d1 * d2 < 0)
                po.p[top++] = u.crosspoint(Line(p[i], p[(i
                                                         + 1)
                                                        % n]));
        }
    }
    //得到周长
    //测试 LightOJ1239
    double getcircumference() {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += p[i].distance(p[(i + 1) % n]);
        }
        return sum;
    }
    //得到面积
    double getarea() {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (p[i] ^ p[(i + 1) % n]);
        }
        return fabs(sum) / 2;
    }
    //得到方向
    // 1 表示逆时针，0 表示顺时针
    bool getdir() {
        double sum = 0;
        for (int i = 0; i < n; i++)
            sum += (p[i] ^ p[(i + 1) % n]);
        if (sgn(sum) > 0)
            return 1;
        return 0;
    }
    //得到重心
    Point getbarycentre() {
        Point ret(0, 0);
        double area = 0;
        for (int i = 1; i < n - 1; i++) {
            double tmp = (p[i] - p[0]) ^ (p[i + 1] - p[0]);
            if (sgn(tmp) == 0)
                continue;
            area += tmp;
            ret.x += (p[0].x + p[i].x + p[i + 1].x) / 3 * tmp;
            ret.y += (p[0].y + p[i].y + p[i + 1].y) / 3 * tmp;
        }
        if (sgn(area))
            ret = ret / area;
        return ret;
    }
    //多边形和圆交的面积
    //测试：POJ3675 HDU3982 HDU2892
    double areacircle(circle c) {
        double ans = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if (sgn((p[j] - c.p) ^ (p[i] - c.p)) >= 0)
                ans += c.areatriangle(p[i], p[j]);
            else
                ans -= c.areatriangle(p[i], p[j]);
        }
        return fabs(ans);
    }
    //多边形和圆关系
    // 2 圆完全在多边形内
    // 1 圆在多边形里面，碰到了多边形边界
    // 0 其它
    int relationcircle(circle c) {
        getline();
        int x = 2;
        if (relationpoint(c.p) != 1)
            return 0; //圆心不在内部
        for (int i = 0; i < n; i++) {
            if (c.relationseg(l[i]) == 2)
                return 0;
            if (c.relationseg(l[i]) == 1)
                x = 1;
        }
        return x;
    }
};