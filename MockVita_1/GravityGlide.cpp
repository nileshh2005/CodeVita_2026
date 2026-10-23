
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Slide {
    int x1, y1, x2, y2;
};

bool isOnSlide(int x, int y, const Slide& s) {
    if (x < min(s.x1, s.x2) || x > max(s.x1, s.x2) ||
        y < min(s.y1, s.y2) || y > max(s.y1, s.y2)) {
        return false;
    }

    long long cross =
        1LL * (s.x2 - s.x1) * (y - s.y1) -
        1LL * (s.y2 - s.y1) * (x - s.x1);

    return cross == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Slide> slides(n);

    for (int i = 0; i < n; i++) {
        cin >> slides[i].x1 >> slides[i].y1
            >> slides[i].x2 >> slides[i].y2;
    }

    int x, y;
    long long energy;
    cin >> x >> y >> energy;

    while (y > 0) {
        int active = -1;

        // Find a slide along which the ball can move downward.
        for (int i = 0; i < n; i++) {
            if (!isOnSlide(x, y, slides[i])) {
                continue;
            }

            int bx, by;

            if (slides[i].y1 < slides[i].y2) {
                bx = slides[i].x1;
                by = slides[i].y1;
            } else {
                bx = slides[i].x2;
                by = slides[i].y2;
            }

            // The ball cannot continue downward along this
            // slide when it is already at its lower endpoint.
            if (x != bx || y != by) {
                active = i;
                break;
            }
        }

        // No downward slide: gravity pulls the ball down.
        if (active == -1) {
            y--;
            continue;
        }

        Slide s = slides[active];

        int bx, by;
        if (s.y1 < s.y2) {
            bx = s.x1;
            by = s.y1;
        } else {
            bx = s.x2;
            by = s.y2;
        }

        int dx = (bx > x) ? 1 : (bx < x ? -1 : 0);
        int dy = (by > y) ? 1 : (by < y ? -1 : 0);

        // Check whether another slide ends at the current point.
        bool junction = false;

        for (int i = 0; i < n; i++) {
            if (i == active) continue;

            if ((slides[i].x1 == x && slides[i].y1 == y) ||
                (slides[i].x2 == x && slides[i].y2 == y)) {
                junction = true;
                break;
            }
        }

        // Unlock the junction if necessary.
        if (junction) {
            long long cost = 1LL * x * y;

            if (energy < cost) {
                break;
            }

            energy -= cost;
        }

        // Each unit step along the slide costs one energy.
        if (energy < 1) {
            break;
        }

        energy--;

        x += dx;
        y += dy;
    }

    cout << x << " " << y;

    return 0;
}
