mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());

vector<int> MODS = {1099999997, 1099999961, 1099999907, 1099999819, 1099999781, 1099999723, 1099999721, 1099999711,
                    1099999657, 1099999613, 1099999601, 1099999573, 1099999561, 1099999543, 1099999531, 1099999507,
                    1099999477, 1099999429, 1099999427, 1099999393, 1099999349, 1099999301, 1099999289, 1099999279,
                    1099999267, 1099999231, 1099999189, 1099999151, 1099999141, 1099999111, 1099999079, 1099999067,
                    1099999057, 1099999049, 1099999037, 1099998997, 1099998961, 1099998959, 1099998929, 1099998883,
                    1099998877, 1099998871, 1099998859, 1099998847, 1099998827, 1099998733, 1099998727, 1099998709,
                    1099998707, 1099998701, 1099998659, 1099998649, 1099998629, 1099998587, 1099998577, 1099998541,
                    1099998533, 1099998511, 1099998509, 1099998467, 1099998443, 1099998409, 1099998377, 1099998371,
                    1099998353, 1099998343, 1099998337, 1099998313, 1099998287, 1099998281, 1099998269, 1099998257,
                    1099998227, 1099998169, 1099998157, 1099998149, 1099998131, 1099998083, 1099998041, 1099998037,
                    1099998001, 1099997957, 1099997953, 1099997929, 1099997909, 1099997879, 1099997867, 1099997863,
                    1099997861, 1099997849, 1099997813, 1099997741, 1099997737, 1099997719, 1099997693, 1099997687,
                    1099997671, 1099997627, 1099997623, 1099997617, 892846183, 892846133, 892846111, 892846091,
                    892846051, 892846021, 892845983, 892845979, 892845977, 892845949, 892845931, 892845917, 892845893,
                    892845871, 892845869, 892845847, 892845817, 892845799, 892845769, 892845743, 892845727, 892845719,
                    892845677, 892845641, 892845619, 892845617, 892845563, 892845529, 892845497, 892845469, 892845461,
                    892845449, 892845427, 892845413, 892845391, 892845383, 892845361, 892845329, 892845319, 892845311,
                    892845277, 892845259, 892845223, 892845221, 892845209, 892845139, 892845137, 892845071, 892845067,
                    892845061};

const int base1 = uniform_int_distribution<ll>(30, 60)(rng), mod1 = MODS[uniform_int_distribution<ll>(0, 75)(rng)];
const int base2 = uniform_int_distribution<ll>(61, 80)(rng), mod2 = MODS[uniform_int_distribution<ll>(76, 149)(rng)];

int pow1[N], inv1[N], pow2[N], inv2[N];
pair<int, int> hashing[N];

int add(int a, int b, int mod) {
    int ans = a + b;
    if (ans >= mod)
        ans -= mod;
    if (ans < 0)
        ans += mod;
    return ans;
}

int mul(int a, int b, int mod) {
    int ans = (a * 1ll * b) % mod;
    if (ans < 0)
        ans += mod;
    return ans;
}

int power(int a, int b, int mod) {
    if (b <= 0) return 1;
    int ret = power(mul(a, a, mod), b / 2, mod);
    if (b % 2) ret = mul(ret, a, mod);
    return ret;
}

void PreCalc() // Don't forget to call it before all the test cases
{
    pow1[0] = inv1[0] = pow2[0] = inv2[0] = 1;
    int pw_inv1 = power(base1, mod1 - 2, mod1);
    int pw_inv2 = power(base2, mod2 - 2, mod2);

    for (int i = 1; i < N; ++i) {
        pow1[i] = mul(pow1[i - 1], base1, mod1);
        inv1[i] = mul(inv1[i - 1], pw_inv1, mod1);
        pow2[i] = mul(pow2[i - 1], base2, mod2);
        inv2[i] = mul(inv2[i - 1], pw_inv2, mod2);
    }
}

void BuildHash(string &s) {
    int n = s.length();
    for (int i = 0; i < n; ++i) {
        hashing[i].first = add(((i == 0) ? 0 : hashing[i - 1].first), mul(pow1[i], s[i] - 'a' + 1, mod1), mod1);
        hashing[i].second = add(((i == 0) ? 0 : hashing[i - 1].second), mul(pow2[i], s[i] - 'a' + 1, mod2), mod2);
    }
}

pair<int, int> GetHash(int l, int r) {
    pair<int, int> ans;
    ans.first = add(hashing[r].first, ((l == 0) ? 0 : -hashing[l - 1].first), mod1);
    ans.second = add(hashing[r].second, ((l == 0) ? 0 : -hashing[l - 1].second), mod2);
    ans.first = mul(ans.first, inv1[l], mod1);
    ans.second = mul(ans.second, inv2[l], mod2);
    return ans;
}


pair<int, int> GetFullHash(string &s) {
    int n = s.length();
    pair<int, int> hash[2];
    for (int i = 0; i < n; ++i) {
        hash[i & 1].first = add(((i == 0) ? 0 : hash[(i - 1) & 1].first), mul(pow1[i], s[i] - 'a' + 1, mod1), mod1);
        hash[i & 1].second = add(((i == 0) ? 0 : hash[(i - 1) & 1].second), mul(pow2[i], s[i] - 'a' + 1, mod2), mod2);
    }
    return hash[(n - 1) & 1];
}