#ifndef TSP_ParseR_CPP
#define TSP_ParseR_CPP

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <limits> 

using namespace std;

class TSPParser {
private:
    string filename;
    vector<pair<double, double>> coordinates;

public:
    explicit TSPParser(string s) : filename(std::move(s)) {}

    void Parse() {
        ifstream file(filename);
        if (!file) {
            cerr << "Cannot open file: " << filename << endl;
            return;
        }

        int verticesCount;
        file >> verticesCount;
        
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        coordinates.reserve(verticesCount);

        double x, y;
        for (int i = 0; i < verticesCount; ++i) {
            if (file >> x >> y) {
                coordinates.emplace_back(x, y);
            } else {
                // Ошибка чтения данных, выходим из цикла
                break;
            }
        }
    }

    const vector<pair<double, double>>& getCoordinates() const {
        return coordinates;
    }
};

#endif // TSP_ParseR_CPP
