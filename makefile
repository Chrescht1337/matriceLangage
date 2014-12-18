SRC         :=  $(wildcard *.cpp)
OBJ         :=  $(SRC:.cpp=.o)
DEP         :=  $(OBJ:.o=.d)
CPPFLAGS    :=  -MMD -MP
CXXFLAGS    :=  -std=c++11 -ggdb3 -Wpedantic

main: $(OBJ)
	$(CXX) $^ -o $@

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP)
