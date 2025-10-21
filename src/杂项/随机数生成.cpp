mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng_64(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> disti(l, r);     // 生成区间 [l, r] 上的随机数
uniform_real_distribution<double> distr(l, r); // 生成区间 [l, r) 上的随机数
int random_int = disti(rng);
double random_double = distr(rng);