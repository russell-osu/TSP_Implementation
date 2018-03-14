
CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = tspDriver.o
OBJS += utilities.o
OBJS += twoOpt.o
OBJS += threeOpt.o
OBJS += christofides.o
OBJS += dynArray.o
OBJS += linkedList.o
OBJS += mergeSort.o

SRCS = tspDriver.cpp
SRCS += utilities.cpp
SRCS += twoOpt.cpp
SRCS += threeOpt.cpp
SRCS += christofides.cpp
SRCS += dynArray.cpp
SRCS += linkedList.cpp
SRCS += mergeSort.cpp

HEADERS = utilities.hpp
HEADERS += twoOpt.hpp
HEADERS += threeOpt.hpp
HEADERS += christofides.hpp
HEADERS += dynArray.hpp
HEADERS += linkedList.hpp
HEADERS += mergeSort.hpp

tsp: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o tsp

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm -f tsp *.o *.tour *.xy
