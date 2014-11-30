CC = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic -g -c -o $@
LDFLAGS = -std=c++11 -o $@ -lncurses

DEPENDENCIES = main.o Matrix.o HelperMatrix.o

main: ${DEPENDENCIES}
	${CC} ${LDFLAGS} ${DEPENDENCIES}

main.o : main.cpp Matrix.cpp HelperMatrix.cpp
	${CC} ${CPPFLAGS} main.cpp

Matrix.o : Matrix.cpp Matrix.hpp
	${CC} ${CPPFLAGS} Matrix.cpp

HelperMatrix.o : HelperMatrix.cpp HelperMatrix.hpp
	${CC} ${CPPFLAGS} HelperMatrix.cpp

clean:
	-rm main ${DEPENDENCIES}
