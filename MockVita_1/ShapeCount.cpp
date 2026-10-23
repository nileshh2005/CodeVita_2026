#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Interval = pair<int, int>;

static void mergeVec(vector<Interval>& a) {
    sort(a.begin(), a.end());
    vector<Interval> merged;
    for (auto [l, r] : a) {
        if (merged.empty() || l > merged.back().second)
            merged.push_back({l, r});
        else
            merged.back().second = max(merged.back().second, r);
    }
    a.swap(merged);
}

// returns index of the merged interval containing [l, r], or -1
static int findCover(const vector<Interval>& iv, int l, int r) {
    auto it = upper_bound(iv.begin(), iv.end(), make_pair(l, INT_MAX));
    if (it == iv.begin()) return -1;
    --it;
    if (it->first <= l && it->second >= r) return int(it - iv.begin());
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<int, vector<Interval>> Hm, Vm;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 == y2 && x1 != x2)
            Hm[y1].push_back({min(x1, x2), max(x1, x2)});
        else if (x1 == x2 && y1 != y2)
            Vm[x1].push_back({min(y1, y2), max(y1, y2)});
    }

    vector<int> ys, xs;
    vector<vector<Interval>> H, V;
    vector<ll> base;           // global id offset for each horizontal line
    ll total = 0;

    for (auto& [y, a] : Hm) {
        mergeVec(a);
        ys.push_back(y);
        base.push_back(total);
        total += a.size();
        H.push_back(a);
    }
    for (auto& [x, a] : Vm) {
        mergeVec(a);
        xs.push_back(x);
        V.push_back(a);
    }

    int h = ys.size(), v = xs.size();
    vector<ll> keys;
    vector<ll> pts; // horizontal-interval ids of points on current vertical interval

    for (int k = 0; k < v; ++k) {
        int x = xs[k];
        for (auto [lo, hi] : V[k]) {
            pts.clear();
            int s = lower_bound(ys.begin(), ys.end(), lo) - ys.begin();
            for (int i = s; i < h && ys[i] <= hi; ++i) {
                int id = findCover(H[i], x, x);
                if (id >= 0) pts.push_back(base[i] + id);
            }
            int m = pts.size();
            for (int a = 0; a < m; ++a)
                for (int b = a + 1; b < m; ++b)
                    keys.push_back(pts[a] * total + pts[b]);
        }
    }

    sort(keys.begin(), keys.end());

    ll ans = 0;
    for (size_t i = 0; i < keys.size();) {
        size_t j = i;
        while (j < keys.size() && keys[j] == keys[i]) ++j;
        ll c = j - i;
        ans += c * (c - 1) / 2;
        i = j;
    }

    cout << ans;
    return 0;
}