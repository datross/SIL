CXX = g++
CXXFLAGS = -Wall -MMD -std=c++11 -fdiagnostics-color -Ithird_parties/
SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)
OBJ = $(SRC:src/%.cpp=obj/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ)
	@mkdir -p bin
	$(CXX) $^ -o bin/sil

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(DEP)

clean:
	rm obj/*

re: clean all


