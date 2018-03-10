#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <iomanip>

struct point {
    double x;
    double y;
    double w;

    point (double x, double y, double w): x(x), y(y), w(w) {
    }
};

double computeWeightTotals(double x,
                          double y,
                          std::vector<point> const &points) {
    double total = 0;
    for (auto const &p : points) {
        total += std::max(std::abs(x - p.x), std::abs(y - p.y)) * p.w;
    }

    return total;
}

struct direction {
    double weight;
    double x_move;
    double y_move;

    direction(double x, double y, double w) :
        weight(w),
        x_move(x),
        y_move(y)
    {
    }
};

direction computeDirection(double x,
                           double y,
                           double x_move,
                           double y_move,
                           std::vector<point> const &points) {
    return direction(x_move,
                     y_move,
                     computeWeightTotals(x + x_move,
                                         y + y_move,
                                         points));
}

int main() {
    int cases = 0;
    std::cin >> cases;

    int caseNo = 1;

    while (caseNo <= cases) {
        int n_points = 0;
        std::cin >> n_points;
        std::vector<point> points;
        points.reserve(n_points);

        while (n_points--) {
            double x, y, w;
            std::cin >> x >> y >> w;
            points.push_back(point(x, y, w));
        }

        double bestSum = std::numeric_limits<double>::max();

        /* Greedy approach - we start at 0, 0 and check all the points
         * around us. Pick the pair that is closer to the best sum
         * and move by stepFactor (which decrements by half each time)
         */
        double stepFactor = 1000.0f;
        double x = 0.0f;
        double y = 0.0f;
        double lastSum = std::numeric_limits<int>::max();

        while (stepFactor >= 0.000000000001f) {
            std::array<direction, 8> sums = {{
                computeDirection(x, y, -stepFactor, -stepFactor, points),
                computeDirection(x, y, stepFactor, -stepFactor, points),
                computeDirection(x, y, -stepFactor, stepFactor, points),
                computeDirection(x, y, stepFactor, stepFactor, points),
                computeDirection(x, y, 0, -stepFactor, points),
                computeDirection(x, y, 0, stepFactor, points),
                computeDirection(x, y, stepFactor, 0, points),
                computeDirection(x, y, -stepFactor, 0, points)
            }};
            std::sort(sums.begin(), sums.end(), [](direction const &a, direction const &b) {
                return a.weight < b.weight;
            });

            direction const &dir = sums[0];
            /*std::cout << "Move in "
                      << dir.x_move
                      << " "
                      << dir.y_move
                      << " from "
                      << x
                      << " "
                      << y
                      <<
                      " weight "
                      << dir.weight
                      << std::endl; */
            x += dir.x_move;
            y += dir.y_move;
            stepFactor = stepFactor / 1.1f;
            lastSum = dir.weight;
        }

        std::cout << std::fixed << "Case #" << caseNo << ": " << lastSum << std::endl;
        caseNo++;
    }
}