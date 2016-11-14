CXX = g++
CXXFLAGS = -Wall -MMD
SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)
OBJ = $(SRC:src/%.cpp=obj/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ)
	$(CXX) $^ -o bin/sil

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(DEP)

clean:
	rm obj/*

re: clean all


