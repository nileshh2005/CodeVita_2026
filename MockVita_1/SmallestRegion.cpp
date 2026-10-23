#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<array<int,4>> r(n);
    for (auto &a : r) cin >> a[0] >> a[1] >> a[2] >> a[3];
    int px1, py1, px2, py2;
    cin >> px1 >> py1 >> px2 >> py2;

    // Vertical fold positions
    vector<int> xs = {px1};
    for (int x = px1 + 1; x < px2; x++) {
        bool ok = true;
        for (auto &a : r)
            if (a[0] < x && x < a[2]) { ok = false; break; }
        if (ok) xs.push_back(x);
    }
    xs.push_back(px2);

    // Horizontal fold positions
    vector<int> ys = {py1};
    for (int y = py1 + 1; y < py2; y++) {
        bool ok = true;
        for (auto &a : r)
            if (a[1] < y && y < a[3]) { ok = false; break; }
        if (ok) ys.push_back(y);
    }
    ys.push_back(py2);

    int minW = INT_MAX, minH = INT_MAX;
    for (size_t i = 1; i < xs.size(); i++) minW = min(minW, xs[i] - xs[i-1]);
    for (size_t i = 1; i < ys.size(); i++) minH = min(minH, ys[i] - ys[i-1]);

    cout << (long long)minW * minH;
    return 0;
}