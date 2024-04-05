
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());


int base1 = uniform_int_distribution<ll>(30,  50)(rng), mod1 = 1e9 + 7;
int base2 = uniform_int_distribution<ll>(51,  70)(rng), mod2 = 1e9 + 9;

int hash1[N], hash2[N], inverse1[N], inverse2[N], power1[N], power2[N];

int add(int a, int b, int mod)
{
    if(a + b >= mod)
        return a + b - mod;
    return a + b;
}

int sub(int a, int b, int mod)
{
    if(a - b < 0)
        return a - b + mod;
    return a - b;
}

int mul(int a, int b, int mod)
{
    return (a * b) % mod;
}

int power(int a, int b, int mod)
{
    if (b <= 0)
        return 1;
    int ret = power((a % mod) * (a % mod) % mod, b / 2, mod);
    if (b % 2)
        ret = (ret % mod) * (a % mod) % mod;
    return ret;
}

void PreCalc()  // Don't forget to call it before all the test cases
{
    inverse1[0] = inverse2[0] =  power1[0] = power2[0] = 1;
    int power_inv1 = power(base1, mod1 - 2, mod1);
    int power_inv2 = power(base2, mod2 - 2, mod2);

    for (int i = 1; i < N; ++i) {
        inverse1[i] = mul(power_inv1, inverse1[i - 1], mod1);
        inverse2[i] = mul(power_inv2, inverse2[i - 1], mod2);

        power1[i] = mul(power1[i - 1], base1, mod1);
        power2[i] = mul(power2[i - 1], base2, mod2);
    }
}

void build_hash(string & s, int n)
{
    for (int i = 0; i < n; ++i) {

        hash1[i] = mul(s[i] - 'a' + 1, power1[i], mod1);
        hash2[i] = mul(s[i] - 'a' + 1, power2[i], mod2);

        if(i){
            hash1[i] = add(hash1[i], hash1[i - 1], mod1);
            hash2[i] = add(hash2[i], hash2[i - 1], mod2);
        }
    }
}


pair<int, int> get_hash(int l, int r)
{
    pair<int, int> ans;
    ans.first  = sub(hash1[r], (l ? hash1[l - 1] : 0), mod1);
    ans.first  = mul(ans.first, inverse1[l], mod1);
    ans.second = sub(hash2[r], (l ? hash2[l - 1] : 0), mod2);
    ans.second = mul(ans.second, inverse2[l], mod2);

    return ans;
}

pair<int, int> get_full_hash(string & s)
{
    int n = s.length();
    pair<int, int> ans = {0,0};

    for (int i = 0; i < n; ++i) {
        ans.first  = add(mul(s[i] - 'a' + 1, power1[i], mod1), ans.first, mod1);
        ans.second = add(mul(s[i] - 'a' + 1, power2[i], mod2), ans.second, mod2);
    }
    return ans;
}