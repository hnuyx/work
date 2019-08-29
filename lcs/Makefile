#****************************************************************************
#
# Makefile for test
# Henry
# 2019-08-28
#
#****************************************************************************

CC	:= gcc

INC_LIBS:= 
INC_HEAD:= 
INC_SLIB:= 
CFLAGS:= -Wall -c -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)

BIN_SOURCES = $(shell ls *.c)
BIN_OBJECTS = $(BIN_SOURCES:.c=.o)
BIN_CCFLAGS:= -Wall -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)

BIN_PATH := ./
BIN		 := test

.PHONY: test
test:$(BIN_OBJECTS)
	$(CC) $(INC_LIBS) -o $(BIN_PATH)/$@ $(BIN_OBJECTS) $(BIN_CCFLAGS)

.PHONY: clean
clean:
	rm -f *.o *~

.PHONY: cleanall
cleanall:
	rm -f *.o *~ $(BIN_PATH)/$(BIN)
