const int maxn = 1010;
struct circles {
    circle c[maxn];
    double ans[maxn]; //ans[i] 表示被覆盖了 i 次的面积
    double pre[maxn];
    int n;
    circles() {}
    void add(circle cc) {
        c[n++] = cc;
    }
    //x 包含在 y 中
    bool inner(circle x, circle y) {
        if (x.relationcircle(y) != 1)
            return 0;
        return sgn(x.r - y.r) <= 0 ? 1 : 0;
    }
    //圆的面积并去掉内含的圆
    void init_or() {
        bool mark[maxn] = {0};
        int i, j, k = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                if (i != j && !mark[j]) {
                    if ((c[i] == c[j]) || inner(c[i], c[j]))
                        break;
                }
            if (j < n)
                mark[i] = 1;
        }
        for (i = 0; i < n; i++)
            if (!mark[i])
                c[k++] = c[i];
        n = k;
    }
    //圆的面积交去掉内含的圆
    void init_add() {
        int i, j, k;
        bool mark[maxn] = {0};
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                if (i != j && !mark[j]) {
                    if ((c[i] == c[j]) || inner(c[j], c[i]))
                        break;
                }
            if (j < n)
                mark[i] = 1;
        }
        for (i = 0; i < n; i++)
            if (!mark[i])
                c[k++] = c[i];
        n = k;
    }
    //半径为 r 的圆，弧度为 th 对应的弓形的面积
    double areaarc(double th, double r) {
        return 0.5 * r * r * (th - sin(th));
    }
    //测试 SPOJVCIRCLES SPOJCIRUT
    //SPOJVCIRCLES 求 n 个圆并的面积，需要加上 init_or() 去掉重复圆（否则WA）
    //SPOJCIRUT 是求被覆盖 k 次的面积，不能加 init_or()
    //对于求覆盖多少次面积的问题，不能解决相同圆，而且不能 init_or()
    //求多圆面积并，需要 init_or, 其中一个目的就是去掉相同圆
    void getarea() {
        memset(ans, 0, sizeof(ans));
        vector<pair<double, int> > v;
        for (int i = 0; i < n; i++) {
            v.clear();
            v.push_back(make_pair(-PI, 1));
            v.push_back(make_pair(PI, -1));
            for (int j = 0; j < n; j++)
                if (i != j) {
                    Point q = (c[j].p - c[i].p);
                    double ab = q.len(), ac = c[i].r, bc = c[j].r;
                    if (sgn(ab + ac - bc) <= 0) {
                        v.push_back(make_pair(-PI, 1));
                        v.push_back(make_pair(PI, -1));
                        continue;
                    }
                    if (sgn(ab + bc - ac) <= 0)
                        continue;
                    if (sgn(ab - ac - bc) > 0)
                        continue;
                    double th = atan2(q.y, q.x), fai = acos((ac * ac + ab * ab - bc * bc) / (2.0 * ac * ab));
                    double a0 = th - fai;
                    if (sgn(a0 + PI) < 0)
                        a0 += 2 * PI;
                    double a1 = th + fai;
                    if (sgn(a1 - PI) > 0)
                        a1 -= 2 * PI;
                    if (sgn(a0 - a1) > 0) {
                        v.push_back(make_pair(a0, 1));
                        v.push_back(make_pair(PI, -1));
                        v.push_back(make_pair(-PI, 1));
                        v.push_back(make_pair(a1, -1));
                    } else {
                        v.push_back(make_pair(a0, 1));
                        v.push_back(make_pair(a1, -1));
                    }
                }
            sort(v.begin(), v.end());
            int cur = 0;
            for (int j = 0; j < v.size(); j++) {
                if (cur && sgn(v[j].first - pre[cur])) {
                    ans[cur] += areaarc(v[j].first - pre[cur], c[i].r);
                    ans[cur] += 0.5 * (Point(c[i].p.x + c[i].r * cos(pre[cur]), c[i].p.y + c[i].r * sin(pre[cur])) ^ Point(c[i].p.x + c[i].r * cos(v[j].first), c[i].p.y + c[i].r * sin(v[j].first)));
                }
                cur += v[j].second;
                pre[cur] = v[j].first;
            }
        }
        for (int i = 1; i < n; i++)
            ans[i] -= ans[i + 1];
    }
};