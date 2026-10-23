#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> X(n), Y(n);
    for (int i = 0; i < n; i++) {
        cin >> X[i] >> Y[i];
        X[i] *= 10;
        Y[i] *= 10;
    }

    // Shortest original edge (scaled by 10) decides the largest allowed H
    long long minL = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        long long len = llabs(X[j] - X[i]) + llabs(Y[j] - Y[i]);
        if (len > 0) minL = min(minL, len);
    }
    long long kmax = (minL - 1) / 2;   // need minL - 2k >= 1 (0.1 unit)

    // Remove collinear / duplicate vertices
    bool changed = true;
    while (changed) {
        changed = false;
        int m = X.size();
        for (int i = 0; i < m; i++) {
            int p = (i + m - 1) % m, q = (i + 1) % m;
            long long cr = (X[i] - X[p]) * (Y[q] - Y[i]) - (Y[i] - Y[p]) * (X[q] - X[i]);
            if (cr == 0) {
                X.erase(X.begin() + i);
                Y.erase(Y.begin() + i);
                changed = true;
                break;
            }
        }
    }
    n = X.size();

    // Make the polygon counter-clockwise
    long long a2 = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        a2 += X[i] * Y[j] - X[j] * Y[i];
    }
    if (a2 < 0) {
        reverse(X.begin(), X.end());
        reverse(Y.begin(), Y.end());
    }

    vector<int> dx(n), dy(n);
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        long long ex = X[j] - X[i], ey = Y[j] - Y[i];
        dx[i] = (ex > 0) - (ex < 0);
        dy[i] = (ey > 0) - (ey < 0);
    }

    double best = 0;
    for (long long k = 1; k <= kmax; k++) {
        vector<long long> nx(n), ny(n);
        for (int i = 0; i < n; i++) {
            int p = (i + n - 1) % n;
            if (dx[p] == 0) {
                nx[i] = X[i] + (long long)(-dy[p]) * k;
                ny[i] = Y[i] + (long long)(dx[i]) * k;
            } else {
                ny[i] = Y[i] + (long long)(dx[p]) * k;
                nx[i] = X[i] + (long long)(-dy[i]) * k;
            }
        }
        long long s = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            s += nx[i] * ny[j] - nx[j] * ny[i];
        }
        double area = fabs((double)s) / 2.0 / 100.0;   // real units
        best = max(best, area * (k / 10.0));
    }

    printf("%.2f", best + 1e-9);
    return 0;
}