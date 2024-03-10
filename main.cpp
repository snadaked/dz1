#include "TSPParser.cpp"
#include "TSPSolver.cpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_test_file1> <path_to_test_file2> ..." << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        std::string filename = argv[i];

        std::cout << "Processing file: " << filename << std::endl;

        TSPParser parser(filename);
        parser.Parse();


        auto coordinates = parser.getCoordinates();

        TSPSolver solver(coordinates);
        solver.solve();
    }

    return 0;
}
