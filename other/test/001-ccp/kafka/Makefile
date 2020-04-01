#****************************************************************************
# Makefile
#****************************************************************************

CXX	:= g++
CXXFLAGS:= -Wall -c -fPIC -Wno-deprecated -g -std=c++11

BIN_SOURCES = $(shell ls *.cpp)
BIN_OBJECTS = $(BIN_SOURCES:.cpp=.o)
BIN_CCFLAGS:= -Wall -fPIC -Wno-deprecated -g -std=c++11

BIN		 := test

.PHONY: test
test:$(BIN_OBJECTS)
	$(CXX) $(INC_LIBS) -o $@ $(BIN_OBJECTS) $(BIN_CCFLAGS) -lpthread -lrdkafka++

.PHONY: clean
clean:
	rm -f *.o $(BIN)
