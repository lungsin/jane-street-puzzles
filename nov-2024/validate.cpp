#include <bits/stdc++.h>

using namespace std;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); } // makes dist()=1
  P perp() const { return P(-y, x); }       // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

template <class P> pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

std::random_device rd;
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<double> dis(0.0, 1.0);

using Pt = Point<double>;

double genRandomDouble() { return static_cast<double>(gen()) / gen.max(); }
Pt generateRandomPt() { return Pt(genRandomDouble(), genRandomDouble()); }

Pt generateRandomRedPt() {
  while (true) {
    Pt pt = generateRandomPt();
    if (pt.x <= 0.5 && pt.y <= pt.x) {
      return pt;
    }
  }
}

bool simulate() {
  Pt const red = generateRandomRedPt();
  Pt const blue = generateRandomPt();

  Pt const mid = (red + blue) / 2.0;
  Pt const dir = (blue - red).perp();
  Pt const checkPt = mid + dir;

  auto [isIntersect, intersectPt] =
      lineInter(Pt(0.0, 0.0), Pt(1.0, 0.0), mid, checkPt);
  if (!isIntersect)
    return false;

  return 0.0 <= intersectPt.x && intersectPt.x <= 1.0;
}

int main() {
  constexpr int NUM_ITER = 1000'000'000;

  int num_ok = 0;
  for (int i = 0; i < NUM_ITER; i++) {
    num_ok += simulate();
  }
  cout << num_ok << endl;
  cout << (double)num_ok / NUM_ITER << endl;
  return 0;
}
