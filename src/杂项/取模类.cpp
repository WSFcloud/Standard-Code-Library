using ll = long long;
using ull = unsigned long long;
using uint = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;

template <class T>
constexpr T qpow(T a, ull b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <uint P>
constexpr uint mulMod(uint a, uint b) {
    return ull(a) * b % P;
}

template <ull P>
constexpr ull mulMod(ull a, ull b) {
    ull res = a * b - ull(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

constexpr ll safeMod(ll x, ll m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

constexpr pair<ll, ll> invGcd(ll a, ll b) {
    a = safeMod(a, b);
    if (a == 0) {
        return {b, 0};
    }
    ll s = b, t = a;
    ll m0 = 0, m1 = 1;
    while (t) {
        ll u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        swap(s, t);
        swap(m0, m1);
    }
    if (m0 < 0) {
        m0 += b / s;
    }
    return {s, m0};
}

template <unsigned_integral U, U P>
struct ModIntBase {
public:
    constexpr ModIntBase() :
        x(0) {}
    template <unsigned_integral T>
    constexpr ModIntBase(T x_) :
        x(x_ % mod()) {}
    template <signed_integral T>
    constexpr ModIntBase(T x_) {
        using S = make_signed_t<U>;
        S v = x_ % S(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr U val() const {
        return x;
    }
    constexpr static U mod() {
        return P;
    }
    constexpr ModIntBase inv() const {
        return qpow(*this, mod() - 2);
    }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }
    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<mod()>(x, rhs.val());
        return *this;
    }
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }
    friend constexpr bool operator==(const ModIntBase &lhs, const ModIntBase &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr strong_ordering operator<=>(const ModIntBase &lhs, const ModIntBase &rhs) {
        return lhs.val() <=> rhs.val();
    }
    friend constexpr istream &operator>>(istream &is, ModIntBase &a) {
        ll i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const ModIntBase &a) {
        return os << a.val();
    }

private:
    U x;
};

template <uint P>
using ModInt = ModIntBase<uint, P>;
template <ull P>
using ModInt64 = ModIntBase<ull, P>;

struct Barrett {
public:
    Barrett(uint m_) :
        m(m_), im((ull)(-1) / m_ + 1) {}

    constexpr uint mod() const {
        return m;
    }
    constexpr uint mul(uint a, uint b) const {
        ull z = a;
        z *= b;
        ull x = ull((u128(z) * im) >> 64);
        uint v = uint(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

private:
    uint m;
    ull im;
};

template <uint Id>
struct DynModInt {
public:
    constexpr DynModInt() :
        x(0) {}
    template <unsigned_integral T>
    constexpr DynModInt(T x_) :
        x(x_ % mod()) {}
    template <signed_integral T>
    constexpr DynModInt(T x_) {
        int v = x_ % int(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static void setMod(uint m) {
        bt = m;
    }

    constexpr uint val() const {
        return x;
    }
    static uint mod() {
        return bt.mod();
    }
    constexpr DynModInt inv() const {
        auto v = invGcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    constexpr DynModInt operator-() const {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }
    constexpr DynModInt &operator+=(const DynModInt &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr DynModInt &operator-=(const DynModInt &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr DynModInt &operator*=(const DynModInt &rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }
    constexpr DynModInt &operator/=(const DynModInt &rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt &rhs) {
        lhs /= rhs;
        return lhs;
    }
    friend constexpr bool operator==(const DynModInt &lhs, const DynModInt &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr strong_ordering operator<=>(const DynModInt &lhs, const DynModInt &rhs) {
        return lhs.val() <=> rhs.val();
    }
    friend constexpr istream &operator>>(istream &is, DynModInt &a) {
        ll i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const DynModInt &a) {
        return os << a.val();
    }

private:
    uint x;
    static Barrett bt;
};

template <uint Id>
Barrett DynModInt<Id>::bt = 998244353;

// using Z = ModInt<1000000007>;
// using DZ1 = DynModInt<1>;
// using DZ2 = DynModInt<2>;
// DynModInt<1>::setMod(998244353);
// DynModInt<2>::setMod(1000000007);