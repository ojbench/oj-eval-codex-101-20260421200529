#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c, d, e, f; // input order: a b c d e f
    if (!(cin >> a >> b >> c >> d >> e >> f)) return 0;

    // Total seconds in a day
    long long ab = a * b;
    long long day = ab * c;

    // current time in seconds since 0:0:0
    long long t0 = ab * f + a * e + d;

    // We want the minimal t >= t0 + 1 such that hour==minute==second
    long long m = min(a, min(b, c));
    long long best_t = LLONG_MAX;

    for (long long x = 0; x < m; ++x) {
        // delta = floor( x*(1+a) / (a*b) )
        long long numerator = x * (1 + a);
        long long delta = numerator / ab; // floor division

        // n0 satisfies: (n0 + delta) % c == x -> n0 % c == (x - delta) mod c
        long long rhs = (x - delta) % c;
        if (rhs < 0) rhs += c;
        long long n0 = rhs; // minimal non-negative representative

        // base time for this x
        long long t_base = ab * n0 + x * (1 + a);

        // Find the earliest t >= t0 + 1 in the progression t_base + k * (ab*c)
        if (t_base < t0 + 1) {
            long long step = day; // ab*c
            long long need = (t0 + 1) - t_base;
            long long k = (need + step - 1) / step; // ceil
            t_base += k * step;
        }

        if (t_base < best_t) best_t = t_base;
    }

    long long s = best_t - t0; // guaranteed > 0
    cout << s << '\n';
    return 0;
}

