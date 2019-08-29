#****************************************************************************
#
# Makefile for clib
# Henry
# 2019-08-28
#
#****************************************************************************

CXX	:= g++

INC_LIBS:= 
INC_HEAD:= 
INC_SLIB:= 
CXXFLAGS:= -Wall -c -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)

BIN_SOURCES = $(shell ls hl*.cpp)
BIN_OBJECTS = $(BIN_SOURCES:.cpp=.o)
BIN_CCFLAGS:= -Wall -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)

BIN_PATH := ./
BIN		 := test

.PHONY: test
test:$(BIN_OBJECTS) test.o
	$(CXX) $(INC_LIBS) -o $(BIN_PATH)/$@ $(BIN_OBJECTS) $(BIN_CCFLAGS) test.o

.PHONY: clean
clean:
	rm -f *.o *~

.PHONY: cleanall
cleanall:
	rm -f *.o *~ $(BIN_PATH)/$(BIN)
