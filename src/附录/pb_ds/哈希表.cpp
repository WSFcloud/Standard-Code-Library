#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

cc_hash_table<string, int> mp1; // 拉链法
gp_hash_table<string, int> mp2; // 查探法（快一些）