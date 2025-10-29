//多边形是逆时针的，在 q1q2 的左侧
//测试:HDU3982
vector<Point> convexCut(const vector<Point> &ps, Point q1, Point q2) {
    vector<Point> qs;
    int n = ps.size();
    for (int i = 0; i < n; i++) {
        Point p1 = ps[i], p2 = ps[(i + 1) % n];
        int d1 = sgn((q2 - q1) ^ (p1 - q1)), d2 = sgn((q2 - q1) ^ (p2 - q1));
        if (d1 >= 0)
            qs.push_back(p1);
        if (d1 * d2 < 0)
            qs.push_back(Line(p1, p2).crosspoint(Line(q1, q2)));
    }
    return qs;
}