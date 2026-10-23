#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<char>> Grid;

// Stones fall toward the bottom of each column
void applyGravity(Grid &g) {
    int m = g.size(), n = g[0].size();
    for (int j = 0; j < n; j++) {
        int pos = m - 1;                 // next free cell from the bottom
        for (int i = m - 1; i >= 0; i--) {
            if (g[i][j] == '*') {
                g[i][j] = '.';
                g[pos][j] = '*';
                pos--;
            }
        }
    }
}

// Rotate 90 degrees clockwise: new[i][j] = old[m-1-j][i]
Grid rotateRight(const Grid &g) {
    int m = g.size(), n = g[0].size();
    Grid r(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            r[i][j] = g[m - 1 - j][i];
    return r;
}

// Rotate 90 degrees counter-clockwise: new[i][j] = old[j][n-1-i]
Grid rotateLeft(const Grid &g) {
    int m = g.size(), n = g[0].size();
    Grid r(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            r[i][j] = g[j][n - 1 - i];
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    Grid g(m, vector<char>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    applyGravity(g);                     // gravity at the initial stage

    int k;
    cin >> k;
    while (k--) {
        string s;
        cin >> s;
        if (s == "right") g = rotateRight(g);
        else              g = rotateLeft(g);
        applyGravity(g);                 // gravity after each rotation
    }

    // Single spaces between characters, newline between rows,
    // no trailing newline after the last row
    for (size_t i = 0; i < g.size(); i++) {
        for (size_t j = 0; j < g[i].size(); j++) {
            if (j) cout << ' ';
            cout << g[i][j];
        }
        if (i + 1 < g.size()) cout << '\n';
    }
    return 0;
}