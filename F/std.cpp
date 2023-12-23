#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const double eps = 1e-8;
inline bool equals(double a, double b) {
    return fabs(a - b) < eps;
}

class Point {
    public:
    double x, y;
    Point () {}
    Point(double x, double y): x(x), y(y) {}
    Point operator+(Point& b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(Point& b) {
        return Point(x - b.x, y - b.y);
    }
    Point operator*(double k) {
        return Point(x * k, y * k);
    }
    Point operator/(double k) {
        return Point(x / k, y / k);
    }
    bool operator==(const Point& b) {
        return equals(this->x, b.x) && equals(this->y, b.y);
    }
};
typedef Point Vector;

class Line {
    public:
    Point p1, p2;
    Line() {}
    Line(Point p1, Point p2) : p1(p1), p2(p2){}
};
typedef Line Segment;

double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}
double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}
double norm(Vector v) {
    return pow(v.x, 2) + pow(v.y, 2);
}
double absV(Vector v) {
    return sqrt(norm(v));
}
Point project(Point p, Line l) {
    Vector base = l.p2 - l.p1;
    double r = dot(p - l.p1, base) / norm(base);
    base = base * r;
    return Point(l.p1 + base);
}
bool pointOnLine(Point p, Line l) {
    return project(p, l) == p;
}
const int CC = 1;
const int C = -1;
const int OB = 2;
const int OF = -2;
const int OS = 0;
int ccw(Vector a, Vector b) {
    if (cross(a, b) > eps) return CC;
    if (cross(a, b) < -eps) return C;
    if (dot(a, b) < -eps) return OB;
    if (norm(a) < norm(b)) return OF;
    return OS;
}
int ccw(Point p1, Point p2, Point p3) {
    Vector a = p2 - p1;
    Vector b = p3 - p1;
    return ccw(a, b);
}
bool intersect_ss(Point a, Point b, Point c, Point d) {
    return ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0;
}
bool intersect_ss(Segment a, Segment b) {
    return intersect_ss(a.p1, a.p2, b.p1, b.p2);
}
double get_dis(Point a, Point b) {
    return absV(a - b);
}
Point getCrossPoint_Line(Line s1, Line s2) {
    Vector v1, v2;
    v1 = s1.p2 - s1.p1, v2 = s2.p2 - s2.p1;
    Vector u = s1.p1 - s2.p1;
    double t = cross(v2, u) / cross(v1, v2);
    Point x = v1 * t;
    return s1.p1 + x;
}
Point getCrossPoint(Segment s1, Segment s2, bool flag = 0) {
    if (!intersect_ss(s1, s2)) {
        if (flag) return getCrossPoint_Line(s1, s2);
        else return Point(1e18, 1e18);
    }
    Vector base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1));
    double d2 = abs(cross(base, s1.p2 - s2.p1));
    double t = d1 / (d1 + d2);
    Point x = (s1.p2 - s1.p1) * t;
    return s1.p1 + x;
}

const int MAXN = 103;
const int MAXK = 1e7 + 3;

int n;
Point a, b;
Segment s[MAXN];
int cri[MAXN][MAXN], tot = 1;
Point crp[MAXK];

int first[MAXK], nt[MAXK], v[MAXK];
double w[MAXK];

int te;
void addEdge(int x, int y, double fe) {
    nt[++te] = first[x];
    first[x] = te;
    v[te] = y;
    w[te] = fe;
}

double dis[MAXK];
bool vis[MAXK];
struct HeapNode{
    int p;
    double d;
    friend bool operator < (HeapNode x, HeapNode y) {
        return x.d > y.d;
    }
};

void Dijkstra(int s) {
	for (int i = 0; i <= tot; i++) dis[i] = 1e18;
	dis[s] = 0;
	priority_queue <HeapNode> q;
	q.push((HeapNode) {s, 0});
	while (!q.empty()) {
		const int x = q.top().p;
        // cout << x << endl;
		q.pop();
		if (vis[x]) continue;
		vis[x] = true;
		for (int eo = first[x]; eo != 0; eo = nt[eo]) {
			const int ep = v[eo];
			if (dis[ep] > dis[x] + w[eo]) {
				dis[ep] = dis[x] + w[eo];
				q.push((HeapNode){ep, dis[ep]});
			}
		}
	}
}

int main() {
    cin >> n;
    cin >> a.x >> a.y >> b.x >> b.y;
    for (int i = 1; i <= n; i++) {
        cin >> s[i].p1.x >> s[i].p1.y >> s[i].p2.x >> s[i].p2.y;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            if (intersect_ss(s[i], s[j])) {
                if (cri[i][j] != 0) continue;
                Point cr = getCrossPoint(s[i], s[j]);
                cri[i][j] = cri[j][i] = ++tot;
                crp[tot] = cr;
            }
        }
        bool onI1 = pointOnLine(a, s[i]), onI2 = pointOnLine(b, s[i]);
        if (onI1 && onI2) {
            addEdge(0, 1, get_dis(a, b));
            addEdge(1, 0, get_dis(a, b));
        }
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            if (cri[i][j] == 0) continue;
            if (onI1) {
                addEdge(0, cri[i][j], get_dis(a, crp[cri[i][j]]));
                addEdge(cri[i][j], 0, get_dis(a, crp[cri[i][j]]));
            }
            if (onI2) {
                addEdge(1, cri[i][j], get_dis(b, crp[cri[i][j]]));
                addEdge(cri[i][j], 1, get_dis(b, crp[cri[i][j]]));
            }
            for (int k = j + 1; k <= n; k++) {
                if (cri[i][k] == 0) continue;
                addEdge(cri[i][j], cri[i][k], get_dis(crp[cri[i][j]], crp[cri[i][k]]));
                addEdge(cri[i][k], cri[i][j], get_dis(crp[cri[i][j]], crp[cri[i][k]]));
            }
        }
    }
    Dijkstra(0);
    cout << fixed << setprecision(10) << dis[1] << '\n';
    return 0;
}
