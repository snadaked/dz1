CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = TSPSolver
SRC = main.cpp TSPParser.cpp TSPSolver.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
