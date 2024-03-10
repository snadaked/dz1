#include "TSPParser.cpp"
#include "TSPSolver.cpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    // Проверяем, переданы ли аргументы командной строки
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_test_file1> <path_to_test_file2> ..." << std::endl;
        return 1;
    }

    // Перебираем все предоставленные пути к файлам
    for (int i = 1; i < argc; ++i) {
        std::string filename = argv[i];

        std::cout << "Processing file: " << filename << std::endl;

        // Создание объекта парсера и чтение данных
        TSPParser parser(filename);
        parser.Parse();

        // Получение координат вершин графа
        auto coordinates = parser.getCoordinates();

        // Создание объекта солвера и решение задачи коммивояжера
        TSPSolver solver(coordinates);
        solver.solve();
    }

    return 0;
}
