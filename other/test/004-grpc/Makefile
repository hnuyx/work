#****************************************************************************
#
# Makefile for grpc
# Henry
# 2020-03-17
#
#****************************************************************************

CXX	:= g++

INC_LIBS:= 
INC_HEAD:= 
INC_SLIB:= 
CXXFLAGS:= -Wall -c -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)

LIBS	:= -shared
AR	:= ar rc

LIBSPATH:= ./

OUTPUT	:= libtdgrpc.so
ARLIB	:= libtdgrpc.a

SOURCES = $(shell ls *.cc)
OBJECTS = $(SOURCES:.cc=.o)

BIN_SOURCES = $(shell ls *.cpp)
BIN_OBJECTS = $(BIN_SOURCES:.cpp=.o) $(OBJECTS)
BIN_CXXFLAGS:= -Wall -fPIC -Wno-deprecated -g $(INC_HEAD) $(INC_SLIB)
BIN_CXXFLAGS += `pkg-config --libs protobuf grpc++` -lgrpc++_reflection

BIN_PATH := ./
BIN		 := test

.PHONY: all
all:$(OUTPUT)

$(OUTPUT):$(OBJECTS)
	@$(CXX) -o $@ $(LIBS) $(OBJECTS) $(INC_HEAD) $(INC_LIBS) $(INC_SLIB)
	$(AR) $(ARLIB) $(OBJECTS) 


.PHONY: test
test:$(BIN_OBJECTS)
	$(CXX) $(INC_LIBS) -o $(BIN_PATH)/$@ $(BIN_OBJECTS) $(BIN_CXXFLAGS)


PROTOC = protoc
PROTOS_PATH = ./
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
TYPT_PROTO = data.proto
SERVICE_PROTO = data_service.proto
OUT_PATH = .

.PHONY: grpc
grpc:
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(OUT_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $(SERVICE_PROTO)
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(OUT_PATH) $(TYPT_PROTO) $(SERVICE_PROTO)

.PHONY: clean
clean:
	rm -f *.o *~

.PHONY: cleanall
cleanall:
	rm -f *.so *.o *~ $(OUTPUT) $(ARLIB) $(LIBSPATH)/$(OUTPUT) $(BIN_PATH)/$(BIN)
