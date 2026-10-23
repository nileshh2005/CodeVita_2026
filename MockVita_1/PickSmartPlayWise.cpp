#include <bits/stdc++.h>
using namespace std;

typedef double D;
struct P { D x, y; };
vector<P> pts;

int getId(P p) {
    for (size_t i = 0; i < pts.size(); i++)
        if (fabs(pts[i].x - p.x) < 1e-5 && fabs(pts[i].y - p.y) < 1e-5) return i;
    pts.push_back(p);
    return pts.size() - 1;
}

int main() {
    int n;
    cin >> n;
    vector<array<D,4>> s(n);
    D total = 0;
    for (auto &a : s) {
        cin >> a[0] >> a[1] >> a[2] >> a[3];
        total += hypot(a[2] - a[0], a[3] - a[1]);
    }

    vector<vector<pair<D,int>>> on(n);
    for (int i = 0; i < n; i++) {
        on[i].push_back({0.0, getId({s[i][0], s[i][1]})});
        on[i].push_back({1.0, getId({s[i][2], s[i][3]})});
    }
    const D eps = 1e-9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            D px = s[i][0], py = s[i][1], rx = s[i][2] - px, ry = s[i][3] - py;
            D qx = s[j][0], qy = s[j][1], sx = s[j][2] - qx, sy = s[j][3] - qy;
            D d = rx * sy - ry * sx;
            if (fabs(d) < 1e-12) continue;
            D t = ((qx - px) * sy - (qy - py) * sx) / d;
            D u = ((qx - px) * ry - (qy - py) * rx) / d;
            if (t < -eps || t > 1 + eps || u < -eps || u > 1 + eps) continue;
            int id = getId({px + t * rx, py + t * ry});
            on[i].push_back({t, id});
            on[j].push_back({u, id});
        }
    }

    set<pair<int,int>> edges;
    for (int i = 0; i < n; i++) {
        sort(on[i].begin(), on[i].end());
        for (size_t k = 1; k < on[i].size(); k++) {
            int a = on[i][k - 1].second, b = on[i][k].second;
            if (a == b) continue;
            edges.insert({min(a, b), max(a, b)});
        }
    }

    int V = pts.size();
    vector<set<int>> adj(V);
    for (auto &e : edges) {
        adj[e.first].insert(e.second);
        adj[e.second].insert(e.first);
    }

    // prune nodes with degree <= 1
    queue<int> q;
    for (int i = 0; i < V; i++) if (adj[i].size() <= 1) q.push(i);
    vector<bool> removed(V, false);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (removed[v]) continue;
        removed[v] = true;
        for (int w : adj[v]) {
            adj[w].erase(v);
            if (!removed[w] && adj[w].size() <= 1) q.push(w);
        }
        adj[v].clear();
    }

    int start = -1;
    for (int i = 0; i < V; i++) if (!removed[i] && !adj[i].empty()) { start = i; break; }
    if (start < 0) {
        cout << "Abandoned";
        return 0;
    }

    // walk the cycle
    vector<int> cyc;
    int prev = -1, cur = start;
    do {
        cyc.push_back(cur);
        int nxt = -1;
        for (int w : adj[cur]) if (w != prev) { nxt = w; break; }
        if (nxt == -1) nxt = *adj[cur].begin();
        prev = cur;
        cur = nxt;
    } while (cur != start && cyc.size() <= (size_t)V);

    D area2 = 0, perim = 0;
    int m = cyc.size();
    for (int i = 0; i < m; i++) {
        P a = pts[cyc[i]], b = pts[cyc[(i + 1) % m]];
        area2 += a.x * b.y - b.x * a.y;
        perim += hypot(b.x - a.x, b.y - a.y);
    }
    D kalyan = fabs(area2) / 2.0;
    D L = total - perim;
    D comp = L > 0 ? L * L / (4 * acos(-1.0)) : 0;

    cout << (kalyan > comp ? "Kalyan" : "Computer");
    return 0;
}