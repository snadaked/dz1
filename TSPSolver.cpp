#ifndef TSP_SOLVER_H 
#define TSP_SOLVER_H

#include "TSPParser.cpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

class TSPSolver {
private:
    vector<pair<double, double>> coordinates;
    vector<vector<double>> distances; 
    vector<int> bestPath;
    double bestDistance = numeric_limits<double>::max();

    void calculateAllDistances() {
        distances.resize(coordinates.size(), vector<double>(coordinates.size(), 0.0));
        for (size_t i = 0; i < coordinates.size(); ++i) {
            for (size_t j = 0; j < coordinates.size(); ++j) {
                if (i != j) {
                    distances[i][j] = sqrt(pow(coordinates[i].first - coordinates[j].first, 2) +
                                           pow(coordinates[i].second - coordinates[j].second, 2));
                }
            }
        }
    }

    double pathDistance(const vector<int>& path) {
        double distance = 0.0;
        if (path.empty()) {
            cerr << "Ошибка: вектор пути пуст." << endl;
            return 0;
        }

        for (size_t i = 0; i < path.size() - 1; ++i) {
            if (static_cast<size_t>(path[i]) < coordinates.size() && static_cast<size_t>(path[i + 1]) < coordinates.size()) {
                distance += distances[path[i]][path[i + 1]]; 
            } else {
                cerr << "Ошибка: индекс вне диапазона вектора координат." << endl;
                return 0;
            }
        }

        if (!path.empty() && static_cast<size_t>(path.back()) < coordinates.size() && !coordinates.empty()) {
            distance += distances[path.back()][path[0]]; 
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
                double delta = -distances[bestPath[i - 1]][bestPath[i]]
                               -distances[bestPath[k]][bestPath[(k + 1) % bestPath.size()]]
                               +distances[bestPath[i - 1]][bestPath[k]]
                               +distances[bestPath[i]][bestPath[(k + 1) % bestPath.size()]];
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
    explicit TSPSolver(const vector<pair<double, double>>& coords) : coordinates(coords) {
        calculateAllDistances(); 
    }

    void solve() {
        bestPath.resize(coordinates.size());
        iota(bestPath.begin(), bestPath.end(), 0);
        bestDistance = pathDistance(bestPath);

        while (twoOpt());

        cout << "Best distance found: " << bestDistance << endl;
        cout << "Best path: ";
        for (int i : bestPath) {
            cout << i << " ";
        }
        cout << endl;
    }
};

#endif // TSP_SOLVER_H
