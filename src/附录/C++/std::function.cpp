#define DEFINE_FUN(func_name, return_type, ...) \
    std::function<return_type(__VA_ARGS__)> func_name = [&](__VA_ARGS__) -> return_type
// 直接使用 std::function
std::function<int(int)> fib_1;
fib_1 = [&](int n) { return n <= 2 ? 1 : fib_1(n - 1) + fib_1(n - 2); };
// 使用宏定义
DEFINE_FUN(fib_2, int, int n) {
    return n <= 2 ? 1 : fib_2(n - 1) + fib_2(n - 2);
};