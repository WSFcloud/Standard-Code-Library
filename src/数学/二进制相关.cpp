// 获取 x 的第 i 位的 bool 值
int get_th(int x, int i) {
    return (x >> i) & 1;
}
// 设置 x 的第 i 位为 1
void set_th(int &x, int i) {
    x = x | (1 << i);
}
// 设置 x 的第 i 位为 0
void clear_th(int &x, int i) {
    x = x & ~(1 << i);
}
// 将 x 的第 i 位取反
void flip_th(int &x, int i) {
    x ^= (1 << i);
}
// 取出 x 的第 0 位到第 i 位
int get_low(int x, int i) {
    return x & ((1 << (i + 1)) - 1);
}
// 将 x 加上 $v \times 2 ^ i$
void make_th(int &x, int i, int v) {
    x = x + (v << i);
}