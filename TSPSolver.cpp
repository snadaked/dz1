#ifndef TSP_SOLVER_CPP
#define TSP_SOLVER_CPP

#include "TSPParser.cpp"
#include <cmath>
#include <numeric> // Для std::iota
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

class TSPSolver {
private:
    vector<pair<double, double>> coordinates;
    vector<int> bestPath;
    double bestDistance = numeric_limits<double>::max();

    double calculateDistance(const pair<double, double>& a, const pair<double, double>& b) {
        return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    }

    double pathDistance(const vector<int>& path) {
        
        double distance = 0.0;
        if(path.empty()) {
            cerr << "Ошибка: вектор пути пуст." << endl;
            return 0;
        }

        for (size_t i = 0; i < path.size() - 1; ++i) {
        // Проверяем, что path[i] и path[i + 1] существуют в векторе coordinates
            if (static_cast<size_t>(path[i]) < coordinates.size() && static_cast<size_t>(path[i + 1]) < coordinates.size()) {
                distance += calculateDistance(coordinates[path[i]], coordinates[path[i + 1]]);
            } else {
                cerr << "Ошибка: индекс вне диапазона вектора координат." << endl;
            // Обработка ошибки или прерывание функции
                return 0; // или другое подходящее действие
            }
    }
    // Для замыкания пути от последней точки к первой
    if (!path.empty() && static_cast<size_t>(path.back()) < coordinates.size() && !coordinates.empty()) {
        distance += calculateDistance(coordinates[path.back()], coordinates[path[0]]);
    } else {
        cerr << "Ошибка: невозможно замкнуть путь из-за отсутствующих индексов." << endl;
    }
    return distance;
}


    void twoOptSwap(int i, int k) {
        reverse(bestPath.begin() + i, bestPath.begin() + k + 1);
    }

    bool twoOpt() {
        bool improved = false;
        for (size_t i = 1; i < bestPath.size() - 1; ++i) {
            for (size_t k = i + 1; k < bestPath.size(); ++k) {
                double delta = -calculateDistance(coordinates[bestPath[i - 1]], coordinates[bestPath[i]])
                               -calculateDistance(coordinates[bestPath[k]], coordinates[bestPath[(k + 1) % bestPath.size()]])
                               +calculateDistance(coordinates[bestPath[i - 1]], coordinates[bestPath[k]])
                               +calculateDistance(coordinates[bestPath[i]], coordinates[bestPath[(k + 1) % bestPath.size()]]);
                if (delta < 0) {
                    twoOptSwap(i, k);
                    bestDistance += delta;
                    improved = true;
                }
            }
        }
        return improved;
    }

public:
    explicit TSPSolver(const vector<pair<double, double>>& coords) : coordinates(coords) {}

    void solve() {
        // Initialize bestPath with a sequential path
        bestPath.resize(coordinates.size());
        iota(bestPath.begin(), bestPath.end(), 0);
        bestDistance = pathDistance(bestPath);

        // Keep trying to improve the path with 2-opt swaps
        while (twoOpt());

        cout << "Best distance found: " << bestDistance << endl;
        cout << "Best path: ";
        for (int i : bestPath) {
            cout << i << " ";
        }
        cout << endl;
    }
};

#endif // TSP_SOLVER_CPP
