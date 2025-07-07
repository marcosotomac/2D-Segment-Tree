#include <iostream>
#include <vector>
using namespace std;

class SegmentTree2D {
private:
    int n, m;
    vector<vector<int>> matrix;
    vector<vector<int>> tree;

    void buildY(const int nodeX, const int lx, const int rx, const int nodeY, const int ly, const int ry) {
        if (ly == ry) {
            if (lx == rx) {
                tree[nodeX][nodeY] = matrix[lx][ly];
            } else {
                tree[nodeX][nodeY] = tree[2*nodeX][nodeY] + tree[2*nodeX+1][nodeY];
            }
        } else {
            const int my = (ly + ry) / 2;
            buildY(nodeX, lx, rx, 2*nodeY, ly, my);
            buildY(nodeX, lx, rx, 2*nodeY+1, my+1, ry);
            tree[nodeX][nodeY] = tree[nodeX][2*nodeY] + tree[nodeX][2*nodeY+1];
        }
    }

    void buildX(const int nodeX, const int lx, const int rx) {
        if (lx != rx) {
            const int mx = (lx + rx) / 2;
            buildX(2*nodeX, lx, mx);
            buildX(2*nodeX+1, mx+1, rx);
        }
        buildY(nodeX, lx, rx, 1, 0, m-1);
    }

    int queryY(const int nodeX, const int nodeY, const int ly, const int ry, const int y1, const int y2) {
        if (y2 < ly || ry < y1) return 0;
        if (y1 <= ly && ry <= y2) return tree[nodeX][nodeY];
        const int my = (ly + ry) / 2;
        return queryY(nodeX, 2*nodeY, ly, my, y1, y2) +
               queryY(nodeX, 2*nodeY+1, my+1, ry, y1, y2);
    }

    int queryX(const int nodeX, const int lx, const int rx, const int x1, const int x2, const int y1, const int y2) {
        if (x2 < lx || rx < x1) return 0;
        if (x1 <= lx && rx <= x2) return queryY(nodeX, 1, 0, m-1, y1, y2);
        const int mx = (lx + rx) / 2;
        return queryX(2*nodeX, lx, mx, x1, x2, y1, y2) +
               queryX(2*nodeX+1, mx+1, rx, x1, x2, y1, y2);
    }

    void updateY(const int nodeX, const int lx, const int rx, const int nodeY, const int ly, const int ry, const int x, const int y, const int val) {
        if (ly == ry) {
            if (lx == rx) {
                tree[nodeX][nodeY] = val;
            } else {
                tree[nodeX][nodeY] = tree[2*nodeX][nodeY] + tree[2*nodeX+1][nodeY];
            }
        } else {
            if (const int my = (ly + ry) / 2; y <= my) updateY(nodeX, lx, rx, 2*nodeY, ly, my, x, y, val);
            else updateY(nodeX, lx, rx, 2*nodeY+1, my+1, ry, x, y, val);
            tree[nodeX][nodeY] = tree[nodeX][2*nodeY] + tree[nodeX][2*nodeY+1];
        }
    }

    void updateX(const int nodeX, const int lx, const int rx, const int x, const int y, const int val) {
        if (lx != rx) {
            if (const int mx = (lx + rx) / 2; x <= mx) updateX(2*nodeX, lx, mx, x, y, val);
            else updateX(2*nodeX+1, mx+1, rx, x, y, val);
        }
        updateY(nodeX, lx, rx, 1, 0, m-1, x, y, val);
    }

public:
    explicit SegmentTree2D(const vector<vector<int>>& input) {
        matrix = input;
        n = input.size();
        m = input[0].size();
        tree.assign(4*n, vector<int>(4*m, 0));
        buildX(1, 0, n-1);
    }

    int query(const int x1, const int y1, const int x2, const int y2) {
        return queryX(1, 0, n-1, x1, x2, y1, y2);
    }

    void update(const int x, const int y, const int val) {
        matrix[x][y] = val;
        updateX(1, 0, n-1, x, y, val);
    }
};

int main() {
    const vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    SegmentTree2D st(mat);

    cout << "Suma (0,0)-(1,1): " << st.query(0, 0, 1, 1) << endl; // 1+2+4+5 = 12
    st.update(1, 1, 10); // mat[1][1] = 10
    cout << "Suma (0,0)-(1,1) tras update: " << st.query(0, 0, 1, 1) << endl; // 1+2+4+10 = 17

    return 0;
}