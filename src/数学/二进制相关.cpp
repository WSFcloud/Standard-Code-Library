#define get_th(x, i) ((x >> (i - 1)) & 1)       // 获取 x 的 i-th 的 bool 值
#define set_th(x, i) (x = x | (1 << (i - 1)))   // 强制 x 的 i-th 为 1
#define clear_th(x, i) (x = x & (1 << (i - 1))) // 强制 x 的 i-th 为 0