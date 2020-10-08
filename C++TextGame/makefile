#Project 5 makefile - Russell Eck

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
#CXXFLAGS += -g
LDFLAG = -lboost_date_time

OBJS = main.o space.o onett.o twoson.o winters.o dalaam.o saturn.o giygas.o character.o menuClass.o

SRCS = main.cpp space.cpp onett.cpp twoson.cpp winters.cpp dalaam.cpp saturn.cpp giygas.cpp character.cpp menuClass.cpp

HEADERS = space.hpp onett.hpp twoson.hpp winters.hpp dalaam.hpp saturn.hpp giygas.hpp character.hpp menuClass.hpp

langtonsAnt: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o Earthbound

create.o: ${SRCS}
	${CXX} ${CXXFLAGS} -c ${@:.o=.cpp}

clean:
	rm *.o Earthbound
