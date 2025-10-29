using L3 = Line3;
using P3 = Point3;
// 正负性判断
int sign(ld x) {
    if (x > eps) {
        return 1;
    }
    if (x < -eps) {
        return -1;
    }
    return 0;
}
// 原点到当前点的距离计算
ld len(P3 p) {
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}
// 叉乘
P3 crossEx(P3 a, P3 b) {
    P3 ans;
    ans.x = a.y * b.z - a.z * b.y;
    ans.y = a.z * b.x - a.x * b.z;
    ans.z = a.x * b.y - a.y * b.x;
    return ans;
}
// 计算两个向量的叉乘模长（平行四边形面积）
ld cross(P3 a, P3 b) {
    return len(crossEx(a, b));
}
// 点乘
ld dot(P3 a, P3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
// 获取平面法向量
P3 getVec(Plane s) {
    return crossEx(s.u - s.v, s.v - s.w);
}
// 三维欧几里得距离公式
ld dis(P3 a, P3 b) {
    ld val = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
    return sqrt(val);
}
// 将三维向量转换为单位向量
P3 standardize(P3 vec) {
    return vec / len(vec);
}
// 三点是否共线
bool onLine(P3 p1, P3 p2, P3 p3) {
    return sign(cross(p1 - p2, p3 - p2)) == 0;
}
// 给定的三个点能否构成平面
bool onLine(Plane s) {
    return onLine(s.u, s.v, s.w);
}
// 四点是否共面
bool onPlane(P3 p1, P3 p2, P3 p3, P3 p4) {
    ld val = dot(getVec({p1, p2, p3}), p4 - p1);
    return sign(val) == 0;
}
// 判断空间点是否在线段上（包含端点）
bool pointOnSegment(P3 p, L3 seg) {
    bool collinear = (sign(cross(p - seg.a, p - seg.b)) == 0);
    bool in_x_range = min(seg.a.x, seg.b.x) <= p.x && p.x <= max(seg.a.x, seg.b.x);
    bool in_y_range = min(seg.a.y, seg.b.y) <= p.y && p.y <= max(seg.a.y, seg.b.y);
    bool in_z_range = min(seg.a.z, seg.b.z) <= p.z && p.z <= max(seg.a.z, seg.b.z);
    return collinear && in_x_range && in_y_range && in_z_range;
}

// 判断空间点是否在线段上（不包含端点）
bool pointOnSegmentEx(P3 p, L3 seg) {
    bool collinear = (sign(cross(p - seg.a, p - seg.b)) == 0);
    bool strictly_in_x = min(seg.a.x, seg.b.x) < p.x && p.x < max(seg.a.x, seg.b.x);
    bool strictly_in_y = min(seg.a.y, seg.b.y) < p.y && p.y < max(seg.a.y, seg.b.y);
    bool strictly_in_z = min(seg.a.z, seg.b.z) < p.z && p.z < max(seg.a.z, seg.b.z);
    return collinear && strictly_in_x && strictly_in_y && strictly_in_z;
}
// 空间两点是否在线段同侧
// 当给定的两点与线段不共面、点在线段上时返回 false
bool pointOnSegmentSide(P3 p1, P3 p2, L3 l) {
    if (!onPlane(p1, p2, l.a, l.b)) { // 特判不共面
        return 0;
    }
    ld val = dot(crossEx(l.a - l.b, p1 - l.b), crossEx(l.a - l.b, p2 - l.b));
    return sign(val) == 1;
}
// 两点是否在平面同侧
// 点在平面上时返回 false
bool pointOnPlaneSide(P3 p1, P3 p2, Plane s) {
    ld val = dot(getVec(s), p1 - s.u) * dot(getVec(s), p2 - s.u);
    return sign(val) == 1;
}
// 空间两直线是否平行
bool lineParallel(L3 l1, L3 l2) {
    return sign(cross(l1.a - l1.b, l2.a - l2.b)) == 0;
}
// 空间两直线是否垂直
bool lineVertical(L3 l1, L3 l2) {
    return sign(dot(l1.a - l1.b, l2.a - l2.b)) == 0;
}
// 两平面是否平行
bool planeParallel(Plane s1, Plane s2) {
    ld val = cross(getVec(s1), getVec(s2));
    return sign(val) == 0;
}
// 两平面是否垂直
bool planeVertical(Plane s1, Plane s2) {
    ld val = dot(getVec(s1), getVec(s2));
    return sign(val) == 0;
}
// 空间两直线是否是同一条
bool same(L3 l1, L3 l2) {
    return lineParallel(l1, l2) && lineParallel({l1.a, l2.b}, {l1.b, l2.a});
}
// 两平面是否是同一个
bool same(Plane s1, Plane s2) {
    bool a = onPlane(s1.u, s2.u, s2.v, s2.w);
    bool b = onPlane(s1.v, s2.u, s2.v, s2.w);
    bool c = onPlane(s1.w, s2.u, s2.v, s2.w);
    return a && b && c;
}
// 直线是否与平面平行
bool linePlaneParallel(L3 l, Plane s) {
    ld val = dot(l.a - l.b, getVec(s));
    return sign(val) == 0;
}
// 空间两线段是否相交
bool segmentIntersection(L3 l1, L3 l2) {    // 重叠、相交于端点均视为相交
    if (!onPlane(l1.a, l1.b, l2.a, l2.b)) { // 特判不共面
        return 0;
    }
    if (!onLine(l1.a, l1.b, l2.a) || !onLine(l1.a, l1.b, l2.b)) {
        return !pointOnSegmentSide(l1.a, l1.b, l2) && !pointOnSegmentSide(l2.a, l2.b, l1);
    }
    return pointOnSegment(l1.a, l2) || pointOnSegment(l1.b, l2) || pointOnSegment(l2.a, l1) || pointOnSegment(l2.b, l2);
}
bool segmentIntersection1(L3 l1, L3 l2) { // 重叠、相交于端点不视为相交
    return onPlane(l1.a, l1.b, l2.a, l2.b) && !pointOnSegmentSide(l1.a, l1.b, l2) && !pointOnSegmentSide(l2.a, l2.b, l1);
}
// 空间两直线是否相交及交点
// 当两直线不共面、两直线平行时返回 false
pair<bool, P3> lineIntersection(L3 l1, L3 l2) {
    if (!onPlane(l1.a, l1.b, l2.a, l2.b) || lineParallel(l1, l2)) {
        return {0, {}};
    }
    auto [s1, e1] = l1;
    auto [s2, e2] = l2;
    ld val = 0;
    if (!onPlane(l1.a, l1.b, {0, 0, 0}, {0, 0, 1})) {
        val = ((s1.x - s2.x) * (s2.y - e2.y) - (s1.y - s2.y) * (s2.x - e2.x)) / ((s1.x - e1.x) * (s2.y - e2.y) - (s1.y - e1.y) * (s2.x - e2.x));
    } else if (!onPlane(l1.a, l1.b, {0, 0, 0}, {0, 1, 0})) {
        val = ((s1.x - s2.x) * (s2.z - e2.z) - (s1.z - s2.z) * (s2.x - e2.x)) / ((s1.x - e1.x) * (s2.z - e2.z) - (s1.z - e1.z) * (s2.x - e2.x));
    } else {
        val = ((s1.y - s2.y) * (s2.z - e2.z) - (s1.z - s2.z) * (s2.y - e2.y)) / ((s1.y - e1.y) * (s2.z - e2.z) - (s1.z - e1.z) * (s2.y - e2.y));
    }
    return {1, s1 + (e1 - s1) * val};
}
// 直线与平面是否相交及交点
// 当直线与平面平行、给定的点构不成平面时返回 false
pair<bool, P3> linePlaneCross(L3 l, Plane s) {
    if (linePlaneParallel(l, s)) {
        return {0, {}};
    }
    P3 vec = getVec(s);
    P3 U = vec * (s.u - l.a), V = vec * (l.b - l.a);
    ld val = (U.x + U.y + U.z) / (V.x + V.y + V.z);
    return {1, l.a + (l.b - l.a) * val};
}
// 两平面是否相交及交线
// 当两平面平行、两平面为同一个时返回 false
pair<bool, L3> planeIntersection(Plane s1, Plane s2) {
    if (planeParallel(s1, s2) || same(s1, s2)) {
        return {0, {}};
    }
    P3 U = linePlaneParallel({s2.u, s2.v}, s1) ? linePlaneCross({s2.v, s2.w}, s1).second : linePlaneCross({s2.u, s2.v}, s1).second;
    P3 V = linePlaneParallel({s2.w, s2.u}, s1) ? linePlaneCross({s2.v, s2.w}, s1).second : linePlaneCross({s2.w, s2.u}, s1).second;
    return {1, {U, V}};
}
// 点到直线的最近点与最近距离
pair<ld, P3> pointToLine(P3 p, L3 l) {
    ld val = cross(p - l.a, l.a - l.b) / dis(l.a, l.b); // 面积除以底边长
    ld val1 = dot(p - l.a, l.a - l.b) / dis(l.a, l.b);
    return {val, l.a + val1 * standardize(l.a - l.b)};
}
// 点到平面的最近点与最近距离
pair<ld, P3> pointToPlane(P3 p, Plane s) {
    P3 vec = getVec(s);
    ld val = dot(vec, p - s.u);
    val = abs(val) / len(vec); // 面积除以底边长
    return {val, p - val * standardize(vec)};
}
// 空间两直线的最近距离与最近点对
tuple<ld, P3, P3> lineToLine(L3 l1, L3 l2) {
    P3 vec = crossEx(l1.a - l1.b, l2.a - l2.b); // 计算同时垂直于两直线的向量
    ld val = abs(dot(l1.a - l2.a, vec)) / len(vec);
    P3 U = l1.b - l1.a, V = l2.b - l2.a;
    vec = crossEx(U, V);
    ld p = dot(vec, vec);
    ld t1 = dot(crossEx(l2.a - l1.a, V), vec) / p;
    ld t2 = dot(crossEx(l2.a - l1.a, U), vec) / p;
    return {val, l1.a + (l1.b - l1.a) * t1, l2.a + (l2.b - l2.a) * t2};
}
// 任意位置的空间两直线夹角的 cos 值
ld lineCos(L3 l1, L3 l2) {
    return dot(l1.a - l1.b, l2.a - l2.b) / len(l1.a - l1.b) / len(l2.a - l2.b);
}
// 空间两平面夹角的 cos 值
ld planeCos(Plane s1, Plane s2) {
    P3 U = getVec(s1), V = getVec(s2);
    return dot(U, V) / len(U) / len(V);
}
// 直线与平面夹角的 sin 值
ld linePlaneSin(L3 l, Plane s) {
    P3 vec = getVec(s);
    return dot(l.a - l.b, vec) / len(l.a - l.b) / len(vec);
}