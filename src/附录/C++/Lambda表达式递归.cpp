// C++ 14 (至少需要 GCC 9.3)
auto f = [&](auto &self, int i) -> int {
    return (i == 0) ? 1 : i * self(self, i - 1);
};
int x = f(f, 5);

// C++ 23 (至少需要 GCC 14 或 Clang 19)
auto g = [&](this auto &&self, int i) -> int {
    return (i == 0) ? 1 : i * self(i - 1);
};
int y = g(5);