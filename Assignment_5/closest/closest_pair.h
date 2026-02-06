#include <vector>
#include <math.h>
#include <algorithm>
struct Point {
    int id;
    double x, y;
};
double dist(const Point& p1, const Point& p2) {
    auto dx = p1.x - p2.x;
    auto dy = p1.y - p2.y;
    return std::sqrt(dx*dx + dy*dy);
}
// --- Your code here
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}
// ---

std::pair<Point, Point> findInStrip(std::vector<Point> strip, double d){
    double minDist = d;
    std::pair<Point, Point> closestPair = {strip[0], strip[1]};

    int n = strip.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n && (strip[j].y - strip[i].y) < minDist; ++j) {
            double currentDist = dist(strip[i], strip[j]);
            if (currentDist < minDist) {
                minDist = currentDist;
                closestPair = {strip[i], strip[j]};
            }
        }
    }
    return closestPair;
}

std::pair<Point, Point> Recursion(std::vector<Point>& pointsX, std::vector<Point>& pointsY, int l, int r){
    if (r-l <= 3) {
        double minDist = std::numeric_limits<double>::max();
        std::pair<Point, Point> closestPair;
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                double currentDist = dist(pointsX[i], pointsX[j]);
                if (currentDist < minDist) {
                    minDist = currentDist;
                    closestPair = {pointsX[i], pointsX[j]};
                }
            }
        }
        return closestPair;
    }

    int m = (l+r)/2;
    Point midPoint = pointsX[m];
    std::vector<Point> pointsYLeft, pointsYRight;
    for (const auto& p : pointsY) {
        if (p.x <= midPoint.x) {
            pointsYLeft.push_back(p);
        } else {
            pointsYRight.push_back(p);
        }
    }
    auto leftClosest = Recursion(pointsX, pointsYLeft, l, m);
    auto rightClosest = Recursion(pointsX, pointsYRight, m+ 1, r);
    double dLeft = dist(leftClosest.first, leftClosest.second);
    double dRight = dist(rightClosest.first, rightClosest.second);
    double d = std::min(dLeft, dRight);
    std::pair<Point, Point> minPair = (dLeft<dRight) ? leftClosest : rightClosest;

    std::vector<Point> strip;
    for (const auto& p : pointsY) {
        if (std::abs(p.x - midPoint.x) < d) {
            strip.push_back(p);
        }
    }
    if (strip.size() > 1) {
        auto stripClosestPair = findInStrip(strip, d);
        double stripDist = dist(stripClosestPair.first, stripClosestPair.second);
        if (stripDist < d) {
            return stripClosestPair;
        }
    }
    
    return minPair;
}


std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
    // --- Your code here
    std::vector<Point> pointsX = points;
    std::sort(pointsX.begin(), pointsX.end(), compareX);
    std::vector<Point> pointsY = points;
    std::sort(pointsY.begin(),pointsY.end(), compareY);
    auto result =Recursion(pointsX, pointsY, 0, points.size() - 1);
    if (result.first.id > result.second.id) {
        return {result.second, result.first};
    }
    return result;
    // ---
}