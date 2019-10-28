#****************************************************************************
#
# Makefile for lib
# Henry
# 2019-08-29
#
#****************************************************************************

CXX	:= g++

INC_HEAD:= 
INC_LIBS:= 
CXXFLAGS:= -Wall -c -fPIC -Wno-deprecated -g $(INC_HEAD)

BIN_SOURCES = $(shell ls *.cpp)
BIN_OBJECTS = $(BIN_SOURCES:.cpp=.o)
BIN_CCFLAGS:= -Wall -fPIC -Wno-deprecated -g $(INC_HEAD)

BIN_PATH := ./
BIN		 := test

.PHONY: test
test:$(BIN_OBJECTS)
	$(CXX) $(INC_LIBS) -o $(BIN_PATH)/$@ $(BIN_OBJECTS) $(BIN_CCFLAGS)

.PHONY: clean
clean:
	rm -f *.o *~

.PHONY: cleanall
cleanall:
	rm -f *.o *~ $(BIN_PATH)/$(BIN)
